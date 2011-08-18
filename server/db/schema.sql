# Dump File
#
# Database is ported from MS Access
#--------------------------------------------------------
# Program Version 3.0.108

CREATE DATABASE IF NOT EXISTS `timelis`;
USE `timelis`;


#
# Table structure for table 'Event'
#

DROP TABLE IF EXISTS `Event`;
CREATE TABLE `Event` (
  `id` INTEGER NOT NULL AUTO_INCREMENT, 
  `time` DATETIME, 
  `trigger` DATETIME, 
  `text` TEXT, 
  `fired` TINYINT DEFAULT 0, 
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `Project`;
CREATE TABLE `Project` (
  `ID` INTEGER NOT NULL AUTO_INCREMENT, 
  `MasterID` INTEGER DEFAULT 0, 
  `Name` VARCHAR(50), 
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `Activity`;
CREATE TABLE `Activity` (
  `ID` INTEGER NOT NULL AUTO_INCREMENT, 
  `MasterID` INTEGER DEFAULT 0, 
  `ProjectID` INTEGER NOT NULL, 
  `Name` VARCHAR(50), 
  `Enabled` TINYINT DEFAULT 0, 
  PRIMARY KEY (ID), 
  INDEX (ProjectID),
  FOREIGN KEY (ProjectID) REFERENCES Project(ID)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `TimeSheet`;
CREATE TABLE `TimeSheet` (
  `ID` INTEGER NOT NULL AUTO_INCREMENT, 
  `StartTime` DATETIME, 
  `EndTime` DATETIME, 
  `ReportingHours` INTEGER DEFAULT -1, 
  `Modified` TINYINT DEFAULT -1, 
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `Task`;
CREATE TABLE `Task` (
  `ID` INTEGER NOT NULL AUTO_INCREMENT, 
  `SheeterID` INTEGER DEFAULT 0, 
  `ActivityID` INTEGER DEFAULT 0, 
  `OfficialDescription` VARCHAR(255), 
  `PrivateDescription` VARCHAR(255), 
  `Minutes` INTEGER DEFAULT 0, 
  PRIMARY KEY (`ID`), 
  INDEX ('SheeterID'),
  FOREIGN KEY ('SheeterID') REFERENCES TimeSheet('ID'),
  INDEX ('ActivityID'),
  FOREIGN KEY ('ActivityID') REFERENCES Activity('ID')
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `Pauses`;
CREATE TABLE `Pauses` (
  `ID` INTEGER NOT NULL AUTO_INCREMENT, 
  `SheeterID` INTEGER DEFAULT 0, 
  `Begin` DATETIME, 
  `End` DATETIME, 
  PRIMARY KEY (`ID`), 
  INDEX ('SheeterID'),
  FOREIGN KEY ('SheeterID') REFERENCES TimeSheet('ID')
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
