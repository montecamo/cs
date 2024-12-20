https://csapp.cs.cmu.edu/
https://www.cs.cmu.edu/~213/

#book
https://cmu.primo.exlibrisgroup.com/discovery/delivery/01CMU_INST:01CMU/12295179970004436

# Data lab undefined behavior...

```c
int isLessOrEqual(int x, int y) {
  int sum = ~x + 1 + y;
  int msb = (sum >> 31) & 0x1;

  printf("ma digit %d\n", !msb); // works if printf is removed, wtf?

  return !((sum >> 31) & 0x1);
}

int isLessOrEqual(int x, int y) {
  int sum = ~x + 1 + y;
  int msb = (sum >> 31) & 0x1;

  return !((sum >> 31) & 0x1); // !msb not working, wtf?
}
```
