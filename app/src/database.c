
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include "database.h"
#include "helpers.h"


MYSQL *_db = NULL;


void connect_to_db(const char *host, const char *user, const char *pass, const char *db)
{
    _db = mysql_init(NULL);
    if (!mysql_real_connect(_db, host, user, pass, db, 0, NULL, 0))
        error(mysql_error(_db));

    #ifdef GLOBAL_DEBUG
        printf("Izvrsena konekcija na bazu.\n");
    #endif
}


int execute_query(const char *query)
{
    #ifdef GLOBAL_DEBUG
        printf("Izvrsavam query: %s\n", query);
    #endif

    if (_db == NULL || mysql_query(_db, query)) {
        printf("Greska prilikom izvrsavanja:\n%s\n", mysql_error(_db));
        return 0;
    }

    if (strcasestr(query, "select") == query)
        print_query_results();
    return 1;
}


void print_query_results()
{
    MYSQL_RES *res = mysql_use_result(_db);

    int col_num = mysql_num_fields(res);

    print_splitter(col_num);

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

    print_splitter(col_num);

    mysql_free_result(res);
}


void print_splitter(int col_num)
{
    printf("+");
    for (int i = 0; i < col_num; i++)
        printf("----------------------+");
    putchar('\n');
}


void show_table(const char *table)
{
    char query[512];
    sprintf(query, "SELECT * FROM %s", table);
    execute_query(query);
}


void close_db_connection()
{
    if (_db != NULL) {
        mysql_close(_db);
        _db = NULL;
        #ifdef GLOBAL_DEBUG
            printf("Zatvorena konekcija sa bazom.\n");
        #endif
    }
}
