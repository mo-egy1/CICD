#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5000
char *fName[SIZE];
struct flags {
  int file;
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int btrack;
  int squeezes;
  int lookinput;
};

int handl_command_line(char **input, struct flags *flag);
void open_files(struct flags flag);
void set_values(struct flags *flag);
void read(FILE *file, struct flags *flag);
void stylee(char **input, struct flags *flag, int i);
void show(char ch, struct flags *flag);

#endif
