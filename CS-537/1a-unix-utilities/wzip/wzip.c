#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef union {
  int a;
  char c[4];
} int_converter;

void put_int_dump(int a) {
  int_converter cvt = {.a = a};
  printf("%c%c%c%c", cvt.c[0], cvt.c[1], cvt.c[2], cvt.c[3]);
}

void RLE(char* str, bool forse_print) {
  static int counter = 0;
  static char c = '\0';

  while (*str != '\0') {
    if (!counter) {
      c = *str;
    }
    while (*str == c) {
      ++counter;
      ++str;
    }
    if (*str) {
      put_int_dump(counter);
      putchar(c);
      counter = 0;
    }
  }
  if (forse_print && counter) {
      put_int_dump(counter);
      putchar(c);
      counter = 0;
  }
}

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    puts("wzip: file1 [file2 ...]");
    exit(1);
  }

  const int buffer_size = 1024;  

  for (int i = 1; i < argc; ++i) {
    FILE* file = fopen(argv[i], "r");
    if (!file) {
      printf("wzip: cannot open file");
      exit(1);
    }

    char buffer[buffer_size];
    while (fgets(buffer, buffer_size, file)) {
      if (i == argc - 1) {
        RLE(buffer, true);
      } else {
        RLE(buffer, false);
      }
    }
  }

  return 0;
}
