#include <stdio.h>
#include <stdlib.h>

enum Slot {
  EMPTY = '_',
  WHITE = 'W',
  BLACK = 'B'
};

typedef struct Field* PField;

struct Field {
  int size;
  enum Slot slots[100];
};

PField Field__create(int size, int black_count, int white_count) {
  PField p = (PField) calloc(1, sizeof(struct Field));
  p->size = size;
  int position = 0;
  int limit = black_count;

  for (; position < limit; position++) {
    p->slots[position] = BLACK;
  }

  limit += white_count;
  for (; position < limit; position++) {
    p->slots[position] = WHITE;
  }

  for (; position < size; position++) {
    p->slots[position] = EMPTY;
  }

  return p;
};

void Field__print(PField field, FILE* fout) {
  fprintf(fout, "%c", field->slots[0]);
  for (int i = 1; i < field->size; i++) {
    fprintf(fout, " %c", field->slots[i]);
  }
  fprintf(fout, "\n");
}

void Field__left_long_jump(PField field, int position) {
  if (
      position < 2
      || field->slots[position] != WHITE
      || field->slots[position - 1] != BLACK
      || field->slots[position - 2] != EMPTY
    ) {
    printf("Invalid jump");
    exit(100);
  }

  field->slots[position - 2] = WHITE;
  field->slots[position] = EMPTY;
}

void Field__left_jump(PField field, int position) {
  if (
      position == 0
      || field->slots[position] != WHITE
      || field->slots[position - 1] != EMPTY
    ) {
    printf("Invalid jump");
    exit(100);
  }

  field->slots[position - 2] = WHITE;
  field->slots[position] = EMPTY;
}


int main() {
  FILE* fin = fopen("input.txt", "r");
  FILE* fout = fopen("output.txt", "w+");

  int field_size, black_count, white_count;

  fscanf(fin, "%d %d %d", &field_size, &black_count, &white_count);

  PField field = Field__create(field_size, black_count, white_count);

  Field__print(field, fout);

  return 0;
}