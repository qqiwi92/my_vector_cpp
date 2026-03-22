#include "vector.hpp"
#include <iostream>

#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_RESET "\033[0m"

bool testEmptyVector()
{
  stuff::Vector< int > v;
  return v.isEmpty();
}

bool testPushBack() {
    stuff::Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    return v.getSize() == 3;
}

int main()
{
  using test_t = std::pair< const char*, bool (*)() >;
  test_t tests[] = {{"Empty vector", testEmptyVector}, {"Push test", testPushBack}};
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
