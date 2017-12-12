# Opis funkcionalnosti C programa

Ideja je da C aplikacija funkcioniše kao komandna linija i tako simulira stvarne komande koje se mogu zadati bot aplikaciji.

Primeri komandi:
- ``delguild <gid>``
    * Brisanje servera iz baze, kao i svih njegovih kanala, filtera, emotikona itd.
    * Izaziva triger brisanja svih članova tog servera i članova svih kanala koji pripadaju tom serveru (ne brišu se korisnici već samo informacije o članstvu iz tabela Clan_Guilda i Clan_Kanala).
- ``addmember <uid> <gid>``
    * Dodaje korisnika u tabelu Clan_Guilda.
    * Izaziva triger provere pre unosa da li je korisnik banovan i ako jeste, sprečava unos.
- ``updmember <uid> <gid> <perms>``
    * Updatuje permisije korisnika
    * Izaziva triger logovanja.
- ``ban <uid> <gid> <timestamp>``
    * Dodaje ban za dati uid i gid i vreme trajanja.
    * Izaziva triger brisanja članstva tog korisnika za taj server i članstva u svim kanalima koji pripadaju tom serveru.
    * Izaziva triger logovanja.
- ``unban <uid> <gid>``
    * Uklanja uid ban za guild sa datim gid-om.
    * Izaziva triger logovanja.
- ``nickname <uid> <name>``
    * Dodaje novo prilagodjeno ime korisniku
- razne komande za ispis trenutnih servera, clanova itd.
    * Plan je da se ovde doda ispis stanja baze kao i izvršavanje raw SQL upita (npr ``q SELECT * FROM Guild;``).
