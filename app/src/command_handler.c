#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command_handler.h"


void process_command(char **parsed_data, int arg_c)
{
    if (!strcmp(parsed_data[0], "exit")) {
        exit(EXIT_SUCCESS);
    } else if (!strcmp(parsed_data[0], "delguild")) {
        delguild(parsed_data);
    } else if (!strcmp(parsed_data[0], "addmember")) {
        addmember(parsed_data);
    } else if (!strcmp(parsed_data[0], "updmember")) {
        updmember(parsed_data);
    } else if (!strcmp(parsed_data[0], "ban")) {
        ban(parsed_data);
    } else if (!strcmp(parsed_data[0], "unban")) {
        unban(parsed_data);
    } else if (!strcmp(parsed_data[0], "nickname")) {
        nickname(parsed_data);
    } else if (!strcmp(parsed_data[0], "q")) {
        q(parsed_data);
    } else {
        printf("Unknown command.");
    }
}


void delguild(char **parsed_data)
{
    printf("delguild");
}

void addmember(char **parsed_data)
{
    printf("addmember");
}


void updmember(char **parsed_data)
{
    printf("updmember");
}


void ban(char **parsed_data)
{
    printf("ban");
}


void unban(char **parsed_data)
{
    printf("unban");
}


void nickname(char **parsed_data)
{
    printf("nickname");
}


void q(char **parsed_data)
{
    printf("q");
}
