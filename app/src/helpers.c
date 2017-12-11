#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"


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

int is_empty(const char *s) {
    while (*s != '\0') {
        if (!isspace((unsigned char)*s))
            return 0;
        s++;
    }
    return 1;
}


void error(const char * msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
