#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  const int buffer_size = 255;

  for (int i = 1; i < argc; ++i) {
    FILE* file = fopen(argv[i], "r");
    if (!file) {
      printf("wcat: cannot open file\n");
      exit(1);
    }
   
    char s[buffer_size];
    while (fgets(s, buffer_size, file)) {
      printf("%s", s);
    }

    fclose(file);
  }

  return 0;
}
