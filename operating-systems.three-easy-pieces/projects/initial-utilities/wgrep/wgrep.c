#include "stdio.h"
#include "string.h"


int main(int argc, char **argv) {
  if (argc == 1) {
    printf("wgrep: searchterm [file ...]\n");
    return 1;
  }

  char *needle = argv[1];

  for (int i = 2; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");

    if (fp == NULL) {
      printf("wgrep: cannot open file\n");
      return 1;
    }

    char *line = NULL;
    size_t linecap = 0;

    while (getline(&line, &linecap, fp) > 0) {
      if (strstr(line, needle) != NULL) {
        printf("%s", line);
      }
    }

    fclose(fp);
  }

  if (argc == 2) {
    char *line = NULL;
    size_t linecap = 0;

    while (getline(&line, &linecap, stdin) > 0) {
      if (strstr(line, needle) != NULL) {
        printf("%s", line);
      }
    }
  }

  return 0;
}
