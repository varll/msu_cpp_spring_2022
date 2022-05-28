#include "format.hpp"
#include "gtest/gtest.h"


TEST(TestFormat, TestFromHomework){
    auto text = format("{1}+{1} = {0}", 2, "one");
    ASSERT_EQ(text, "one+one = 2");
}

TEST(TestFormat, TestWrongText){
    try{
        auto text = format("{0}+{test} = 3", 2, 1);
    }
    catch(std::runtime_error const& err){
            EXPECT_EQ(err.what(), std::string("number expected"));
    }

    try{
        auto text = format("{0} + 0}", 1);
    }
    catch(std::runtime_error const& err){
        EXPECT_EQ(err.what(), std::string("expected opening"));
    }

    try{
        auto text = format("{0 + {0} - 2", 1);
    }
    catch(std::runtime_error const& err){
        EXPECT_EQ(err.what(), std::string("number expected"));
    }

    try{
        auto text = format("{0} - {1} + {2}", 2, 4);
    }
    catch(std::runtime_error const& err){
        EXPECT_EQ(err.what(), std::string("out of range"));
    }
}

TEST(TestFormat, TestNormalText){
    auto text = format("{2} + {0} = {1}{1}", 8, 1, 3);
    ASSERT_EQ(text, "3 + 8 = 11");

    text = format("{3} test_test {0}{2}{1}", "test", std::string("one"), 0.132, true, 32);
    ASSERT_EQ(text, "1 test_test test0.132one");
}


int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}