#include "vector.hpp"
#include <iostream>

#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_RESET "\033[0m"

bool testEmptyVector() { return false; }

int main()
{
  using test_t = std::pair< const char*, bool (*)() >;
  test_t tests[] = {{"Empty vector", testEmptyVector}};
  const size_t count = sizeof(tests) / sizeof(test_t);

  std::cout << std::boolalpha;

  bool all_pass = true;
  for (size_t i = 0; i < count; ++i) {
    bool res = tests[i].second();

    if (!res) {
      std::cout << ANSI_RED << tests[i].first << ": " << res << ANSI_RESET;
      all_pass = false;
    } else {
      std::cout << ANSI_GREEN << tests[i].first << ": " << res << ANSI_RESET;
    }
    std::cout << "\n";
  }

  std::cout << "\n";
  return all_pass ? 0 : 1;
}
