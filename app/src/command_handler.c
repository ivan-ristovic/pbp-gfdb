#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "command_handler.h"
#include "database.h"


void process_command(char **parsed_data, int arg_c)
{
    if (!strcmp(parsed_data[0], "exit")) {
        exit(EXIT_SUCCESS);
    } else if (!strcmp(parsed_data[0], "delguild") || !strcmp(parsed_data[0], "dg")) {
        if (arg_c >= 2)
            delguild(parsed_data);
        else
            printf("Not enough arguments provided for command: delguild");
    } else if (!strcmp(parsed_data[0], "addmember") || !strcmp(parsed_data[0], "am")) {
        if (arg_c >= 3)
            addmember(parsed_data);
        else
            printf("Not enough arguments provided for command: addmember");
    } else if (!strcmp(parsed_data[0], "updmember") || !strcmp(parsed_data[0], "um")) {
        if (arg_c >= 4)
            updmember(parsed_data);
        else
            printf("Not enough arguments provided for command: updmember");
    } else if (!strcmp(parsed_data[0], "ban") || !strcmp(parsed_data[0], "b")) {
        if (arg_c >= 3)
            ban(parsed_data, arg_c == 3);
        else
            printf("Not enough arguments provided for command: ban");
    } else if (!strcmp(parsed_data[0], "unban") || !strcmp(parsed_data[0], "ub")) {
        if (arg_c >= 2)
            unban(parsed_data);
        else
            printf("Not enough arguments provided for command: unban");
    } else if (!strcmp(parsed_data[0], "nickname") || !strcmp(parsed_data[0], "nick")) {
        if (arg_c >= 3)
            nickname(parsed_data);
        else
            printf("Not enough arguments provided for command: nickname");
    } else if (!strcmp(parsed_data[0], "query") || !strcmp(parsed_data[0], "q")) {
        if (arg_c >= 2)
            q(parsed_data, arg_c);
        else
            printf("Not enough arguments provided for command: q");
    } else if (!strcmp(parsed_data[0], "help") || !strcmp(parsed_data[0], "h")) {
        print_help();
    } else {
        printf("Unknown command.");
    }
}


void delguild(char **parsed_data)
{
    unsigned long long gid = parse_id(parsed_data[1]);
    if (gid == 0) {
        invalid_argument("gid");
        return;
    }
    printf("Deleted guild `%llu`", gid);
}


void addmember(char **parsed_data)
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
    printf("Added uid `%llu` as member of guild `%llu`", uid, gid);
}


void updmember(char **parsed_data)
{
    unsigned long long uid = parse_id(parsed_data[1]);
    unsigned long long gid = parse_id(parsed_data[2]);
    unsigned char perms = (char)parse_id(parsed_data[2]);
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
    printf("Set permission bytes for uid `%llu` in guild `%llu` to `%#04x`", uid, gid, perms);
}


void ban(char **parsed_data, int indefinite)
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
    printf("Banned uid `%llu` from guild `%llu` until `%s`", uid, gid, (indefinite ? "indefinite" : parsed_data[3]));
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
    printf("Unbanned uid %llu from guild %llu", uid, gid);
}


void nickname(char **parsed_data)
{
    unsigned long long uid = parse_id(parsed_data[1]);
    if (uid == 0) {
        invalid_argument("uid");
        return;
    }
    printf("Changed nickname for uid `%llu` to `%s`", uid, parsed_data[2]);
}


void q(char **parsed_data, int arg_c)
{
    char query[512] = "\0";
    for (int i = 1; i < arg_c; i++) {
        strcat(query, parsed_data[i]);
        strcat(query, " ");
    }
    execute_query(query);
}
