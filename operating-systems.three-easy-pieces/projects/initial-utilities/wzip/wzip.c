#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// state
// 0 - parsing
// 1 - counting
void write_line(char* line) {
  int state = 0;
  int count = 0;
  char prev;

  for (int i = 0, len = strlen(line); i < len; i++) {
    char symbol = line[i];
    // printf("symbol: %c, state: %d\n", symbol, state);

    switch(state) {
      case 0:
        if (prev == symbol) {
          state = 1;
          count = 2;
        } else {
          prev = line[i];
        }
        break;

      case 1: 
        if (prev == symbol && i < len - 1) {
          count++;
        } else {
          count++;
          // printf("fwrite\n");
          fwrite(&count, 4, 1, stdout);
          fwrite(&prev, 1, 1, stdout);
          prev = line[i];
          count = 0;
          state = 0;
        }
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc == 1) { 
    printf("wzip: file1 [file2 ...]\n");
    exit(1);
  }

  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");

    if (fp == NULL) {
      printf("wzip: cannot open file\n");
      exit(1);
    }

    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;

    while ((linelen = getline(&line, &linecap, fp)) > 0) {
      write_line(line);
    }

    fclose(fp); 
  }

  return 0;
}
