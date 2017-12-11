#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

void process_command(char **parsed_data, int arg_c);


int main()
{
    char line[512];

    while (1) {
        printf("> ");
        if (fgets(line, 512, stdin) == NULL)
            continue;
        int arg_c;
        char **parsed_data = parse(line, &arg_c);
        process_command(parsed_data, arg_c);
        printf("\n");
        free(parsed_data);
    }

    exit(EXIT_SUCCESS);
}



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
