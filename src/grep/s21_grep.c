#include "s21_grep.h"
int ch = 0;
int e_count = 0;
char* optstring = "e:ivclnhsf:o";

void set_flag(int argc, char* argv[], struct flags* flag, char* ef_arg) {
  while ((ch = getopt_long(argc, argv, optstring, NULL, NULL)) != -1) {
    switch (ch) {
      case 'e':
        flag->e = 1;
        pattern_e(optarg, &e_count, ef_arg, flag);
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'f':
        flag->f = 1;
        regexes_file_f(optarg, &e_count, ef_arg, flag);
        break;
      case 'o':
        flag->o = 1;
        break;
      case '?':
        exit(1);
      default:
        break;
    }
  }
  if (flag->empty_line) flag->o = 0;
}
//-e
void pattern_e(char* optarg, int* e_count, char* ef_arg, struct flags* flag) {
  // If this is not the first search pattern, add a '|' separator
  if (*e_count > 0) {
    strcat(ef_arg, "|");
  }
  // If the search pattern is empty, set it to '.'
  if (*optarg == '\0') {
    optarg = ".";
    flag->empty_line++;
  }
  // Append the search pattern to the ef_arg string
  size_t len = strlen(optarg);
  strncat(ef_arg, optarg, len);
  // Increment the count of search patterns
  *e_count += 1;
}
// f
void regexes_file_f(char* optarg, int* e_count, char* ef_arg,
                    struct flags* flag) {
  FILE* fp_f = NULL;
  char line[STR_BUFFER] = {0};
  // Open the file specified by the -f option
  if ((fp_f = fopen(optarg, "r")) == NULL) {
    printf("grep: %s: No such file or directory\n", optarg);
    exit(2);
  } else {
    // Read each line from the file and add it to the search pattern
    while (fgets(line, STR_BUFFER, fp_f) != NULL) {
      // Remove the newline character if present
      if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = 0;

      // If this is not the first search pattern, add a '|' separator
      if (*e_count > 0) strcat(ef_arg, "|");

      // If the line is empty, set it to '.' and increment empty_line field
      if (*line == '\0') {
        flag->empty_line = 1;
        strcat(ef_arg, ".");
      } else {
        // Append the line to the ef_arg string
        strcat(ef_arg, line);
      }
    }

    // Close the file
    fclose(fp_f);
  }
}
void file_read(int argc, char* argv[], char* ef_arg, struct flags flag) {
  FILE* fp;                         // file pointer
  int files_count = argc - optind;  // count of files to search

  // Loop through the remaining command line arguments
  for (; optind < argc; optind++) {
    // Open the file
    if ((fp = fopen(argv[optind], "r")) == NULL) {
      // If the file cannot be opened and the -s option is not set, print an
      // error message
      if (flag.s == 0) {
        printf("grep: %s: No such file or directory\n", argv[optind]);
      }
    } else {
      // Compile the regular expression and search for matches in the file
      searche(argv, ef_arg, fp, flag, files_count);
      // Close the file
      fclose(fp);
    }
  }
}
void searche(char** argv, char* my_reg, FILE* fp, struct flags flag,
             int files_count) {
  // Declare variables for regular expression matching
  regex_t myre;
  regmatch_t pmatch[1] = {0};
  size_t nmatch = 1;
  // Declare variables for error handling
  int err;
  char err_msg[MAX_ERR_LENGTH];
  // Declare variables for reading input from file
  char str[STR_BUFFER];
  size_t n_line = 1;
  int lines_count = 0;
  // Declare a variable for the REG_ICASE option
  int i_option = 0;
  if (flag.i != 0) {
    // If the -i option is set, use the REG_ICASE option to make the search
    // case-insensitive
    i_option = REG_ICASE;
  }
  err = regcomp(
      &myre, my_reg,
      REG_EXTENDED | i_option);  // Compile the regular expression in my_reg

  if (err != 0) {
    // If there is an error compiling the regular expression, print an error
    // message and exit the program
    regerror(err, &myre, err_msg, MAX_ERR_LENGTH);
    printf("Error analyzing regular expression '%s': %s.\n", my_reg, err_msg);
    exit(3);
  }
  // Read each line from the file and search for matching lines
  while (feof(fp) == 0) {  // feof(fp) returns a non-zero value if the end of
                           // the file has been reached
    if (fgets(str, STR_BUFFER, fp)) {
      int new_line_o_counter = 1;
      // Search for a match in the current line using the compiled regular
      // expression
      err = regexec(&myre, str, nmatch, pmatch, 0);
      // If the -v option is set, invert the match result
      if (flag.v != 0) {
        err = err ? 0 : 1;
      }
      if (err == 0) {
        // If a match is found, print the line with any additional information
        // specified by the command line options
        if (flag.c == 0 && flag.l == 0) {
          if (files_count > 1 && flag.h == 0) {
            printf("%s:", argv[optind]);
          }
          if (flag.n != 0) {
            printf("%lu:", n_line);  //-n تنسيق عدد صحيح طويل10:matching line
          }
          if (flag.o != 0 && flag.v == 0) {
            // If the -o option is set, print only the matched substrings
            new_line_o_counter = 0;
            char* ptr = str;
            while (err == 0) {
              if (pmatch[0].rm_eo == pmatch[0].rm_so) {
                break;
              }
              printf("%.*s\n",
                     (int)(pmatch[0].rm_eo  //هو محدد تنسيق يستخدم لطباعة سلسلة
                                            //بطول محددvariable width specifier
                           - pmatch[0].rm_so),
                     ptr + pmatch[0].rm_so);
              ptr += pmatch[0].rm_eo;
              err = regexec(&myre, ptr, nmatch, pmatch, REG_NOTBOL);
            }
          }
          if (!flag.o || flag.v) {
            // If the -o option is not set or the -v option is set, print the
            // entire line
            printf("%s", str);
          }
          if (str[strlen(str) - 1] != '\n' && new_line_o_counter != 0) {
            // If the line does not end with a newline character, print one
            printf("\n");
          }
        }
        lines_count++;  // Increment the count of matching lines
      }
      // Increment the count of lines read from the file
      n_line++;
    }
  }
  // Print the search result summary if the -c or -l option is set
  if (flag.c != 0) {
    if (files_count > 1 && !flag.h) {
      printf("%s:", argv[optind]);
    }
    if (flag.l && lines_count) {
      // If the -l  is set, print the file name
      printf("1\n");
    } else {
      // Otherwise, print the count of matching lines
      printf("%d\n", lines_count);
    }
  }
  if (flag.l && lines_count) {
    // If the -l is set,print the file name
    printf("%s\n", argv[optind]);
  }
  regfree(&myre);  // Free the memory
}

int main(int argc, char* argv[]) {
  struct flags flag = {0};
  char ef_arg[MY_REG] = {
      0};  // character array to store the extended regular expression argument

  if (argc > 1) {
    set_flag(argc, argv, &flag, ef_arg);
    if (flag.e == 0 && flag.f == 0) {
      if (*argv[optind] == 0) argv[optind] = ".";
      strcat(ef_arg, argv[optind]);
      optind += 1;
    }
    file_read(argc, argv, ef_arg, flag);
  }
  return 0;
}
