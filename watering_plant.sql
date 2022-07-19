﻿# Host: localhost  (Version 5.5.5-10.4.6-MariaDB)
# Date: 2022-07-02 16:34:14
# Generator: MySQL-Front 6.0  (Build 2.20)


#
# Structure for table "sensordata"
#

DROP TABLE IF EXISTS `sensordata`;
CREATE TABLE `sensordata` (
  `id` int(6) unsigned NOT NULL AUTO_INCREMENT,
  `suhu` decimal(10,2) NOT NULL,
  `kelembapanu` int(11) NOT NULL,
  `kelembapant` int(11) NOT NULL,
  `keterangan` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=25 DEFAULT CHARSET=latin1;

#
# Data for table "sensordata"
#

INSERT INTO `sensordata` VALUES (1,31.00,59,500,'SIRAM OTOMATIS'),(2,29.00,64,636,'SIRAM OTOMATIS'),(3,30.00,64,637,'SIRAM OTOMATIS'),(4,30.00,64,636,'SIRAM OTOMATIS'),(5,30.00,63,636,'SIRAM OTOMATIS'),(6,30.00,63,639,'SIRAM OTOMATIS'),(7,29.00,63,645,'SIRAM OTOMATIS'),(8,30.00,63,639,'SIRAM OTOMATIS'),(9,30.00,63,638,'SIRAM OTOMATIS'),(10,30.00,63,638,'SIRAM OTOMATIS'),(11,30.00,63,639,'SIRAM OTOMATIS'),(12,30.00,63,644,'SIRAM OTOMATIS'),(13,30.00,63,642,'SIRAM OTOMATIS'),(14,30.00,63,642,'SIRAM OTOMATIS'),(15,30.00,63,640,'SIRAM OTOMATIS'),(16,30.00,63,644,'SIRAM OTOMATIS'),(17,30.00,63,639,'SIRAM OTOMATIS'),(18,30.00,63,640,'SIRAM OTOMATIS'),(19,30.00,63,641,'SIRAM OTOMATIS'),(20,30.00,63,638,'SIRAM OTOMATIS'),(21,29.00,64,637,'SIRAM OTOMATIS'),(22,30.00,63,630,'SIRAM OTOMATIS'),(23,30.00,63,629,'SIRAM OTOMATIS');

#
# Structure for table "threshold"
#

DROP TABLE IF EXISTS `threshold`;
CREATE TABLE `threshold` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `siramo` int(11) NOT NULL DEFAULT 0,
  `tanahk` int(11) NOT NULL DEFAULT 0,
  `normal` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

#
# Data for table "threshold"
#

INSERT INTO `threshold` VALUES (1,550,500,300);
