#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command_handler.h"
#include "database.h"
#include "helpers.h"

#define GLOBAL_DEBUG


int main()
{
    connect_to_db("localhost", "root", "enigma", "pbp_gfdb");

    print_help();

    char line[512];
    while (1) {
        printf("\n> ");
        if (fgets(line, 512, stdin) == NULL || is_empty(line))
            continue;
        int arg_c;
        char **parsed_data = parse(line, &arg_c);
        process_command(parsed_data, arg_c);
        for (int i = 0; i < arg_c; i++)
            free(parsed_data[i]);
        free(parsed_data);
    }

    clean_up_and_exit(EXIT_SUCCESS);
}
