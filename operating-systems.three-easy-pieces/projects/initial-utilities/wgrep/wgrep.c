#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE (512)

void print_grep(FILE *fp, char *needle) {
  char *haystack = NULL;
  size_t linecap = 0;
  ssize_t linelen;

  while ((linelen = getline(&haystack, &linecap, fp)) > 0) {
    char *result = strstr(haystack, needle);
    if (result) {
      printf("%s", haystack);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("wgrep: searchterm [file ...]\n");
    exit(1);
  }

  char *needle = argv[1];

  for (int i = 2; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");

    if (fp == NULL) {
      printf("wgrep: cannot open file\n");
      exit(1);
    }

    print_grep(fp, needle);

    fclose(fp); 
  }

  if (argc == 2) {
    print_grep(stdin, needle);
  }

  return 0;
}
