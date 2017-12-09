DELIMITER $

CREATE TRIGGER tr_Clan_Kanala_BINS1
BEFORE INSERT ON Clan_Kanala
FOR EACH ROW
BEGIN
  DECLARE x INTEGER;
  SET x = (
    SELECT COUNT(*) 
    FROM Clan_Guilda
    WHERE Clan_Guilda.korisnik_uid = new.korisnik_uid
      AND Clan_Guilda.guild_gid IN (SELECT guild_gid
                                    FROM Kanal
                                    WHERE cid = new.kanal_cid)
  );
  IF (x = 0) THEN
    SIGNAL SQLSTATE '45000' SET message_text='Korisnik nije clan guilda kome taj kanal pripada! Unos otkazan.';
  END IF;
END$


CREATE TRIGGER tr_Clan_Kanala_BINS2
BEFORE INSERT ON Clan_Kanala
FOR EACH ROW
BEGIN
  DECLARE x INTEGER;
  SET x = (
    SELECT COUNT(*) 
    FROM Ban
    WHERE Ban.banovani_uid = new.korisnik_uid
      AND Ban.guild_gid IN (SELECT guild_gid
                            FROM Kanal
                            WHERE Kanal.cid = new.kanal_cid)
  );
  IF (x <> 0) THEN
    SIGNAL SQLSTATE '45000' SET message_text='Nemoguce dodati banovanog korisnika!';
  END IF;
END$


CREATE TRIGGER tr_Clan_Guilda_BINS
BEFORE INSERT ON Clan_Guilda
FOR EACH ROW
BEGIN
  DECLARE x INTEGER;
  SET x = (
    SELECT COUNT(*) 
    FROM Ban
    WHERE Ban.banovani_uid = new.korisnik_uid
      AND Ban.guild_gid = new.guild_gid
  );
  IF (x <> 0) THEN
    SIGNAL SQLSTATE '45000' SET message_text='Nemoguce dodati banovanog korisnika!';
  END IF;
END$


CREATE TRIGGER tr_Ban_AINS
AFTER INSERT ON Ban
FOR EACH ROW
BEGIN
  DELETE FROM Clan_Guilda
  WHERE Clan_Guilda.korisnik_uid = new.banovani_uid
    AND Clan_Guilda.guild_gid = new.guild_gid;
END$


CREATE TRIGGER tr_Ban_AINS_Log
AFTER INSERT ON Ban
FOR EACH ROW
BEGIN
  INSERT INTO Log VALUES 
  (default, new.autor_uid, CONCAT('ban: ', new.banovani_uid, ' (until: ', COALESCE('indefinite', new.vreme), ')'), default, new.razlog);
END$


DELIMITER ;

