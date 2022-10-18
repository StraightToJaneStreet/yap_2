#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <chrono>
#include <numeric>

template<typename T>
T pick_item(const std::vector<T> &source) {
  int position = rand() % source.size();

  return source[position];
}

std::string pick_sequence(const std::vector<std::string> &source) {
  auto first = pick_item(source);
  auto second = pick_item(source);
  return first + " " + second;
}

int main() {
  srand(std::chrono::system_clock::now().time_since_epoch().count());

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
      encryption_base.push_back(word);
    }
  }

  encryption_base.shrink_to_fit();

  std::vector<std::string> message_items;

  {
    std::string word;

    while (!fin_message.eof()) {
      fin_message >> word;

      message_items.push_back(word);
    }
  }

  message_items.shrink_to_fit();

  std::string encrypted = std::accumulate(
      std::next(message_items.begin()),
      message_items.end(),
      *message_items.begin(),
      [&encryption_base](const std::string& l, const std::string& r) -> std::string {
        return l + " " + pick_sequence(encryption_base) + " " + r;
      }
  );

  encrypted = pick_sequence(encryption_base) + " " + encrypted;

  fout_encrypted << encrypted << std::endl;

  fin_base.close();
  fin_message.close();

  fout_encrypted.close();

  return 0;
}