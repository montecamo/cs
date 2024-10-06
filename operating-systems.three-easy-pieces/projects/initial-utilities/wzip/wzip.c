#include "stdio.h"

void print(int number, char letter) {
  fwrite(&number, 4, 1, stdout);
  printf("%c", letter);
}

int main(int argc, char** argv) {
  if (argc == 1) {
    printf("wzip: file1 [file2 ...]\n");
    return 1;
  }

  int c;
  char prev = '\0';
  int count = 1;
  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");

    if (fp == NULL) {
      printf("error\n"); 
      return 1;
    }

    while ((c = fgetc(fp)) != EOF) {
      if (prev == '\0') {
        prev = c;
        continue;
      }

      if (prev != c) {
        print(count, prev);

        count = 1; 
        prev = c;
      } else {
        count++;
      }
    }


    fclose(fp);
  }

  print(count, prev);

  return 0;
}
