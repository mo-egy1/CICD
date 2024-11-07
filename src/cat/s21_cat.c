#include "s21_cat.h"

//  initializes the given struct flags variable with default values.
void set_values(struct flags *flag) {
  // Use designated initializers to set the values of the struct members.
  *flag = (struct flags){
      .file = 0,
      .b = 0,
      .btrack = 0,  //-b
      .e = 0,
      .n = 0,
      .s = 0,
      .squeezes = 0,  //-s
      .t = 0,
      .v = 0,
      .lookinput = 0  //-v
  };
}

int handl_command_line(char **argv, struct flags *flag) {
  int error = 1;

  int j = 0;

  // Loop through the command line arguments, starting from index 1.
  for (int i = 1; argv[i]; i++) {
    if (argv[i][0] == '-' && argv[i][1] == '-') {
      // If an argument starts with --, call flag_GNU to handle GNU-style long
      // options.
      stylee(argv, flag, i);
    } else if (argv[i][0] == '-' && argv[i][1] != '-') {
      // If an argument starts with - but is not a long option, loop to set the
      // appropriate flags in the struct flags.
      for (int t = 1; argv[i][t]; t++) {
        if (argv[i][t] == 'b') {
          flag->b = 1;
        } else if (argv[i][t] == 'e') {
          flag->e = 1;
          flag->v = 1;
        } else if (argv[i][t] == 'n') {
          flag->n = 1;
        } else if (argv[i][t] == 's') {
          flag->s = 1;
        } else if (argv[i][t] == 't') {
          flag->t = 1;
          flag->v = 1;
        } else if (argv[i][t] == 'v') {
          flag->v = 1;
        } else if (argv[i][t] == 'E') {
          flag->e = 1;
        } else if (argv[i][t] == 'T') {
          flag->t = 1;
        } else {
          // If an invalid option is encountered, print an error message and set
          // error to 0.
          printf("s21_cat: invalid option -- '%c'\n", argv[i][t]);
          error = 0;
        }
      }
    } else {
      // If an argument is not a flag, it is assumed to be an input file name,
      // so set the file flag to 1 and add the file name to the fName array.
      flag->file = 1;
      fName[j] = argv[i];
      j++;
    }
  }
  // If the b flag is set, the n flag is automatically reset to 0, since the -b
  if (flag->b == 1) {
    flag->n = 0;
  }
  return error;
}

/*  handles GNU-style with long options*/
void stylee(char **argv, struct flags *flag, int i) {
  // Get the value of the argument at index i.
  const char *arg = argv[i];

  // Check the third character of the argument against the known long options
  switch (arg[2]) {
    // If the third character is 'b', set the b flag in the struct flags to 1.
    case 'b':
      flag->b = 1;
      break;

    case 'n':
      flag->n = 1;
      break;

    case 's':
      flag->s = 1;
      break;
    //  doesn't match er
    default:
      printf("s21_cat: invalid option -- '%s'\n", arg);
  }
}

/*reads*/
void read(FILE *file, struct flags *flag) {
  int ch;

  // Loop through the input file until the end of the file is reached.
  while ((ch = getc(file)) != EOF) {
    show((char)ch, flag);
  }
}

/*open*/
void open_files(struct flags flag) {
  for (int i = 0; fName[i]; i++) {
    FILE *file;
    file = fopen(fName[i], "r");
    if (file) {
      read(file, &flag);
      fclose(file);
    } else {
      printf("s21_cat: %s: No such file or directory\n", fName[i]);
    }
  }
}

void show(char ch, struct flags *flag) {
  int null_str = 0;

  // Handle the -s flag, which squeezes consecutive empty lines into one.
  if (flag->s == 1 && flag->squeezes == 0 && ch == '\n') {
    flag->squeezes += 1;
  } else if (flag->squeezes != 0 && ch == '\n') {
    flag->squeezes += 1;
    null_str = 1;
  } else if (flag->squeezes > 1 && ch != '\n') {
    flag->squeezes = 0;
    if (flag->e == 1) {
      printf("$");
    }
    printf("\n");
    if (flag->n != 0) {
      printf("%6d\t", flag->n);
      flag->n += 1;
    }
  } else {
    flag->squeezes = 0;
  }

  // Handle the -n, -b, and -E flags, which add line numbers, add line numbers
  // to non-empty lines, and add a $ to the end of each line, respectively.
  if (flag->n != 0 || flag->b != 0) {
    if (flag->lookinput == 1) {
      printf("%6d\t", flag->n);
      flag->n += 1;
      flag->lookinput = 0;
    }
    if (flag->n == 1) {
      printf("%6d\t", flag->n);
      flag->n += 1;
    }
    if (flag->b == 1) {
      printf("%6d\t", flag->b);
      flag->b += 1;
    }
    if (ch == '\n' && flag->n != 0 && null_str == 0) {
      flag->lookinput = 1;
    }
    if (ch == '\n' && flag->b != 0) {
      flag->btrack += 1;
    }
    if (ch != '\n' && flag->btrack != 0 && flag->squeezes == 0) {
      printf("%6d\t", flag->b);
      flag->btrack = 0;
      flag->b += 1;
    }
  }
  if (flag->e == 1 && ch == '\n' && null_str == 0) {
    printf("$");
  }

  // Handle the -v flag, which displays non-printing characters as ^ followed by
  // the corresponding printable character or ? for non-printable characters.
  if (flag->v == 1) {
    if (ch < 32 && ch != 9 && ch != 10) {
      printf("^");
      ch += 64;
    }
    if (ch == 127) {
      printf("^");
      ch = '?';
    }
  }

  // Handle the -t flag, which displays tabs as ^I.
  if (flag->t == 1 && ch == '\t') {
    printf("^");
    ch = 'I';
  }

  // Print the modified character to the standard output, unless it's a null
  // string (i.e., it's been squeezed due to the -s flag).
  if (null_str == 0) {
    printf("%c", ch);
  }
}

int main(int argc, char **argv) {
  // Declare a struct flags variable called flag and initialize it using the
  // EmptyCatStruct function.
  struct flags flag;
  set_values(&flag);

  if (argc > 0) {
    // Call the get_arg function to parse the arguments and set the appropriate
    // flags in the flag variable.
    if (handl_command_line(argv, &flag)) {
      // معالجة ملفات الإدخال..
      open_files(flag);
    }
  }

  return 0;
}
