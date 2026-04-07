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

bool testInsert()
{
  stuff::Vector< int > v;
  v.insert(0, 1);
  ASSERT_TRUE(v[0] == 1);
  v.insert(0, 2);
  ASSERT_TRUE(v[0] == 2);

  return true;
}

bool testErase()
{
  stuff::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  v.erase(1);
  ASSERT_TRUE(v[1] == 3);
  return true;
}

bool testConstContainer()
{
  stuff::Vector< int > v;
  v.pushBack(42);

  const stuff::Vector< int >& c_v = v;

  ASSERT_TRUE(c_v.getSize() == 1);
  ASSERT_TRUE(c_v.at(0) == 42);
  ASSERT_TRUE(c_v[0] == 42);

  return true;
}

bool testCopyConstructor()
{
  stuff::Vector< int > v;
  stuff::Vector< int > yav = v;
  return v == yav;
}

bool testCopyConstrucotorForNonEmpty()
{
  stuff::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  stuff::Vector< int > yav = v;
  return v == yav;
}

bool testInitializerConstructor()
{
  stuff::Vector< int > v{1, 2, 3};
  ASSERT_TRUE(v[0] == 1);
  ASSERT_TRUE(v[1] == 2);
  ASSERT_TRUE(v[2] == 3)
  return true;
}

bool testPushBackCount()
{
  stuff::Vector< int > v;
  v.pushBackCount(3, 64);
  ASSERT_TRUE(v[0] == 64);
  ASSERT_TRUE(v[1] == 64);
  ASSERT_TRUE(v[2] == 64)
  return true;
}

bool testPushBackRange()
{
  int data[] = {10, 20, 30, 40};
  stuff::Vector< int > v;
  v.pushBackRange(data, 4);

  ASSERT_TRUE(v.getSize() == 4);

  bool match = (v[0] == 10 && v[1] == 20 && v[2] == 30 && v[3] == 40);
  ASSERT_TRUE(match);
  return true;
}

bool testReserve()
{
  stuff::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);

  size_t oldSize = v.getSize();
  v.reserve(100);

  ASSERT_TRUE(v.getSize() == oldSize);
  ASSERT_TRUE(v.getCapacity() >= 100);
  ASSERT_TRUE(v[0] == 1 && v[1] == 2);
  return true;
}

bool testShrinkToFit()
{
  stuff::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.reserve(100);

  v.shrinkToFit();
  return v.getCapacity() == v.getSize();
}

bool testEraseRange()
{
  auto v = stuff::Vector< int >({1, 2, 3, 4, 5});
  v.erase(v.begin() + 1, v.begin() + 3); 
  
  ASSERT_TRUE(v.getSize() == 3);
  ASSERT_TRUE(v[0] == 1);
  ASSERT_TRUE(v[1] == 4);
  ASSERT_TRUE(v[2] == 5);
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

using test_t = std::pair< const char*, bool (*)() >;

template < size_t Len > bool run_tests(test_t (&in)[Len])
{
  const size_t count = sizeof(in) / sizeof(test_t);

  std::cout << std::boolalpha;

  bool all_pass = true;
  for (size_t i = 0; i < count; ++i) {
    test_t tst = in[i];
    run_test(tst.first, tst.second);
  }

  std::cout << "\n";
  return all_pass;
}

int main()
{
  test_t tests[] = {
      {"Empty", testEmptyVector},
      {"Push", testPushBack},
      {"at()", testAt},
      {"Vec[i]", testBrackets},
      {"insert()", testInsert},
      {"erase()", testErase},
      {"Const Elements", testConstContainer},
      {"copy constructor", testCopyConstructor},
      {"copy constructor non empty", testCopyConstrucotorForNonEmpty},
      {"initializer constructor", testInitializerConstructor},
      {"pushBackCount", testPushBackCount},
      {"pushBackRange", testPushBackRange},
      {"reserve", testReserve},
      {"shrinkToFit", testShrinkToFit},
      {"EraseRange", testEraseRange},
  };

  bool success = run_tests(tests);

  return success ? 0 : 1;
}
