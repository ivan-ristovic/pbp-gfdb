SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

DROP DATABASE IF EXISTS pbp_gfdb;
CREATE DATABASE IF NOT EXISTS pbp_gfdb;
USE pbp_gfdb;

-- -----------------------------------------------------
-- Table `Korisnik`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Korisnik` (
  `uid` BIGINT(20) NOT NULL,
  `prilagodjeno_ime` VARCHAR(45) NULL DEFAULT NULL,
  PRIMARY KEY (`uid`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Guild`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Guild` (
  `gid` BIGINT(20) NOT NULL,
  `prilagodjeno_ime` VARCHAR(45) NULL DEFAULT NULL,
  `prilagodjeni_prefix` VARCHAR(10) NULL DEFAULT NULL,
  PRIMARY KEY (`gid`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Kanal`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Kanal` (
  `cid` BIGINT(20) NOT NULL,
  `guild_gid` BIGINT(20) NOT NULL,
  `tip` VARCHAR(10) NOT NULL,
  `prilagodjeno_ime` VARCHAR(45) NULL DEFAULT NULL,
  PRIMARY KEY (`cid`),
  INDEX `fk_Kanal_Guild_idx` (`guild_gid` ASC),
  CONSTRAINT `fk_Kanal_Guild`
    FOREIGN KEY (`guild_gid`)
    REFERENCES `Guild` (`gid`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Clan_Guilda`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Clan_Guilda` (
  `korisnik_uid` BIGINT(20) NOT NULL,
  `guild_gid` BIGINT(20) NOT NULL,
  `vreme_ulaska` DATETIME NOT NULL,
  `prilagodjene_permisije` BIT(8) NULL DEFAULT 0,
  PRIMARY KEY (`korisnik_uid`, `guild_gid`),
  INDEX `fk_Korisnik_has_Guild_Guild1_idx` (`guild_gid` ASC),
  INDEX `fk_Korisnik_has_Guild_Korisnik1_idx` (`korisnik_uid` ASC),
  CONSTRAINT `fk_Korisnik_has_Guild_Korisnik1`
    FOREIGN KEY (`korisnik_uid`)
    REFERENCES `Korisnik` (`uid`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Korisnik_has_Guild_Guild1`
    FOREIGN KEY (`guild_gid`)
    REFERENCES `Guild` (`gid`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Clan_Kanala`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Clan_Kanala` (
  `korisnik_uid` BIGINT(20) NOT NULL,
  `kanal_cid` BIGINT(20) NOT NULL,
  `prilagodjene_permisije` BIT(8) NULL DEFAULT 0,
  INDEX `fk_Pripada_Guildu_has_Kanal_Kanal1_idx` (`kanal_cid` ASC),
  INDEX `fk_Pripada_Guildu_has_Kanal_Pripada_Guildu1_idx` (`korisnik_uid` ASC),
  PRIMARY KEY (`kanal_cid`, `korisnik_uid`),
  CONSTRAINT `fk_Pripada_Guildu_has_Kanal_Pripada_Guildu1`
    FOREIGN KEY (`korisnik_uid`)
    REFERENCES `Korisnik` (`uid`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Pripada_Guildu_has_Kanal_Kanal1`
    FOREIGN KEY (`kanal_cid`)
    REFERENCES `Kanal` (`cid`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Filter`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Filter` (
  `fid` INT NOT NULL,
  `guild_gid` BIGINT(20) NOT NULL,
  `filter_regex` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`fid`, `guild_gid`),
  INDEX `fk_Filter_Guild1_idx` (`guild_gid` ASC),
  CONSTRAINT `fk_Filter_Guild1`
    FOREIGN KEY (`guild_gid`)
    REFERENCES `Guild` (`gid`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Emoji`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Emoji` (
  `ime` VARCHAR(20) NOT NULL,
  `guild_gid` BIGINT(20) NOT NULL,
  `autor_uid` BIGINT(20),
  `datum_kreiranja` DATETIME NOT NULL,
  `unicode_reprezentacija` CHAR(1) NOT NULL,
  PRIMARY KEY (`ime`, `guild_gid`),
  INDEX `fk_Emoji_Guild1_idx` (`guild_gid` ASC),
  INDEX `fk_Emoji_Korisnik1_idx` (`autor_uid` ASC),
  CONSTRAINT `fk_Emoji_Guild1`
    FOREIGN KEY (`guild_gid`)
    REFERENCES `Guild` (`gid`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Emoji_Korisnik1`
    FOREIGN KEY (`autor_uid`)
    REFERENCES `Korisnik` (`uid`)
    ON DELETE SET NULL
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Zadatak`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Zadatak` (
  `tid` INT NOT NULL,
  `sadrzaj` VARCHAR(45) NOT NULL,
  `vreme_izvrsavanja` DATETIME NOT NULL,
  PRIMARY KEY (`tid`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Konfiguracija_Servera`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Konfiguracija_Servera` (
  `guild_gid` BIGINT(20) NOT NULL,
  `welcome_cid` BIGINT(20) NULL DEFAULT NULL,
  `leave_cid` BIGINT(20) NULL DEFAULT NULL,
  `antispam_aktivan` BIT(1) NOT NULL DEFAULT 0,
  `antiflood_aktivan` BIT(1) NOT NULL DEFAULT 0,
  INDEX `fk_Konfiguracija_Servera_Kanal1_idx` (`welcome_cid` ASC),
  INDEX `fk_Konfiguracija_Servera_Kanal2_idx` (`leave_cid` ASC),
  PRIMARY KEY (`guild_gid`),
  CONSTRAINT `fk_Konfiguracija_Servera_Guild1`
    FOREIGN KEY (`guild_gid`)
    REFERENCES `Guild` (`gid`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Konfiguracija_Servera_Kanal1`
    FOREIGN KEY (`welcome_cid`)
    REFERENCES `Kanal` (`cid`)
    ON DELETE SET NULL
    ON UPDATE SET NULL,
  CONSTRAINT `fk_Konfiguracija_Servera_Kanal2`
    FOREIGN KEY (`leave_cid`)
    REFERENCES `Kanal` (`cid`)
    ON DELETE SET NULL
    ON UPDATE SET NULL)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Ban`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Ban` (
  `banovani_uid` BIGINT(20) NOT NULL,
  `guild_gid` BIGINT(20) NOT NULL,
  `autor_uid` BIGINT(20),
  `vreme` DATETIME NULL DEFAULT NULL,
  `razlog` VARCHAR(45) NULL DEFAULT NULL,
  PRIMARY KEY (`guild_gid`, `banovani_uid`),
  INDEX `fk_Ban_Guild1_idx` (`guild_gid` ASC),
  INDEX `fk_Ban_Korisnik2_idx` (`autor_uid` ASC),
  CONSTRAINT `fk_Ban_Korisnik1`
    FOREIGN KEY (`banovani_uid`)
    REFERENCES `Korisnik` (`uid`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Ban_Guild1`
    FOREIGN KEY (`guild_gid`)
    REFERENCES `Guild` (`gid`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Ban_Korisnik2`
    FOREIGN KEY (`autor_uid`)
    REFERENCES `Korisnik` (`uid`)
    ON DELETE SET NULL
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Log`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Log` (
  `lid` INT NOT NULL,
  `uid_izvrsioca` BIGINT(20) NOT NULL,
  `komanda` VARCHAR(64) NOT NULL,
  `vreme_izvrsavanja` DATETIME NULL DEFAULT CURRENT_TIMESTAMP,
  `komentar` VARCHAR(128) NULL,
  PRIMARY KEY (`lid`),
  INDEX `fk_Log_Korisnik1_idx` (`uid_izvrsioca` ASC),
  CONSTRAINT `fk_Log_Korisnik1`
    FOREIGN KEY (`uid_izvrsioca`)
    REFERENCES `Korisnik` (`uid`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
