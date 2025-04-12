const db = require("../config/db");

class EntryController {
    constructor(wss) {
        this.wss = wss;
        this.lastCheckTime = "1970-01-01 00:00:00";
    }

    startChecking() {
        setInterval(() => {
            db.query(`
                SELECT c.*, u.firstname, u.lastname 
                FROM CARDCHECKS c
                LEFT JOIN USER u ON c.userid = u.userid
                WHERE c.check_time > ?
                ORDER BY c.check_time ASC
            `, [this.lastCheckTime], (err, results) => {
                if (err) {
                    console.error("DB error: ", err);
                    return;
                }

                if (results.length > 0) {
                    results.forEach(record => {
                        this.lastCheckTime = record.check_time;

                        let message = "";

                        if (record.cardid === "UNKNOWN" && record.userid === -1) {
                            message = `Ismeretlen kártyával próbáltak belépni! - ${record.check_time}`;
                        } else if (record.cardid !== "UNKNOWN" && record.userid === -1) {
                            message = `Tulajdonos nélküli kártyával próbáltak meg belépni! - ${record.check_time}`;
                        } else if (record.cevent === "ENTRY" || record.cevent === "AUTHORIZED") {
                            message = `${record.firstname} ${record.lastname} - Belépett! - ${record.check_time}`;
                        }

                        this.wss.clients.forEach(client => {
                            if (client.readyState === 1) { // WebSocket.OPEN
                                client.send(message);
                            }
                        });
                    });
                }
            });
        }, 1000); // 1 mp-enként
    }
}

module.exports = EntryController;
