#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream finput_1, finput_2;
  std::ofstream foutput;

  finput_1.open("input_1.txt");
  finput_2.open("input_2.txt");

  foutput.open("output.txt");

  std::string a;

  finput_1 >> a;

  foutput << a;
  return 0;
}