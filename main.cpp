#include "helpers.hpp"
#include "tests.hpp"
#include "vector.hpp"
#include <iostream>




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
      {"String Basics", testStringVector},
      {"String Deep Copy", testStringDeepCopy},
      {"String Reallocation", testStringReallocation},
      {"String Edge Cases", testStringEdgeCases}};

  bool success = run_tests(tests);

  stuff::Vector< int > v{1, 2, 3};
  return success ? 0 : 1;
}
