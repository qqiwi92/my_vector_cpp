#ifndef TESTS_HPP
#define TESTS_HPP

#include "helpers.hpp"
using test_t = std::pair< const char*, bool (*)() >;

bool testEmptyVector();
bool testPushBack();
bool testAt();
bool testBrackets();
bool testInsert();
bool testErase();
bool testConstContainer();
bool testCopyConstructor();
bool testCopyConstrucotorForNonEmpty();
bool testInitializerConstructor();
bool testPushBackCount();
bool testPushBackRange();
bool testReserve();
bool testShrinkToFit();
bool testEraseRange();

bool testStringVector();
bool testStringDeepCopy();
bool testStringReallocation();
bool testStringEdgeCases();
template < typename F > bool run_test(const char* name, F test)
{
  bool verbose = false;
  bool result = test();
  try {
    if (result) {
      if (!verbose)
        return true;

      std::cout << ANSI_GREEN << "[PASS] " << name << ANSI_RESET << "\n";
    } else {
      std::cout << ANSI_RED << "[FAIL] " << name << ANSI_RESET << "\n";
    }
  } catch (const std::exception& e) {
    std::cout << ANSI_RED << "[CRASH] " << name << " threw: " << e.what()
              << ANSI_RESET << "\n";
  }
  return result;
}

template < size_t Len > bool run_tests(test_t (&in)[Len])
{
  const size_t count = sizeof(in) / sizeof(test_t);

  std::cout << std::boolalpha;

  size_t successRate = 0;
  for (size_t i = 0; i < count; ++i) {
    test_t tst = in[i];
    bool result = run_test(tst.first, tst.second);
    successRate += result;
  }

  std::cout << "\n";

  if (successRate == count) {

    std::cout << ANSI_GREEN;
  } else {
    std::cout << ANSI_RED;
  }
  std::cout << successRate << '/' << count;
  std::cout << ANSI_RESET << "\n";
  std::cout << "\n";

  ASSERT_EQ(successRate, count);
  return true;
}
#endif
