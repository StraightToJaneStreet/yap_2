#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template<typename T>
T pick_item(std::vector<T> source) {
  int position = std::rand() % sizeof(source);

  return source[position];
}

int main() {
  std::ifstream fin_message, fin_base;
  std::ofstream fout_encrypted;

  fin_message.open("message.txt");
  fin_base.open("base.txt");

  if (!fin_message.is_open() || !fin_base.is_open()) {
    std::cout << "Cant open source files" << std::endl;
  }

  fout_encrypted.open("encrypted.txt");

  std::vector<std::string> encryption_base;

  {
    std::string word;

    while (!fin_base.eof()) {
      fin_base >> word;
      std::cout << word;
      encryption_base.push_back(word);
    }
  }

  encryption_base.shrink_to_fit();

  fout_encrypted << pick_item(encryption_base) << std::endl;

  fin_base.close();
  fin_message.close();
  fout_encrypted.close();

  return 0;
}