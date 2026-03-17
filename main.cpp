#include "vector.hpp"
#include <iostream>
bool testEmptyVector() { return false; }

int main()
{
  using test_t = std::pair< const char*, bool (*)() >;
  test_t tests[] = {{"Empty vector", testEmptyVector}};
  const size_t count = sizeof(tests) / sizeof(test_t);
  for (size_t i = 0; i < count; ++i) {
    std::cout << tests[i].first << ": ";
    std::cout << tests[i].second() << ": ";
  }

  std::cout << "\n";
}
