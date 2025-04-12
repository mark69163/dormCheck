const db = require("../config/db");

class CardModel {

    static addCardCheck(cardid, userid, event) {
        return new Promise((resolve, reject) => {
            const sql = "INSERT INTO CARDCHECKS (cardid, userid, cevent, check_time) VALUES (?, ?, ?, NOW())";
            db.query(sql, [cardid, userid, event], (err, result) => {
                if (err) {
                    reject(err);
                } else {
                    resolve(result.insertId);
                }
            });
        });
    }

    static validateCard(cardid) {
        return new Promise((resolve, reject) => {
            // Először megnézzük létezik-e a kártya
            const checkCardSql = "SELECT * FROM ACCESSCARD WHERE cardid = ?";
            db.query(checkCardSql, [cardid], (err, results) => {
                if (err) return reject(err);
                if (results.length === 0) return resolve("UNAUTHORIZED");  // Nincs ilyen kártya

                // Van ilyen kártya → megnézzük van-e hozzárendelve aktív userhez
                const checkAssignmentSql = `
                        SELECT * FROM ASSIGNMENT
                        WHERE cardid = ?
                        AND CURRENT_DATE BETWEEN valid_start AND valid_end
                    `;

                db.query(checkAssignmentSql, [cardid], (err, results) => {
                    if (err) return reject(err);
                    if (results.length === 0) return resolve("UNASSIGNED");  // Van kártya, de nincs aktív assignment
                    return resolve("AUTHORIZED");  // Van kártya, van aktív assignment
                });
            });
        });
    }

    static logInvalidCheck(cardid) {
        return new Promise((resolve, reject) => {
            const sql = "INSERT INTO INVALID_CHECKS (cardnumber) VALUES (?)";
            db.query(sql, [cardid], (err, result) => {
                if (err) {
                    reject(err);
                } else {
                    resolve(result.insertId);  // nem muszáj használni, de visszaadhatjuk
                }
            });
        });
    }


}
module.exports = CardModel;
