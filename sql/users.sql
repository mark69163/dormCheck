CREATE USER IF NOT EXISTS 'staff'@'localhost' IDENTIFIED BY '7ZxM8ck*';
GRANT ALL PRIVILEGES ON dormCheck.* TO 'staff'@'localhost';

CREATE USER IF NOT EXISTS 'admin'@'localhost' IDENTIFIED BY 'sdjfndNJl23';
GRANT ALL PRIVILEGES ON *.* TO 'admin'@'localhost' WITH GRANT OPTION;

CREATE USER IF NOT EXISTS 'student'@'localhost' IDENTIFIED BY 'S8ze2c!Q';
GRANT SELECT ON dormCheck.USER TO 'student'@'localhost';
GRANT SELECT, INSERT, UPDATE, DELETE ON dormCheck.GUESTS TO 'student'@'localhost';

FLUSH PRIVILEGES;
