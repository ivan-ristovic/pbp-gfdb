#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"


int main()
{
    char line[512];

    while (1) {
        printf("> ");
        if (fgets(line, 512, stdin) == NULL || is_empty(line))
            continue;
        int arg_c;
        char **parsed_data = parse(line, &arg_c);
        process_command(parsed_data, arg_c);
        printf("\n");
        free(parsed_data);
    }

    exit(EXIT_SUCCESS);
}
