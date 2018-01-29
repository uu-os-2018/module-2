#include "parser.h"

#include <stdlib.h> // EXIT_FAILURE
#include <stdio.h>  // printf()
#include <string.h> // strlen()
#include <ctype.h>  // isspace(),
#include <string.h> // strtok_r()
#include <stdbool.h>

bool empty(char* str) {
  while (*str) {
    if (!isspace(*str++))
      return false;
  }
  return true;
}


/**
 *  Strip whitespace (tabs, spaces, etc) from the beginning of a
 *  string.
 *
 */
char* ltrim(char* s) {
  while (isspace((int)*s)) ++s;
  return s;
}

/**
 *  Strip whitespace (tabs, spaces, etc) from the end of a
 *  string.
 */
char* rtrim(char* str) {
  if(*str == 0 )
    return str;
  else {
    char* back = str + strlen(str)-1;  // Pointer to last char in str.

    while( isspace( *back) ) back--;   // While trailing whitespace move pointer-

    *(back+1) = 0; // Done, add terminating '\0'.

    return str;

  }
}

/**
 *  Strip whitespace (tabs, spaces, etc) from the beginning and the
 *  end of a string.
 */
char* trim(char* str) {
  if (str != NULL)
    return(ltrim(rtrim(str)));
  else return NULL;
}


void get_argv(char* str, const char* delim, char* argv[]) {

  char *token;
  int i = 0;
  
  /* get the first token */
  token = strtok(str, delim);

  /* walk through other tokens */
  while( token != NULL ) {
    argv[i] = token;
    token = strtok(NULL, delim);
    i++;
  }
  argv[i] = NULL;
}

void print_argv(char* argv[]) {
  int i = 0;
  char* s;

  while ((s = argv[i])) {
    printf("  argv[%d] = %s\n", i, s);
    i++;
  }
}


void print_argvs(char* argvs[MAX_COMMANDS][MAX_ARGV]) {
  int i = 0;
  while (argvs[i][0]) {
    printf("Command %d\n", i);
    print_argv(argvs[i]);
    i++;
  } 
}

void parse_cmds(char* str, const char* delim, char* cmds[]) {

  char *token;
  int i = 0;
  
  /* get the first token */
  token = strtok(str, delim);

  /* walk through other tokens */
  while( token != NULL ) {
    if (empty(token)) {
      fprintf(stderr, "Parser error: EMPTY command!\n");
      exit(EXIT_FAILURE);
    }

    cmds[i] = trim(token);
    token = strtok(NULL, delim);
    i++;
  }
  cmds[i] = NULL;
}

int parse(char *str, char* argvs[MAX_COMMANDS][MAX_ARGV]) {

  char* cmds[MAX_COMMANDS];

  parse_cmds(str, "|", cmds);

  int i = 0;

  while (cmds[i]) {
    get_argv(cmds[i], " ", argvs[i]);
    i++;
  }

  argvs[i][0] = NULL;
  return i;
}

