#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command_handler.h"
#include "database.h"
#include "helpers.h"


int main(int argc, char** argv)
{
    if (argc != 4)
        error("Usage: ./program <host> <korisnik> <lozinka>");

    connect_to_db(argv[1], argv[2], argv[3], "pbp_gfdb");

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
