#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>


int main(int argc, char** argv) {
  char* p_end;
  char* p_end2;

  int pages = strtol(argv[1], &p_end, 10);
  int trials = strtol(argv[2], &p_end2, 10);
  int page_size = getpagesize();


  int jump = page_size / sizeof(int);

  int arr[pages * jump];

  // printf("pages: %d, trials: %d, array size: %lu\n", pages, trials, pages * jump);

  struct timeval current_time;
  gettimeofday(&current_time, NULL);

  for (int i = 0; i < trials; i++) {
    for (int j = 0; j < pages * jump; j += jump) {
      arr[j] = 1;    
    }
  }

  struct timeval current_time2;
  gettimeofday(&current_time2, NULL);

  int time1 = current_time.tv_sec * 1000000 + current_time.tv_usec;
  int time2 = current_time2.tv_sec * 1000000 + current_time2.tv_usec;

  double trial = ((double)time2 - (double)time1) / (double)trials / (double)(pages * jump);;

  printf("%.10f\n", trial);
}
