#include "vector.hpp"
#include "gtest/gtest.h"

TEST(TestVector, TestRnadom){
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    ASSERT_TRUE(v.size() == 3);
    ASSERT_TRUE(v.capacity() == 7); // 3 * 2 + 1
    v.pop_back();
    ASSERT_TRUE(v.size() == 2);
    ASSERT_TRUE(v.capacity() == 7);
    ASSERT_TRUE(v[0] == 1);
    ASSERT_TRUE(v[1] == 2);
    ASSERT_TRUE(v.empty() == false);
    v.clear();
    ASSERT_TRUE(v.empty() == true);
}
