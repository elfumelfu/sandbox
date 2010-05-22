-- phpMyAdmin SQL Dump
-- version 3.2.0.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: May 13, 2010 at 10:57 AM
-- Server version: 5.1.36
-- PHP Version: 5.3.0

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `se_inchirieaza`
--
CREATE DATABASE `se_inchirieaza` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `se_inchirieaza`;

-- --------------------------------------------------------

--
-- Table structure for table `apartamente`
--

CREATE TABLE IF NOT EXISTS `apartamente` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `judet` varchar(255) NOT NULL DEFAULT '',
  `localitate` varchar(255) NOT NULL DEFAULT '',
  `nrcam` int(11) NOT NULL DEFAULT '0',
  `zona` varchar(255) NOT NULL DEFAULT '',
  `bloc` varchar(255) NOT NULL DEFAULT '',
  `ap` varchar(255) NOT NULL DEFAULT '',
  `etaj` varchar(255) NOT NULL DEFAULT '',
  `dsc` varchar(255) NOT NULL DEFAULT '',
  `grupsanitar` int(11) NOT NULL DEFAULT '0',
  `pret` int(11) NOT NULL DEFAULT '0',
  `moneda` varchar(255) NOT NULL DEFAULT '',
  `data` date,
  `data_modificarii` date,
  `data_expirarii` date,
  `balcon` tinyint(1) NOT NULL DEFAULT '0',
  `gresie` tinyint(1) NOT NULL DEFAULT '0',
  `faianta` tinyint(1) NOT NULL DEFAULT '0',
  `termopan` tinyint(1) NOT NULL DEFAULT '0',
  `parchet` tinyint(1) NOT NULL DEFAULT '0',
  `um` tinyint(1) NOT NULL DEFAULT '0',
  `ct` tinyint(1) NOT NULL DEFAULT '0',
  `ac` tinyint(1) NOT NULL DEFAULT '0',
  `apometre` tinyint(1) NOT NULL DEFAULT '0',
  `repartitoare` tinyint(1) NOT NULL DEFAULT '0',
  `mobilat` varchar(255) NOT NULL  DEFAULT '',
  `nume` varchar(255) NOT NULL DEFAULT '',
  `telefon` varchar(255) NOT NULL DEFAULT '',
  `info_prop` text,
  `altele` text,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=11 ;

--
-- Dumping data for table `apartamente`
--

INSERT INTO `apartamente` (`id`, `judet`, `localitate`, `nrcam`, `zona`, `bloc`, `ap`, `etaj`, `dsc`, `grupsanitar`, `pret`, `moneda`, `data`, `data_modificarii`, `data_expirarii`, `balcon`, `gresie`, `faianta`, `termopan`, `parchet`, `um`, `ct`, `ac`, `apometre`, `repartitoare`, `mobilat`, `nume`, `telefon`, `info_prop`, `altele`) VALUES
(1, 'GALATI', '', 2, '', '', '', '', '', 0, 0, '', '0000-00-00', '0000-00-00', '0000-00-00', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', '', '');



