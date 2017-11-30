# Seminarski rad iz PBP

## Tema
Baza podataka za Discord bot aplikaciju.

## Opis domena

[Discord](https://discordapp.com) je online komunikaciona platforma. Pordržava tekstualni (text) i glasovni (voice) chat. Korisnici Discord servisa mogu napraviti svoje servere (guilds) koji mogu sadržati više glasovnih ili tekstualnih kanala (channels). Jedan korisnik u isto vreme može biti član više servera. Serveri nemaju limit kad je u pitanju broj članova.

Developeri mogu kreirati sopstvene aplikacije (botove) koje će se povezivati na servere, ponašati se kao obični korisnici i izvršavati neki posao. Moja aplikacija funkcioniše tako što joj korisnici zadaju komande u tekstualnim kanalima. Svaka poruka koja počinje prefiksom ``!`` (podrazumevajuće, može da bude specifično za server) se smatra komandom. Aplikacija parsira komandu i izvršava posao.

Spisak svih komandi za moju aplikaciju, kao i detaljan opis funkcionalnosti i izvorni kod, se može naći [ovde](https://github.com/ivan-ristovic/the-godfather). Izmedju ostalog, najbitnije funkcionalnosti su:
- puna administracija servera, kanala, korisnika...
- filtriranje poruka, korisnika i programabilne reakcije na poruke
- pretraga internet servisa (YouTube, reddit, Imgur, Steam...) kao i "pretplaćivanje" (subscribing) na RSS URL-ove
- puštanje muzike u glasovnim kanalima
- igranje mnogobrojnih igara (neki ljudi vole igrice)
- itd. (biće još)

Baza podataka za ovu aplikaciju bi morala imati sledeće entitete:
- **nezavisni**:
    - korisnik
    - server (guild)
    - zadatak
    - ban
    - log
- **zavisni**:
    - kanal (zavisi od servera)
    - filter (zavisi od servera)
    - emotikon (zavisi od servera)
    - serverska konfiguracija (zavisi od servera)
- **agregirani**
    - član servera (veza: korisnik - server)
    - član kanala (veza: član servera - kanal)

Trigeri koji bi bili prisutni:
- izmene servera, kanala, serverske konfiguracije itd. bi bile dodate u log
- svaka akcija banovanja / unbanovanja se mora dodati u log
- izvršavanje zadataka (brisanje zadatka iz baze jer se zadatak izvršio) se takodje mora logovati
- svako dodavanje ili izmena filtera, emotikona se mora logovati
- itd.

<br>
## Opis entiteta i veza
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
- Jedan emotikon odlikuje ``ime`` (jedinstveno za server), ``unicode_reprezentacija``, ``datum_kreiranja`` i ``autor_uid`` (uid autora emotikona).
- Server može imati od 0 do više emotikona ali jedan emotikon može da pripada tačno jednom serveru.
- Jedan član servera može napraviti više emotikona ali ne mora napraviti nijedan. Svaki emotikon ima tačno jednog autora. Ukoliko autor emotikona napusti server, polje autora se postavlja na nedefinisanu vrednost.
- Više različitih servera može imati emotikone sa istim imenom.

### Konfiguracija servera
- Svaki server ima svoju specifičnu konfiguraciju
- Jednu konfiguraciju karakteriše:  ``welcome_kanal``, ``leave_kanal``, ``antispam_aktivan``, ``antiflood_aktivan``
- ``welcome_kanal`` i ``leave_kanal`` su kanali u koje bot šalje welcome/leave poruke. Ukoliko nisu postavljeni, bot ne šalje poruke prilikom ulaska (izlaska) članova u (iz) servera
- ``antispam_aktivan`` je boolean vrednost koja odredjuje da li je antispam aktivan (ukoliko korisnik šalje dosta poruka u kratkom vremenskom intervalu, biće utišan)
- ``antiflood_aktivan`` je boolean vrednost koja odredjuje da li je antiflood aktivan (ukoliko gomila korisnika upadne na server u kratkom intervalu, to će se smatrati DDoS napadom i ti korisnici će biti banovani)
- Server ima tačno jednu konfiguraciju

### Zadatak
- Korisnici mogu definisati zadatke koji se izvršavaju u definisano vreme.
- Jedan zadatak karakteriše ``sadrzaj``, ``vreme_izvrsavanja``
- Kada prodje vreme_izvrsavanja zadatka, on se briše iz baze.

### Ban
- Server može banovati korisnike (zabraniti im pristup odredjenom serveru)
- Svaki ban odlikuje ``server_gid``, ``banovani_uid``, ``autor_uid``, ``vreme``, ``razlog``
- ``guild_gid`` predstavlja identifikator servera
- ``banovani_uid`` predstavlja identifikator banovanog korisnika
- ``autor_uid`` predstavlja identifikator korisnika koji je izvršio akciju
- ``vreme`` predstavlja vreme uklanjanja bana
- ``razlog`` opcioni razlog bana

### Log
- Aplikacija ima log u koji se upisuju sve izvršene akcije
- Jedan entry u log fajlu karakteriše ``uid_izvrsioca``, ``komanda``, ``vreme_izvrsavanja``, ``komentar``
- ``uid_izvrsioca`` je identifikator (uid) korisnika koji je izvršio neku komandu (``komanda``).
- ``vreme_izvrsavanja`` i ``komentar`` predstavljaju vreme izvršavanja komande i opcioni komentar koji je korisnik ostavio
