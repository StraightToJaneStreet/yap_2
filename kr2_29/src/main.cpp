#include <algorithm>
#include <fstream>
#include <map>

void pretty_print(std::ostream& out, const std::pair<int, int>& node) {
  out << "Number: " << node.first << "; Count: " << node.second << ";" << std::endl;
}

int main() {
  std::ifstream fin;
  std::ofstream fout_repeated, fout_unique;

  fin.open("input.txt");

  fout_repeated.open("repeated.txt");
  fout_unique.open("unique.txt");

  std::map<int, int> storage;

  {
    std::string buffer;

    while (!fin.eof()) {
      fin >> buffer;
      storage[std::stoi(buffer)]++;
    }
  }

  for (const auto &node : storage) {
    if (node.second > 1) {
      pretty_print(fout_repeated, node);
    } else {
      pretty_print(fout_unique, node);
    }
  }

  fin.close();

  fout_unique.close();
  fout_repeated.close();

  return 0;
}