#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep(char** line, size_t* line_size, const char* needle, FILE* file) {
  while (getline(line, line_size, file) > 0) {
    if (strstr(*line, needle)) {
      printf("%s", *line);
    }
  }
}

int main(int argc, char* argv[]) {
  char* line;
  size_t line_size;

  if (argc <= 1) {
    puts("wgrep: searchterm [file ...]");
    exit(1);
  }

  if (argc == 2) {
    grep(&line, &line_size, argv[1], stdin);
  }
  for (int i = 2; i < argc; ++i) {
    FILE* file = NULL;

    file = fopen(argv[i], "r");
      if (!file) {
        printf("wgrep: cannot open file\n");
        exit(1);
      }
    grep(&line, &line_size, argv[1], file);
    fclose(file);
  }

  free(line);

  return 0;
}
