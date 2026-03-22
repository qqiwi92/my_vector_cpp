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

template < typename F > void run_test(const char* name, F test)
{
  try {
    if (test()) {
      std::cout << ANSI_GREEN << "[PASS] " << name << ANSI_RESET << "\n";
    } else {
      std::cout << ANSI_RED << "[FAIL] " << name << ANSI_RESET << "\n";
    }
  } catch (const std::exception& e) {
    std::cout << ANSI_RED << "[CRASH] " << name << " threw: " << e.what()
              << ANSI_RESET << "\n";
  }
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
    test_t tst = tests[i];
    run_test(tst.first, tst.second);
  }

  std::cout << "\n";
  return all_pass ? 0 : 1;
}
