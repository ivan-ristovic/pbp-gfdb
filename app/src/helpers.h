#ifndef _H_HELPERS_H
#define _H_HELPERS_H

char** parse(char *str, int *arg_c);
int is_empty(const char *s);
unsigned long long parse_id(const char *s);
void print_help();
void error(const char *msg);
void invalid_argument(const char *msg);
void clean_up_and_exit();

#endif
