#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command_handler.h"


void process_command(char **parsed_data, int arg_c)
{
    if (!strcmp(parsed_data[0], "exit"))
        exit(EXIT_SUCCESS);
    else if (!strcmp(parsed_data[0], "delguild"))
        printf("delguild");
    else if (!strcmp(parsed_data[0], "addmember"))
        printf("addmember");
    else if (!strcmp(parsed_data[0], "updmember"))
        printf("updmember");
    else if (!strcmp(parsed_data[0], "ban"))
        printf("ban");
    else if (!strcmp(parsed_data[0], "unban"))
        printf("unban");
    else if (!strcmp(parsed_data[0], "nickname"))
        printf("nickname");
    else if (!strcmp(parsed_data[0], "q"))
        printf("q");
    else
        printf("Unknown command.");
}
