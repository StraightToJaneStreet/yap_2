#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>

struct Toy {
  std::string name;
  unsigned int price;

};

std::ostream &operator<< (std::ostream &out, const Toy &toy) {
  return out << "{ Name: " + toy.name + "; Price: " + std::to_string(toy.price) + " }";
}

const unsigned int PRICE_BORDER = 10000;

int main() {
  std::vector<Toy> toys = {
    Toy { "Stick" , 9940 },
    Toy { "Rock", 11000 },
    Toy { "Sand", 1200 },
    Toy { "Leaf", 2000 },
    Toy { "Grass", 7000 },
    Toy { "Another rock", 35000 },
  };

  std::vector<Toy> filtered_toys;

  std::copy_if(
      toys.begin(), toys.end(),
      std::back_inserter(filtered_toys),
      [](const Toy &toy) { return toy.price <= PRICE_BORDER; }
  );

  std::cout << "Initial toys list:" << std::endl;

  std::copy(
    toys.begin(), toys.end(),
    std::ostream_iterator<Toy>(std::cout, "\n")
  );

  std::cout << "Filtered toys list:" << std::endl;

  std::copy(
      filtered_toys.begin(), filtered_toys.end(),
      std::ostream_iterator<Toy>(std::cout, "\n")
  );

  return 0;
}