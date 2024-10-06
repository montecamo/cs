#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"

char** PATH;

void panic() {
  char error_message[30] = "An error has occurred\n";
  write(STDERR_FILENO, error_message, strlen(error_message)); 
}

char* trim_left(char* string) {
  for (int i = 0; i < strlen(string); i++) {
    if (string[i] != ' ' && string[i] != '\n') {
      return &string[i];
    }
  }

  return string;
}

char* trim_right(char* string) {
  for (int i = strlen(string) - 1; i >= 0; i--) {
    if (string[i] == ' ' || string[i] == '\0' || string[i] == '\n') {
      string[i] = '\0';
    } else {
      return string;
    }
  }

  return string;
}

char** parse_input(char* input, char* delim) {
  char *token;
  char **tokens = malloc(sizeof(NULL));
  int i = 0;

  while ((token = strsep(&input, delim)) != NULL) {
    i++;

    tokens = realloc(tokens, i * sizeof(char*) + sizeof(NULL));

    tokens[i - 1] = strdup(trim_right(trim_left(token)));
  }

  tokens[i] = NULL;

  return tokens;
}

char* find_program(char* program) {
  for (int i = 0; PATH[i] != NULL; i++) {
    char* path = malloc(
        sizeof(char) * strlen(PATH[i]) +
        sizeof(char) * strlen("/") +
        sizeof(char) * strlen(program) + 1);

    strcat(path, strdup(PATH[i]));
    strcat(path, "/");
    strcat(path, strdup(program));

    if (access(path, X_OK) == 0) {
      return path;
    }
  }

  panic();
  exit(1);
}

int handle_command(char* input, int* fd) {
  char** tokens = parse_input(input, " ");

  if (strcmp(tokens[0], "exit") == 0) {
    if (tokens[1] != NULL) {
      panic();
    }
    exit(0);
  }
  if (strcmp(tokens[0], "cd") == 0) {
    if (chdir(tokens[1]) < 0) {
      panic();
    }
    return -1;
  }
  if (strcmp(tokens[0], "path") == 0) {
    PATH = &tokens[1];
    return -1;
  }

  int rc = fork();

  if (rc < 0) {
    panic();
    return -1;
  }

  if (rc == 0) {
    dup2(fd[0], 0);
    dup2(fd[1], 1);

    tokens[0] = find_program(tokens[0]);

    if (execv(tokens[0], tokens) < 0) {
      panic();
      exit(1);
    };
  } 

  return rc;
}

int handle_redirect(char* input) {
  char** tokens = parse_input(input, ">");
  int fd[2] = {0, 1};

  if (tokens[1] != NULL) {
    if (parse_input(tokens[1], " ")[1] != NULL || tokens[2] != NULL) {
      panic();
      return -1;
    }

    int f = open(tokens[1], O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);

    if (f < 0) {
      panic();
      return -1;
    }

    fd[1] = f;
  }

  return handle_command(tokens[0], fd);
}

void handle_concurrent(char* input) {
  char** tokens = parse_input(input, "&");

  int i = 0;
  char* token;

  int pids_len = 0;
  int* pids = malloc(sizeof(int) * pids_len);

  while ((token = tokens[i++]) != NULL) {
    if (strlen(token) == 0) {
      continue;
    }

    pids_len++;
    pids = realloc(pids, sizeof(int) * pids_len);
    pids[pids_len - 1] = handle_redirect(token);
  }

  for (int i = 0; i < pids_len; i++) {
    waitpid(pids[i], NULL, 0);
  }
}

int main(int argc, char** argv) {
  PATH = malloc(sizeof(char*) + sizeof(NULL));
  PATH[0] = "/bin";
  PATH[1] = NULL;

  if (argc > 2) {
    panic();
    exit(1);
  }
  if (argc > 1) {
    close(0);

    if (open(argv[1], O_RDONLY) < 0) {
      panic();
      exit(1);
    }
  }

  char *line = NULL;

  ssize_t linelen;
  size_t linecap = 0;

  if (argc == 1) {
    printf("wish> ");
  }
  while ((linelen = getline(&line, &linecap, stdin)) > 0) {
    if (strlen(trim_left(trim_right(line))) == 0) {
      continue;
    };

    handle_concurrent(line);

    if (argc == 1) {
      printf("wish> ");
    }
  }
}
