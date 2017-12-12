#include <stdio.h>
#include <mysql.h>
#include "database.h"
#include "helpers.h"


MYSQL *_db = NULL;


void connect_to_db(const char *host, const char *user, const char *pass, const char *db)
{
    _db = mysql_init(NULL);
    if (!mysql_real_connect(_db, host, user, pass, db, 0, NULL, 0))
        error(mysql_error(_db));
    printf("Database connection established.\n");
}


int execute_query(const char *query)
{
    if (_db == NULL || mysql_query(_db, query))
        return 0;

    MYSQL_RES *res = mysql_use_result(_db);

    int col_num = mysql_num_fields(res);

    print_border(col_num);

    // Header
    MYSQL_FIELD *field = mysql_fetch_field(res);
    printf("| ");
    for (int i = 0; i < col_num; i++)
        printf("%20s | ", field[i].name);
    putchar('\n');

    print_splitter(col_num);

    // Rows
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)) != 0) {
        printf("| ");
        for (int i = 0; i < col_num; i++)
            printf("%20.*s | ", 20, row[i]);
        putchar('\n');
    }

    print_border(col_num);

    mysql_free_result(res);
    return 1;
}


void print_splitter(int col_num)
{
    printf("|");
    for (int i = 0; i < col_num; i++)
        printf("----------------------|");
    printf("\n");
}


void print_border(int col_num)
{
    printf("+");
    for (int i = 0; i < col_num; i++)
        printf("-----------------------");
    printf("+\n");
}
