DELIMITER $

CREATE TRIGGER tr_Clan_Kanala_BINS
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


CREATE TRIGGER tr_Ban_AINS
AFTER INSERT ON Ban
FOR EACH ROW
BEGIN
  DELETE FROM Clan_Guilda
  WHERE Clan_Guilda.korisnik_uid = new.banovani_uid
    AND Clan_Guilda.guild_gid = new.guild_gid;
END$


DELIMITER ;

