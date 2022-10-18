#include <stdio.h>
#include <string.h>

const char* BASE_STRING = "POLILI LILIU";
const char* TARGET_SUBSTRING = "LI";
const char* REPLACEMENT = "STO";

int main() {
  char source[100];

  strcpy(source, BASE_STRING);

  {
    size_t substring_length = strlen(TARGET_SUBSTRING);
    size_t base_replacement_length = strlen(REPLACEMENT);
    size_t full_replacement_length = base_replacement_length + 1;

    size_t position_shift = 0;

    size_t source_length = strlen(source);
    int iterations_counter = 0;

    char* position = strstr(source, TARGET_SUBSTRING);

    for(
        ;
        position != NULL && position_shift < source_length;
        position = strstr(source + position_shift, TARGET_SUBSTRING)
    ) {
      iterations_counter += 1;

      size_t index = position - source;
      size_t tail_length = source_length - index - substring_length + 1;

      memcpy(position + full_replacement_length, position + substring_length, tail_length);
      memcpy(position, REPLACEMENT, base_replacement_length);
      *(position + base_replacement_length) = iterations_counter + '0';

      position_shift = index + full_replacement_length;
      source_length += full_replacement_length - substring_length;
    }
  }

  printf("Result: %s\n", source);

  return 0;
}