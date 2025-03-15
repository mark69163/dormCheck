INSERT INTO `USER`(firstname, lastname, email, phone, gender, hashed_psw, user_role, dob, neptun_id, enroll_year) VALUES
('Gipsz', 'Jakab', 'gipszjakab@uni-neumann.hu', '061555666', 'male', 'asd1234', 'student', '2003-11-02', 'DFKL3G', '2023/1'),
('Kovács', 'Lújza', 'kovacslujza@uni-neumann.hu', '062666777', 'female', 'asd3456', 'staff', '1965-01-22', NULL, NULL),
('Kiss', 'Péter', 'kisspeter@uni-neumann.hu', '064213443', 'male', 'asd5678', 'administrator', '1995-02-12', NULL, NULL);

INSERT INTO ACCESSCARD(cardid) VALUES
("JONGHSJDND34"),
("FOLKGFLG323S"),
("OPDSKG32K223");

INSERT INTO BUILDING(build_name, floor_count, build_address) VALUES
("3-as épület", 5, "6000 Kecskemét Homokszem utca 6"),
("2-es épület", 4, "6000 Kecskemét Homokszem utca 6");

INSERT INTO ROOM(room_code, floor, block_number, bid) VALUES
("401", 3, 1, 2),
("402", 3, 2, 2),
("502", 4, 1, 2),
("503", 4, 2, 2),
("101", 0, 1, 1),
("102", 0, 2, 1);

INSERT INTO SERVICES(description) VALUES
("Edzőterem"),
("Értékmegörző szekrény"),
("Mosókonyha");

INSERT INTO GUESTS(name, ID_Card) VALUES
("Vendég János", "ID324234"),
("Vendég Margit", "ID824246");

INSERT INTO PLACEMENT(userid, roomid, moved_in) VALUES
(1,3,1),
(2,4,1),
(3,2,0);

INSERT INTO SUBSCRIPTIONS(userid, serviceid, end_date) VALUES
(1,1,"2025-04-15"),
(2,2,"2025-06-11");

INSERT INTO ASSIGNMENT(userid, cardid, valid_end) VALUES
(1,"FOLKGFLG323S","2025-08-11"),
(2,"OPDSKG32K223","2025-10-23");

INSERT INTO GUESTRECEPTION(userid, guestid) VALUES
(1,2),
(2,2),
(2,1);

INSERT INTO PRICES(description, monthly_cost) VALUES
("Edzőterem", 5500),
("Értékmegörző szekrény", 3500),
("Mosókonyha", 2000);
