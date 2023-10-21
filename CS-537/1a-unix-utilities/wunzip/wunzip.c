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

// assumes that |str| = q * (5 chars) + \0, where q >= 0
void RLE_decode(char* str) {
  int_converter cvt;
  while (*str) {
    for (int i = 0; i != 4; ++i) {
      cvt.c[i] = str[i];
    }
    char c = str[4];
    for (int i = 0; i != cvt.a; ++i) {
      printf("%c", c);
    }
    str += 5;
  }
}

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    puts("wunzip: file1 [file2 ...]");
    exit(1);
  }
 
  char* line = NULL;
  size_t line_size = 0;
  
  char encoded[6];
  encoded[5] = '\0';
  size_t endoded_id = 0;

  for (int i = 1; i < argc; ++i) {
    FILE* file = fopen(argv[i], "r");
    if (!file) {
      printf("wunzip: cannot open file");
      exit(1);
    }

    int len = 0;
    while ((len = getline(&line, &line_size, file)) > 0) {
      for (size_t j = 0; j < len; ++j) {
        encoded[endoded_id++] = line[j];
        if (endoded_id == 5) {
          endoded_id = 0;
          RLE_decode(encoded);
        }
      }
    }
  }

  return 0;
}
