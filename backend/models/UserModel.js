const db = require("../config/db");

class UserModel {
    static getUserByCardId(cardid) {
        return new Promise((resolve, reject) => {
            const sql = `
                SELECT u.*
                FROM USER u
                JOIN ASSIGNMENT a ON u.userid = a.userid
                WHERE a.cardid = ?
                  AND CURRENT_DATE BETWEEN a.valid_start AND a.valid_end
            `;
            db.query(sql, [cardid], (err, results) => {
                if (err) {
                    return reject(err);
                }
                if (results.length === 0) {
                    return resolve(null); // Nincs érvényes kártya
                }
                resolve(results[0]); // Megtalált user visszaadása
            });
        });
    }
}

module.exports = UserModel;
