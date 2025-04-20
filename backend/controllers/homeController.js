const db = require("../config/db");

class HomeController {
    constructor(wss) {
        this.wss = wss;
        this.lastCheckTime = null;
        this.intervalStarted = false;
    }

    startChecking() {
        if (this.intervalStarted) return;
        this.intervalStarted = true;

        setInterval(() => {
            if (!this.lastCheckTime) return;

            db.query(`
                SELECT c.*, u.firstname, u.lastname, u.img_path 
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
                            message = `${record.firstname} ${record.lastname} - Belépett! - ${record.check_time} - ${record.img_path}`;
                        }

                        if (message !== "") {
                            this.wss.clients.forEach(client => {
                                if (client.readyState === 1) {
                                    client.send(message);
                                }
                            });
                        }
                    });
                }
            });
        }, 1000);
    }

    index(req, res) {
        db.query(`
        SELECT check_time 
        FROM CARDCHECKS 
        ORDER BY check_time DESC 
        LIMIT 1
    `, (err, results) => {
            if (err) {
                console.error("Nem sikerült lekérni az utolsó check_time-ot:", err);
                return res.status(500).send("Hiba történt.");
            }

            if (results.length > 0) {
                this.lastCheckTime = results[0].check_time;
            } else {
                this.lastCheckTime = new Date().toISOString().slice(0, 19).replace("T", " ");
            }

            this.startChecking(); // csak itt indítjuk el, amikor már van érvényes idő
            res.render("home");
        });
    }
}

module.exports = HomeController;
