#include "stdio.h"

int main(int argc, char *argv[]) {
  char buff[50];

  if (argc < 2) {
    return 0;
  }

  for (int i = 1; i < argc; i++) {
    FILE *ptr = fopen(argv[i], "r");

    if (ptr == NULL) {
      printf("wcat: cannot open file\n");
      return 1;
    }

    while (fgets(buff, 50, ptr) != NULL) {
      printf("%s", buff);
    }

    fclose(ptr);
  }

  return 0;
}
