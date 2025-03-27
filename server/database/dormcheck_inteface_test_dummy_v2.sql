-- phpMyAdmin SQL Dump
-- version 5.2.1deb1
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Mar 27, 2025 at 03:32 PM
-- Server version: 10.11.6-MariaDB-0+deb12u1
-- PHP Version: 8.2.20

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `dormcheck`
--

-- --------------------------------------------------------

--
-- Table structure for table `ACCESSCARD`
--

CREATE TABLE `ACCESSCARD` (
  `cardid` varchar(16) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `ACCESSCARD`
--

INSERT INTO `ACCESSCARD` (`cardid`) VALUES
('15a1982'),
('436a39f'),
('c6a0fd8b'),
('UNKNOWN');

-- --------------------------------------------------------

--
-- Table structure for table `ASSIGNMENT`
--

CREATE TABLE `ASSIGNMENT` (
  `userid` int(11) NOT NULL,
  `cardid` varchar(16) NOT NULL,
  `valid_start` date NOT NULL DEFAULT curdate(),
  `valid_end` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `ASSIGNMENT`
--

INSERT INTO `ASSIGNMENT` (`userid`, `cardid`, `valid_start`, `valid_end`) VALUES
(1, '436a39f', '2025-03-19', '2025-05-19'),
(3, 'c6a0fd8b', '2025-03-19', '2035-12-31');

-- --------------------------------------------------------

--
-- Table structure for table `CARDCHECKS`
--

CREATE TABLE `CARDCHECKS` (
  `cardid` varchar(16) NOT NULL,
  `userid` int(11) NOT NULL,
  `cevent` varchar(50) NOT NULL,
  `check_time` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;


--
-- Table structure for table `USER`
--

CREATE TABLE `USER` (
  `userid` int(11) NOT NULL,
  `firstname` varchar(25) NOT NULL,
  `lastname` varchar(25) NOT NULL,
  `user_role` enum('student','staff','administrator','guest','unverified') NOT NULL DEFAULT 'student',
  `neptun_id` varchar(15) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `USER`
--

INSERT INTO `USER` (`userid`, `firstname`, `lastname`, `user_role`, `neptun_id`) VALUES
(-1, 'Unknown', 'User', 'unverified', NULL),
(1, 'Attila', 'Hoki', 'student', 'F2XVKV'),
(2, 'Armand', 'Koltai', 'staff', 'GYBASN'),
(3, 'Mark', 'Kovacs', 'administrator', NULL);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `ACCESSCARD`
--
ALTER TABLE `ACCESSCARD`
  ADD PRIMARY KEY (`cardid`);

--
-- Indexes for table `ASSIGNMENT`
--
ALTER TABLE `ASSIGNMENT`
  ADD PRIMARY KEY (`userid`,`cardid`,`valid_start`),
  ADD KEY `cardid` (`cardid`);

--
-- Indexes for table `CARDCHECKS`
--
ALTER TABLE `CARDCHECKS`
  ADD PRIMARY KEY (`cardid`,`userid`,`check_time`),
  ADD KEY `userid` (`userid`);

--
-- Indexes for table `USER`
--
ALTER TABLE `USER`
  ADD PRIMARY KEY (`userid`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `USER`
--
ALTER TABLE `USER`
  MODIFY `userid` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `ASSIGNMENT`
--
ALTER TABLE `ASSIGNMENT`
  ADD CONSTRAINT `ASSIGNMENT_ibfk_1` FOREIGN KEY (`userid`) REFERENCES `USER` (`userid`) ON DELETE CASCADE,
  ADD CONSTRAINT `ASSIGNMENT_ibfk_2` FOREIGN KEY (`cardid`) REFERENCES `ACCESSCARD` (`cardid`) ON DELETE CASCADE;

--
-- Constraints for table `CARDCHECKS`
--
ALTER TABLE `CARDCHECKS`
  ADD CONSTRAINT `CARDCHECKS_ibfk_1` FOREIGN KEY (`cardid`) REFERENCES `ACCESSCARD` (`cardid`) ON DELETE CASCADE,
  ADD CONSTRAINT `CARDCHECKS_ibfk_2` FOREIGN KEY (`userid`) REFERENCES `USER` (`userid`) ON DELETE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
