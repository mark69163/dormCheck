const db = require("../config/db");

class HomeController {
    constructor(wss) {
        this.wss = wss;
        this.lastCheckTime = null; // Dinamikusan indul újra, ha újra megnyitják az oldalt
    }

    startChecking() {
        setInterval(() => {
            if (!this.lastCheckTime) return;

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

                        if (message !== "") {
                            this.wss.clients.forEach(client => {
                                if (client.readyState === 1) { // WebSocket.OPEN
                                    client.send(message);
                                }
                            });
                        }
                    });
                }
            });
        }, 1000); // 1 másodpercenként
    }

    index(req, res) {
        // Mikor a főoldalt újratöltik, akkor lenullázza a figyelési időt
        this.lastCheckTime = new Date().toISOString().slice(0, 19).replace("T", " ");
        res.render("home");
    }
}

module.exports = HomeController;
