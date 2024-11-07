#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_BUFFER 100000
#define MY_REG 10000
#define MAX_ERR_LENGTH 500

struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int empty_line;
};

void set_flag(int argc, char* argv[], struct flags* flag, char* ef_arg);
void pattern_e(char* optarg, int* e_count, char* ef_arg, struct flags*);
void regexes_file_f(char* optarg, int* e_count, char* ef_arg, struct flags*);

void file_read(int argc, char* argv[], char* ef_arg, struct flags flag);
void searche(char* argv[], char* my_reg, FILE* fp, struct flags flag,
             int files_count);

#endif  // SRC_GREP_S21_GREP_H_
