#ifndef _H_COMMAND_HANDLER_H_
#define _H_COMMAND_HANDLER_H_

void process_command(char **parsed_data, int arg_c);
void delguild(char **parsed_data);
void addmember(char **parsed_data);
void updmember(char **parsed_data);
void ban(char **parsed_data);
void unban(char **parsed_data);
void nickname(char **parsed_data);
void q(char **parsed_data);

#endif
