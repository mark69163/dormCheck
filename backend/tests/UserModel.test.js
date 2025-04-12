const UserModel = require('../models/UserModel');
const db = require('../config/db');

describe('UserModel.getUserByCardId', () => {

    beforeAll(async () => {
        await new Promise((resolve, reject) => {
            db.query(`
                INSERT INTO USER (userid, firstname, lastname, email, phone, gender, hashed_psw, dob)
                VALUES (1, 'Hello', 'FromNode', 'teszt@mail.hu', '123456', 'male', 'hashed', '2000-01-01')
                ON DUPLICATE KEY UPDATE firstname=VALUES(firstname)
            `, (err) => {
                if (err) return reject(err);
                resolve();
            });
        });

        await new Promise((resolve, reject) => {
            db.query(`
                INSERT INTO ACCESSCARD (cardid)
                VALUES ('ABC123')
                ON DUPLICATE KEY UPDATE cardid=VALUES(cardid)
            `, (err) => {
                if (err) return reject(err);
                resolve();
            });
        });

        await new Promise((resolve, reject) => {
            db.query(`
                INSERT INTO ASSIGNMENT (userid, cardid, valid_start, valid_end)
                VALUES (1, 'ABC123', CURDATE(), DATE_ADD(CURDATE(), INTERVAL 1 DAY))
                ON DUPLICATE KEY UPDATE valid_start=VALUES(valid_start)
            `, (err) => {
                if (err) return reject(err);
                resolve();
            });
        });
    });

    test('Létező és érvényes kártya esetén visszaadja a usert', async () => {
        const user = await UserModel.getUserByCardId('ABC123');
        expect(user).not.toBeNull();
        expect(user.firstname).toBe('Hello');
    });

    test('Nem létező kártyára null-t ad vissza', async () => {
        const user = await UserModel.getUserByCardId('NEMLETEZO');
        expect(user).toBeNull();
    });

    afterAll((done) => {
        db.end(done);  // lezárja az adatbázis kapcsolatot
    });
});
