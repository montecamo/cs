#include "stdio.h"

int main(int argc, char** argv) {
  if (argc == 1) {
    printf("wunzip: file1 [file2 ...]\n");
    return 1;
  }

  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");

    if (fp == NULL) {
      printf("error\n"); 
      return 1;
    }

    char letter;
    int count;
    while (fread(&count, 4, 1, fp) > 0 && fread(&letter, 1, 1, fp) > 0) {
      for (int i = 0; i < count; i++) {
        printf("%c", letter);
      }
    }

    fclose(fp);
  }

  return 0;
}
