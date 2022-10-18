#include <algorithm>
#include <cstddef>
#include <string>
#include <iostream>

const std::string BASE_STRING = "POLILI LILIU";
const std::string TARGET_SUBSTRING = "LI";
const std::string REPLACEMENT = "STO";

int main() {
  auto source = BASE_STRING;

  {
    const auto substring_length = TARGET_SUBSTRING.length();
    const auto base_replacement_length = REPLACEMENT.length();
    const auto full_replacement_length = base_replacement_length + 1;

    for (
        size_t
          iterations_counter = 1,
          shift = 0,
          position = source.find(TARGET_SUBSTRING, shift);

        position != std::string::npos && iterations_counter <= 9;

        shift = position + full_replacement_length,
        position = source.find(TARGET_SUBSTRING, shift),
        iterations_counter++
    ) {
      const auto substring_begin = source.begin() + position;
      const auto substring_end = substring_begin + substring_length;

      source.insert(substring_end, *std::to_string(iterations_counter).begin());
      source.replace(substring_begin, substring_end, REPLACEMENT.begin(), REPLACEMENT.end());
    }
  }

  std::cout << "Result:" << std::endl;
  std::cout << source << std::endl;

  return 0;
}