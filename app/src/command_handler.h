#ifndef _H_COMMAND_HANDLER_H_
#define _H_COMMAND_HANDLER_H_

void process_command(const char **parsed_data, int arg_c);
void delguild(const char **parsed_data);
void addmember(const char **parsed_data);
void updmember(const char **parsed_data);
void ban(const char **parsed_data);
void unban(const char **parsed_data);
void nickname(const char **parsed_data);
void q(const char **parsed_data);
void help();

#endif
