#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Storage* PStorage;

struct Storage {
  int size;
  int keys[100];
  int values[100];
};

PStorage Storage__new() {
  PStorage p = (PStorage) calloc(1, sizeof(struct Storage));
  p->size = 0;
  return p;
}

int* Storage__get_cell(PStorage storage, int key) {
  for (int i = 0; i < storage->size; i++) {
    if (storage->keys[i] == key) {
      return &storage->values[i];
    }
  }

  return NULL;
}

int* Storage__create_cell(PStorage storage, int key) {
  storage->keys[storage->size] = key;
  storage->values[storage->size] = 0;
  storage->size++;
  return &storage->values[storage->size - 1];
}

bool Storage__has(PStorage storage, int key) {
  return Storage__get_cell(storage, key) != NULL;
}

void pretty_print(FILE* fout, int value, int count) {
  fprintf(fout, "Value: %d; Count: %d;\n", value, count);
}

int main() {
  FILE* fin = fopen("input.txt", "r");
  FILE* fout_unique = fopen("unique.txt", "w+");
  FILE* fout_repeated = fopen("repeated.txt", "w+");

  PStorage storage = Storage__new();

  while (!feof(fin)) {
    int value;
    fscanf(fin, "%d", &value);
    int *cell_adress = Storage__get_cell(storage, value);

    if (Storage__has(storage, value)) {
      int* cell = Storage__get_cell(storage, value);
      *cell += 1;
    } else {
      int* cell = Storage__create_cell(storage, value);
      (*cell) = 1;
    }
  }

  for (int i = 0; i < storage->size; i++) {
    int value = storage->keys[i];
    int count = storage->values[i];

    if (count > 1) {
      pretty_print(fout_repeated, value, count);
    } else {
      pretty_print(fout_unique, value, count);
    }
  }

  return 0;
}