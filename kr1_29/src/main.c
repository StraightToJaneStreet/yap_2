#include <stdio.h>
#include <stdlib.h>

typedef struct Toy* PToy;

struct Toy {
  const char* name;
  unsigned int price;
};

const unsigned int PRICE_BORDER = 10000;

void Toy__print(PToy toy) {
  printf("Name: %s; Price: %d\n", toy->name, toy->price);
}

int main() {
  size_t initial_toys_count = 6;

  struct Toy toys[100] = {
    { "Stick" , 9940 },
    { "Rock", 11000 },
    { "Sand", 1200 },
    { "Leaf", 2000 },
    { "Grass", 7000 },
    { "Another rock", 35000 },
  };

  int filtered_toys_count = 0;
  struct Toy filtered_toys[100];

  for (int i = 0; i < initial_toys_count; i++) {
    if (toys[i].price < PRICE_BORDER) {
      filtered_toys[filtered_toys_count] = toys[i];
      filtered_toys_count++;
    }
  }

  printf("Initial toys list:\n");
  for (int i = 0; i < initial_toys_count; i++) {
    Toy__print(&toys[i]);
  }

  printf("Filtered toys list:\n");
  for (int i = 0; i < filtered_toys_count; i++) {
    Toy__print(&filtered_toys[i]);
  }

  return 0;
}