#include "vector.hpp"
#include <iostream>

#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_RESET "\033[0m"
#define ASSERT_TRUE(condition)                                                 \
  if (!(condition))                                                            \
    return false;

bool testEmptyVector()
{
  stuff::Vector< int > v;
  return v.isEmpty();
}

bool testPushBack()
{
  stuff::Vector< int > v;
  v.pushBack(1);
  ASSERT_TRUE(v.getSize() == 1);
  v.pushBack(2);
  ASSERT_TRUE(v.getSize() == 2);
  v.pushBack(3);
  ASSERT_TRUE(v.getSize() == 3);

  return true;
}

bool testAt()
{
  stuff::Vector< int > v;
  v.pushBack(1);
  ASSERT_TRUE(v.at(0) == 1);
  v.pushBack(2);
  ASSERT_TRUE(v.at(1) == 2);
  v.pushBack(3);
  ASSERT_TRUE(v.at(2) == 3);
  v.at(2) = 4;
  ASSERT_TRUE(v.at(2) == 4);

  try {
    v.at(100);
    return false;
  } catch (...) {
    return true;
  }
}
bool testBrackets()
{
  stuff::Vector< int > v;
  v.pushBack(1);
  ASSERT_TRUE(v[0] == 1);
  v.pushBack(2);
  ASSERT_TRUE(v[1] == 2);
  v.pushBack(3);
  ASSERT_TRUE(v[2] == 3);
  v[2] = 4;
  ASSERT_TRUE(v[2] == 4);

  return true;
}

int main()
{
  using test_t = std::pair< const char*, bool (*)() >;
  test_t tests[] = {
      {"Empty vector", testEmptyVector},
      {"Push test", testPushBack},
      {"at() test", testAt},
      {"Vec[i] test", testBrackets}};

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
