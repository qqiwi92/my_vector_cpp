#ifndef HELPERS
#define HELPERS

#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_RESET "\033[0m"
#define ASSERT_TRUE(condition)                                                 \
  if (!(condition))                                                            \
    return false;

#define ASSERT_EQ(actual, expected)                                            \
  if (!((actual) == (expected))) {                                             \
    stuff::log_failure(                                                               \
        #actual " == " #expected, expected, actual, __FILE__, __LINE__);       \
    return false;                                                              \
  }

#include <iostream>
namespace stuff {
  template < class T, class U >
  void log_failure(
      const char* expr,
      const T& expected,
      const U& actual,
      const char* file,
      int line)
  {
    std::cerr << ANSI_RED << "[FAIL] Assertion failed: " << expr << ANSI_RESET
              << "\n"
              << "       Expected: " << expected << "\n"
              << "       Actual:   " << actual << "\n"
              << "       At:       " << file << ":" << line << "\n";
  }

}

#endif
