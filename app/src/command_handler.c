#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "command_handler.h"


void process_command(const char **parsed_data, int arg_c)
{
    if (!strcmp(parsed_data[0], "exit")) {
        exit(EXIT_SUCCESS);
    } else if (!strcmp(parsed_data[0], "delguild")) {
        if (arg_c >= 2)
            delguild(parsed_data);
        else
            printf("Not enough arguments provided for command: delguild");
    } else if (!strcmp(parsed_data[0], "addmember")) {
        if (arg_c >= 3)
            addmember(parsed_data);
        else
            printf("Not enough arguments provided for command: addmember");
    } else if (!strcmp(parsed_data[0], "updmember")) {
        if (arg_c >= 4)
            updmember(parsed_data);
        else
            printf("Not enough arguments provided for command: updmember");
    } else if (!strcmp(parsed_data[0], "ban")) {
        if (arg_c >= 3)
            ban(parsed_data);
        else
            printf("Not enough arguments provided for command: ban");
    } else if (!strcmp(parsed_data[0], "unban")) {
        if (arg_c >= 2)
            unban(parsed_data);
        else
            printf("Not enough arguments provided for command: unban");
    } else if (!strcmp(parsed_data[0], "nickname")) {
        if (arg_c >= 3)
            nickname(parsed_data);
        else
            printf("Not enough arguments provided for command: nickname");
    } else if (!strcmp(parsed_data[0], "q")) {
        if (arg_c >= 2)
            q(parsed_data);
        else
            printf("Not enough arguments provided for command: q");
    } else if (!strcmp(parsed_data[0], "help")) {
        print_help();
    } else {
        printf("Unknown command.");
    }
}


void delguild(const char **parsed_data)
{
    printf("delguild");
}

void addmember(const char **parsed_data)
{
    printf("addmember");
}


void updmember(const char **parsed_data)
{
    printf("updmember");
}


void ban(const char **parsed_data)
{
    printf("ban");
}


void unban(const char **parsed_data)
{
    printf("unban");
}


void nickname(const char **parsed_data)
{
    printf("nickname");
}


void q(const char **parsed_data)
{
    printf("q");
}
