#ifndef _H_COMMAND_HANDLER_H_
#define _H_COMMAND_HANDLER_H_

void process_command(char **parsed_data, int arg_c);
void show(const char *s);
void delguild(char **parsed_data);
void addguildmember(char **parsed_data);
void addchannelmember(char **parsed_data);
void updmember(char **parsed_data);
void ban(char **parsed_data, int indefinite);
void unban(char **parsed_data);
void nickname(char **parsed_data);
void guildconfig(char **parsed_data);
void q(char **parsed_data, int arg_c);
void help();

#endif
