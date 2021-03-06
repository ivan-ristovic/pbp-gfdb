#ifndef _H_DATABASE_H
#define _H_DATABASE_H

#include <mysql.h>

#define GLOBAL_DEBUG

MYSQL *_db;

void connect_to_db( const char *host, const char *user, const char *pass, const char *db);
int execute_query(const char *query);
void print_query_results();
void print_splitter(int col_num);
void show_table(const char *table);
void close_db_connection();

#endif
