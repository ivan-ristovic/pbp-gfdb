#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "helpers.h"
#include "database.h"


char** parse(char *str, int *arg_c)
{
    char **res = NULL;
    int n = 0;

    char *split_word = strtok (str," \t\n");
    while (split_word != NULL) {
        n++;
        res = realloc(res, n * sizeof(char*));
        if (res == NULL)
            error("realloc() failed.");
        res[n-1] = strdup(split_word);
        if (res[n-1] == NULL)
            error("strdup() failed.");
        split_word = strtok (NULL, " \t\n");
    }

    *arg_c = n;
    return res;
}


unsigned long long parse_id(const char *s)
{
    char *endptr;
    long long id = strtoll(s, &endptr, 10);
    if (*s != '\0' && *endptr == '\0' && id > 0ll)
        return (unsigned long long)(id);
    else
        return 0llu;
}


int is_empty(const char *s) {
    while (*s != '\0') {
        if (!isspace((unsigned char)*s))
            return 0;
        s++;
    }
    return 1;
}


void print_help()
{
    printf(
        " Komande:\n"
        " - show users/guilds/channels/bans/log/guildmem/channelmem/emoji/tasks/gcfg\n"
        "\tPrikazuje odgovarajucu tabelu.\n"
        " - delguild <gid>\n"
        "\tBrisanje servera iz baze, kao i svih njegovih kanala, filtera, emotikona itd.\n"
        " - addguildmember <uid> <gid>\n"
        "\tDodaje korisnika u tabelu Clan_Guilda.\n"
        " - addchannelmember <uid> <cid>\n"
        "\tDodaje korisnika u tabelu Clan_Kanala.\n"
        " - updmember <uid> <gid> <perms>\n"
        "\tUpdatuje permisije korisnika u guildu (perms mora biti u opsegu [0-127]).\n"
        " - ban <uid> <gid> <autor_gid> [timestamp] [reason]\n"
        "\tDodaje ban za dati uid i vreme trajanja.\n"
        " - unban <uid> <gid>\n"
        "\tUklanja uid ban za guild sa datim gid-om.\n"
        " - nickname <uid> <name>\n"
        "\tDodaje novo prilagodjeno ime korisniku.\n"
        " - guildconfig <gid> <wcid> <lcid> <antispam> <antiflood>\n"
        "\tMenja guild konfiguraciju (wcid - welcome kanal id, lcid - leave kanal id, antispam i antiflood su boolean vrednosti).\n"
        " - query <SQL upit>\n"
        "\tIzvrsava dati SQL upit.\n"
    );
}


void error(const char * msg)
{
    perror(msg);
    clean_up_and_exit(EXIT_FAILURE);
}


void invalid_argument(const char *msg)
{
    printf("Argument nije moguce konvertovati u validnu vrednost: `%s`", msg);
}


void clean_up_and_exit(int excode)
{
    close_db_connection();
    printf("Izlaz...\n");
    exit(excode);
}
