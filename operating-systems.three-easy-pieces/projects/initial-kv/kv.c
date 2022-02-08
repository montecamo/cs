#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "store.txt"

void panic() {
  printf("Something went completely wrong\n");
  exit(1);
}

struct database {
  int size;
  char** data;
};

struct database addEntry(struct database db, int index, char* value) {
  if (index + 1 > db.size) {
    db.data = realloc(db.data, sizeof(char*) * index);

    if (db.data == NULL) {
      panic();
    }

    db.size = index + 1;
  }

  db.data[index] = value;

  return db;
}

struct database load() {
  struct database db; 
  db.size = 0;
  db.data = malloc(sizeof(char*));

  FILE* ptr = fopen(FILENAME, "r");

  if (ptr == NULL) {
    return db;
  }

  char* line = NULL;
  size_t linecap = 0;
  ssize_t linelen;
  while ((linelen = getline(&line, &linecap, ptr)) > 0) {
    char* key = strsep(&line, ",");
    char* value = strsep(&line, ",");

    if (key != NULL && value != NULL) {
      int index = atoi(key); 

      db = addEntry(db, index, strdup(value));
    }
  }

  return db;
}

void save(struct database db) {
  FILE* ptr = fopen(FILENAME, "w");

  if (ptr == NULL) panic();

  for (int i = 0; i < db.size; i++) {
    char* entry = db.data[i];

    if (entry != NULL) {
      fprintf(ptr, "%d,%s", i, entry);
    }
  }
}

void print(struct database db) {
  for (int i = 0; i < db.size; i++) {
    char* entry = db.data[i];

    if (entry != NULL) {
      printf("%d,%s\n", i, entry);
    }
  }
}

int main(int argc, char** argv) {
  struct database db = load();     

  for (int i = 1; i < argc; i++) {
    char* command = strsep(&argv[i], ",");
    int index = atoi(strsep(&argv[i], ","));
    char* value = strsep(&argv[i], ",");

    if (strcmp(command, "p") == 0) {
      db = addEntry(db, index, strdup(value));
    } else if (strcmp(command, "g") == 0) {
      if (db.data[index] != 0) {
        printf("%d,%s\n", index, db.data[index]);
      } else {
        printf("%d not found\n", index);
      }
    } else if (strcmp(command, "c") == 0) {
      db.data = malloc(0);
      db.size = 0;
    } else if (strcmp(command, "d") == 0) {
      if (db.data[index] != 0) {
        db.data[index] = 0;
      } else {
        printf("%d not found\n", index);
      }
    } else if (strcmp(command, "a") == 0) {
      print(db); 
    } else {
      printf("bad command\n");
    }
  }

  save(db);
}
