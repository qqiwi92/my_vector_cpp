#include "tests.hpp"
#include "helpers.hpp"
#include <string>
#include "vector.hpp"

bool testEmptyVector()
{
  stuff::Vector< int > v;
  return v.isEmpty();
}

bool testPushBack()
{
  stuff::Vector< int > v;
  v.pushBack(1);
  ASSERT_EQ(v.getSize(), 1);
  v.pushBack(2);
  ASSERT_EQ(v.getSize(), 2);
  v.pushBack(3);
  ASSERT_EQ(v.getSize(), 3);

  return true;
}

bool testAt()
{
  stuff::Vector< int > v;
  v.pushBack(1);
  ASSERT_EQ(v.at(0), 1);
  v.pushBack(2);
  ASSERT_EQ(v.at(1), 2);
  v.pushBack(3);
  ASSERT_EQ(v.at(2), 3);
  v.at(2) = 4;
  ASSERT_EQ(v.at(2), 4);

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
  ASSERT_EQ(v[0], 1);
  v.pushBack(2);
  ASSERT_EQ(v[1], 2);
  v.pushBack(3);
  ASSERT_EQ(v[2], 3);
  v[2] = 4;
  ASSERT_EQ(v[2], 4);

  return true;
}

bool testInsert()
{
  stuff::Vector< int > v;
  v.insert(0, 1);
  ASSERT_EQ(v[0], 1);
  v.insert(0, 2);
  ASSERT_EQ(v[0], 2);

  return true;
}

bool testErase()
{
  stuff::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  v.erase(1);
  ASSERT_EQ(v[1], 3);
  return true;
}

bool testConstContainer()
{
  stuff::Vector< int > v;
  v.pushBack(42);

  const stuff::Vector< int >& c_v = v;

  ASSERT_EQ(c_v.getSize(), 1);
  ASSERT_EQ(c_v.at(0), 42);
  ASSERT_EQ(c_v[0], 42);

  return true;
}

bool testCopyConstructor()
{
  stuff::Vector< int > v;
  stuff::Vector< int > yav = v;
  ASSERT_EQ(v, yav);
  return true;
}

bool testCopyConstrucotorForNonEmpty()
{
  stuff::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  stuff::Vector< int > yav = v;
  ASSERT_EQ(v, yav);
  return true;
}

bool testInitializerConstructor()
{
  stuff::Vector< int > v{1, 2, 3};
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
  ASSERT_EQ(v[2], 3)
  return true;
}

bool testPushBackCount()
{
  stuff::Vector< int > v;
  v.pushBackCount(3, 64);
  ASSERT_EQ(v[0], 64);
  ASSERT_EQ(v[1], 64);
  ASSERT_EQ(v[2], 64)
  return true;
}

bool testPushBackRange()
{
  int data[] = {10, 20, 30, 40};
  stuff::Vector< int > v;
  v.pushBackRange(data, 4);

  ASSERT_EQ(v.getSize(), 4);

  bool match = (v[0], 10 && v[1], 20 && v[2], 30 && v[3], 40);
  ASSERT_EQ(match, true);
  return true;
}

bool testReserve()
{
  stuff::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);

  size_t oldSize = v.getSize();
  v.reserve(100);

  ASSERT_EQ(v.getSize(), oldSize);
  ASSERT_TRUE(v.getCapacity() >= 100);
  ASSERT_EQ(v[0] == 1, v[1] == 2);
  return true;
}

bool testShrinkToFit()
{
  stuff::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.reserve(100);

  v.shrinkToFit();
  return v.getCapacity(), v.getSize();
}

bool testEraseRange()
{
  auto v = stuff::Vector< int >({1, 2, 3, 4, 5});
  v.erase(v.begin() + 1, v.begin() + 3);

  ASSERT_EQ(v.getSize(), 3);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 4);
  ASSERT_EQ(v[2], 5);
  return true;
}

#include <string>

bool testStringVector()
{
  stuff::Vector< std::string > v;
  v.pushBack("Hello");
  v.pushBack("World");

  ASSERT_EQ(v.getSize(), 2);
  ASSERT_EQ(v[0], "Hello");
  ASSERT_EQ(v[1], "World");
  return true;
}

bool testStringDeepCopy()
{
  stuff::Vector< std::string > v1;
  v1.pushBack("Original");

  stuff::Vector< std::string > v2 = v1;
  v2[0] = "Changed";
  ASSERT_EQ(v1[0], "Original");
  ASSERT_EQ(v2[0], "Changed");
  return true;
}

bool testStringReallocation()
{
  stuff::Vector< std::string > v;
  for (int i = 0; i < 50; ++i) {
    v.pushBack("string_" + std::to_string(i));
  }

  ASSERT_EQ(v.getSize(), 50);
  ASSERT_EQ(v[49], "string_49");
  return true;
}

bool testStringEdgeCases()
{
  stuff::Vector< std::string > v;

  v.pushBack("");
  ASSERT_EQ(v[0].empty(), true);

  std::string longStr(1000, 'a');
  v.pushBack(longStr);
  ASSERT_EQ(v[1].length(), 1000);

  v.pushBack("to_be_deleted");
  v.pushBack("keep_me");
  v.erase(2);

  ASSERT_EQ(v[2], "keep_me");
  return true;
}