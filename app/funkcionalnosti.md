Ideja je da C aplikacija funkcioniše kao komandna linija i tako simulira stvarne komande koje se mogu zadati bot aplikaciji.

Primeri komandi:
- ``!delguild <gid>`` - brisanje servera, kao i svih njegovih zavisnih entiteta: filteri, emotikoni itd.
- ``!addmember <uid> <gid>`` - dodaje korisnika u tabelu Clan_Guilda, izaziva proveru da li je  korisnik banovan
- ``!updmember <uid> <gid> <perms>`` - updatuje permisije korisnika, izaziva trigger logovanja
- ``!ban <uid>`` - izaziva triger brisanja korisnika iz Clan_Guilda kao i trigger logovanja
- ``!unban <uid>`` - izaziva logovanje
- razne komande za ispis trenutnih servera, clanova itd.
