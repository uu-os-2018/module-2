#ifndef PARSER_H_
#define PARSER_H_


#define MAX_COMMANDS 16
#define MAX_ARGV     16

int parse(char *str, char* argvs[MAX_COMMANDS][MAX_ARGV]);
void print_argv(char* argv[]);
void print_argvs(char* argvs[MAX_COMMANDS][MAX_ARGV]); 

#endif // PARSER_H_
