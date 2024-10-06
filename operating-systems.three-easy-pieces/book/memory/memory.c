#include "stdlib.h"
#include "inttypes.h"

int main(int argc, char** argv) {
  char* p_end;
  int megabytes = strtol(argv[1], &p_end, 10);

  if (megabytes == 0 || argv[1] == p_end) {
    exit(1);
  }

  int bytes = megabytes * 1024 * 1024;
  
  char* memory = malloc(megabytes * 1024 * 1024);

  while(1) {
    int kek;
    for (int i = 0; i < bytes; i++) {
      kek = memory[i];
    }
  }
}
