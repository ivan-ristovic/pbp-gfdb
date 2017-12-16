#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "command_handler.h"
#include "database.h"


void process_command(char **parsed_data, int arg_c)
{
    if (!strcmp(parsed_data[0], "exit")) {
        clean_up_and_exit(EXIT_SUCCESS);
    } else if (!strcmp(parsed_data[0], "show") || !strcmp(parsed_data[0], "s")) {
        if (arg_c >= 2)
            show(parsed_data[1]);
        else
            printf("Sta da prikazem?");
    } else if (!strcmp(parsed_data[0], "delguild") || !strcmp(parsed_data[0], "dg")) {
        if (arg_c >= 2)
            delguild(parsed_data);
        else
            printf("Nedovoljno argumenata prosledjeno za komandu: delguild\n");
    } else if (!strcmp(parsed_data[0], "addguildmember") || !strcmp(parsed_data[0], "+gm")) {
        if (arg_c >= 3)
            addguildmember(parsed_data);
        else
            printf("Nedovoljno argumenata prosledjeno za komandu: addguildmember\n");
    } else if (!strcmp(parsed_data[0], "addchannelmember") || !strcmp(parsed_data[0], "+cm")) {
        if (arg_c >= 3)
            addchannelmember(parsed_data);
        else
            printf("Nedovoljno argumenata prosledjeno za komandu: addchannelmember\n");
    } else if (!strcmp(parsed_data[0], "updmember") || !strcmp(parsed_data[0], "um")) {
        if (arg_c >= 4)
            updmember(parsed_data);
        else
            printf("Nedovoljno argumenata prosledjeno za komandu: updmember\n");
    } else if (!strcmp(parsed_data[0], "ban") || !strcmp(parsed_data[0], "b")) {
        if (arg_c >= 4)
            ban(parsed_data, arg_c - 1);
        else
            printf("Nedovoljno argumenata prosledjeno za komandu: ban\n");
    } else if (!strcmp(parsed_data[0], "unban") || !strcmp(parsed_data[0], "ub")) {
        if (arg_c >= 2)
            unban(parsed_data);
        else
            printf("Nedovoljno argumenata prosledjeno za komandu: unban\n");
    } else if (!strcmp(parsed_data[0], "nickname") || !strcmp(parsed_data[0], "nick")) {
        if (arg_c >= 3)
            nickname(parsed_data);
        else
            printf("Nedovoljno argumenata prosledjeno za komandu: nickname\n");
    } else if (!strcmp(parsed_data[0], "query") || !strcmp(parsed_data[0], "q")) {
        if (arg_c >= 2)
            q(parsed_data, arg_c);
        else
            printf("Nedovoljno argumenata prosledjeno za komandu: query\n");
    } else if (!strcmp(parsed_data[0], "guildconfig") || !strcmp(parsed_data[0], "gcfg")) {
        if (arg_c >= 6)
            guildconfig(parsed_data);
        else
            printf("Nedovoljno argumenata prosledjeno za komandu: guildconfig\n");
    } else if (!strcmp(parsed_data[0], "help") || !strcmp(parsed_data[0], "h")) {
        print_help();
    } else {
        printf("Nepoznata komanda: %s\n", parsed_data[0]);
    }
}


void show(const char *s)
{
    if (!strcmp(s, "users") || !strcmp(s, "u"))
        show_table("Korisnik");
    else if (!strcmp(s, "guilds") || !strcmp(s, "g"))
        show_table("Guild");
    else if (!strcmp(s, "channels") || !strcmp(s, "c"))
        show_table("Kanal");
    else if (!strcmp(s, "guildmem") || !strcmp(s, "gm"))
        show_table("Clan_Guilda");
    else if (!strcmp(s, "channelmem") || !strcmp(s, "cm"))
        show_table("Clan_Kanala");
    else if (!strcmp(s, "bans") || !strcmp(s, "b"))
        show_table("Ban");
    else if (!strcmp(s, "emoji") || !strcmp(s, "e"))
        show_table("Emoji");
    else if (!strcmp(s, "tasks") || !strcmp(s, "t"))
        show_table("Zadatak");
    else if (!strcmp(s, "log") || !strcmp(s, "l"))
        show_table("Log");
    else if (!strcmp(s, "gcfg") || !strcmp(s, "c"))
        show_table("Konfiguracija_Servera");
    else
        printf("?");
}


void delguild(char **parsed_data)
{
    unsigned long long gid = parse_id(parsed_data[1]);
    if (gid == 0) {
        invalid_argument("gid");
        return;
    }

    char query[512];
    sprintf(query, "DELETE FROM Guild WHERE gid = %llu;", gid);
    if (execute_query(query))
        printf("Obrisan guild %llu\n", gid);
}


void addguildmember(char **parsed_data)
{
    unsigned long long uid = parse_id(parsed_data[1]);
    unsigned long long gid = parse_id(parsed_data[2]);
    if (uid == 0) {
        invalid_argument("uid");
        return;
    }
    if (gid == 0) {
        invalid_argument("gid");
        return;
    }

    char query[512];
    sprintf(query, "INSERT INTO Clan_Guilda VALUES (%llu, %llu, DEFAULT, DEFAULT)", uid, gid);
    if (execute_query(query))
        printf("Dodat uid %llu kao clan guilda %llu\n", uid, gid);
}


void addchannelmember(char **parsed_data)
{
    unsigned long long uid = parse_id(parsed_data[1]);
    unsigned long long cid = parse_id(parsed_data[2]);
    if (uid == 0) {
        invalid_argument("uid");
        return;
    }
    if (cid == 0) {
        invalid_argument("cid");
        return;
    }

    char query[512];
    sprintf(query, "INSERT INTO Clan_Kanala VALUES (%llu, (SELECT guild_gid FROM Kanal WHERE cid = %llu), %llu, DEFAULT)", uid, cid, cid);
    if (execute_query(query))
        printf("Dodat uid %llu kao clan kanala %llu\n", uid, cid);
}


void updmember(char **parsed_data)
{
    unsigned long long uid = parse_id(parsed_data[1]);
    unsigned long long gid = parse_id(parsed_data[2]);
    unsigned perms = (char)parse_id(parsed_data[3]);
    if (uid == 0) {
        invalid_argument("uid");
        return;
    }
    if (gid == 0) {
        invalid_argument("gid");
        return;
    }
    if (perms == 0) {
        invalid_argument("perms");
        return;
    }

    char query[512];
    sprintf(query, "UPDATE Clan_Guilda SET prilagodjene_permisije = %d WHERE korisnik_uid = %llu AND guild_gid = %llu", perms, uid, gid);
    if (execute_query(query))
        printf("Postavljene permisije za uid %llu u guildu %llu na %u (%#04x)\n", uid, gid, perms, perms);
}


void ban(char **parsed_data, int argc)
{
    unsigned long long uid = parse_id(parsed_data[1]);
    unsigned long long gid = parse_id(parsed_data[2]);
    unsigned long long auid = parse_id(parsed_data[3]);
    if (uid == 0) {
        invalid_argument("uid");
        return;
    }
    if (gid == 0) {
        invalid_argument("gid");
        return;
    }
    if (auid == 0) {
        invalid_argument("autor_uid");
        return;
    }

    char query[512];
    char comment[512] = "";
    if (argc < 4)
        sprintf(query, "INSERT INTO Ban VALUES (%llu, %llu, %llu, DEFAULT, DEFAULT)", uid, gid, auid);
    else if (argc < 5)
        sprintf(query, "INSERT INTO Ban VALUES (%llu, %llu, %llu, %s, DEFAULT)", uid, gid, auid, parsed_data[3]);
    else {
        for (int i = 4; i < argc; i++) {
            strcat(comment, parsed_data[i]);
            strcat(comment, " ");
        }
        sprintf(query, "INSERT INTO Ban VALUES (%llu, %llu, %llu, %s, %s)", uid, gid, auid, parsed_data[3], parsed_data[4]);
    }

    if (execute_query(query))
        printf("Banovan uid %llu iz guilda %llu (vreme uklanjanja bana: %s) od strane %llu (razlog: %s)\n", uid, gid, (argc < 4 ? "permanent ban" : parsed_data[3]), auid, (argc < 5 ? "nema" : comment));
}


void unban(char **parsed_data)
{
    unsigned long long uid = parse_id(parsed_data[1]);
    unsigned long long gid = parse_id(parsed_data[2]);
    if (uid == 0) {
        invalid_argument("uid");
        return;
    }
    if (gid == 0) {
        invalid_argument("gid");
        return;
    }

    char query[512];
    sprintf(query, "DELETE FROM Ban WHERE banovani_uid = %llu AND guild_gid = %llu", uid, gid);
    if (execute_query(query))
        printf("Unbanovan uid %llu iz guilda %llu\n", uid, gid);
}


void nickname(char **parsed_data)
{
    unsigned long long uid = parse_id(parsed_data[1]);
    if (uid == 0) {
        invalid_argument("uid");
        return;
    }

    char query[512];
    sprintf(query, "UPDATE Korisnik SET prilagodjeno_ime = '%s' WHERE uid = %llu", parsed_data[2], uid);
    if (execute_query(query))
        printf("Postavljeno ime za uid %llu na %s\n", uid, parsed_data[2]);
}


void guildconfig(char **parsed_data)
{
    unsigned long long gid = parse_id(parsed_data[1]);
    unsigned long long wcid = parse_id(parsed_data[2]);
    unsigned long long lcid = parse_id(parsed_data[3]);
    int antispam = (int)parse_id(parsed_data[4]);
    int antiflood= (int)parse_id(parsed_data[5]);
    if (gid == 0) {
        invalid_argument("gid");
        return;
    }
    if (antispam != 0 && antispam != 1) {
        invalid_argument("antispam");
        return;
    }
    if (antiflood != 0 && antiflood != 1) {
        invalid_argument("antiflood");
        return;
    }

    char query[512];
    sprintf(query, "UPDATE Konfiguracija_Servera SET welcome_cid = %llu, leave_cid = %llu, antispam_aktivan = %d, antiflood_aktivan = %d WHERE guild_gid = %llu", wcid, lcid, antispam, antiflood, gid);
    if (execute_query(query))
        printf("Izmenjena konfiguracija za gid `%llu` (wcid: %llu, lcid: %llu, antispam: %d, antiflood: %d)", gid, wcid, lcid, antispam, antiflood);
}


void q(char **parsed_data, int arg_c)
{
    char query[512] = "\0";
    for (int i = 1; i < arg_c; i++) {
        strcat(query, parsed_data[i]);
        strcat(query, " ");
    }

    if (!execute_query(query))
        printf("Query nije validan.");
}
