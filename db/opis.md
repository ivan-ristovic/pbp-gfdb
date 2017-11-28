# Seminarski rad iz PBP

## Tema: Bot za Discord

## Opis domena:


### Korisnik:
- Korisnika odlikuje jedinstveni identifikator (``uid``) i ``prilagodjeno_ime``.
- Korisnik koji se nalazi u bazi mora imati nalog na Discord platformi jer se jedinstveni identifikator tog naloga koristi u bazi kao ``uid`` (user id).
- ``prilagodjeno_ime`` služi kao "nadimak" za korisnika. Može imati nedefinisane vrednosti, i u tom slučaju se koristi korisničko ime koje Discord pamti.

### Server (Guild)
- Server odlikuje jedinstveni identifikator (``gid``), ``prilagodjeno_ime`` i ``prilagodjeni_prefix``.
- Server koji se nalazi u bazi mora postojati na Discord platformi jer se jedinstveni identifikator tog servera koristi u bazi kao ``gid`` (guild id).
- ``prilagodjeno_ime`` služi kao "nadimak" za server. Može imati nedefinisane vrednosti, i u tom slučaju se koristi ime servera koje Discord pamti.
- ``prilagodjeni_prefix``, ukoliko je postavljen (tj. nije nedefinisan), označava da se komande pozivaju sa prefiksom koji nije podrazumevajući (na primer podrazumevajući prefiks za komande je ``!``, ali korisnici mogu to da promene za njihov server).

### Kanal
- Kanal odlikuje jedinstveni identifikator (``cid``), ``prilagodjeno_ime`` i ``tip``.
- Kanal koji se nalazi u bazi mora postojati na Discord platformi jer se jedinstveni identifikator tog kanala koristi u bazi kao ``cid`` (channel id).
- ``prilagodjeno_ime`` služi kao "nadimak" za kanal. Može imati nedefinisane vrednosti, i u tom slučaju se koristi ime kanala koje Discord pamti.
- ``tip`` može biti ``tekstualni``, ``glasovni`` ili ``kategorija``. U zavisnosti od tipa kanala se odredjuju funkcije koje se smeju izvoditi nad datim kanalom (na primer audio zapis se sme puštati samo u glasovnim kanalima).

### Veze izmedju korisnika, servera i kanala:
- Svaki server mora imati barem jedan kanal, ali ih obično ima više. Sa druge strane, kanal ima tačno jedan roditeljski server. Ukoliko se server obriše iz baze, brišu se i sva "deca" kanali.
- Korisnik može biti član jednog ili više servera. U jednom serveru mora biti barem jedan ili više korisnika.
- Korisnik koji je član servera ne mora biti istovremeno i član svih kanala (može mu se ograničiti pristup odredjenim kanalima). Dakle, jedan član servera može biti član jednog ili više kanala, ali sa druge strane ako je član kanala onda je istovremeno i član servera. Ukoliko korisnik napusti server, onda istovremeno napušta i sve kanale tog servera.

### Filter
- Server može definisati filtere za poruke koje korisnici šalju.
- Filter odredjuje ``filter_regex``.
- ``filter_regex`` je regularni izraz koji se pokušava upariti sa svakom porukom poslatom u kanalima servera. Svaka poruka koja ima poklapanja sa nekim filterom se briše.
- Jedan server može imati više filtera, ali ih ne mora imati. Sa druge strane, filter se primenjuje na tačno jedan server.
- Ukoliko se server obriše iz baze, brišu se i svi postavljeni filteri.

### Emotikon (Emoji)
- Server može definisati emotikone specifične za taj server (mogu se koristiti samo u kanalima tog servera).
- Jedan emotikon odlikuje ``ime`` (jedinstveno), ``unicode_reprezentacija``, ``datum_kreiranja`` i ``autor_uid`` (uid autora emotikona).
- Server može imati od 0 do više emotikona ali jedan emotikon može da pripada tačno jednom serveru.
- Jedan član servera može napraviti više emotikona ali ne mora napraviti nijedan. Svaki emotikon ima tačno jednog autora. Ukoliko autor emotikona napusti server, polje autora se postavlja na nedefinisanu vrednost.
- Više različitih servera može imati emotikone sa istim imenom.

### Konfiguracija servera

TODO

### Zadatak
- Server može definisati zadatke koji se izvršavaju u definisano vreme.
- Jedan zadatak karakterise ``sadrzaj``, ``vreme_izvrsavanja``, ``autor_uid`` (uid autora zadatka)
- Jedan server može imati više zadataka ali ne mora imati nijedan. Jedan zadatak ima tačno jedan server na koji se odnosi. Ako se server obriše iz baze, brišu se i svi zadaci koji se odnose na taj server.
- Kada prodje vreme_izvrsavanja zadatka, on se briše iz baze.

### Ban

TODO
