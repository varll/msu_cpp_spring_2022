#include "BigInt.hpp"
#include "gtest/gtest.h"

TEST(TestBigInt, TestValidCreation){
    BigInt test;
    BigInt test_int32(123);
    BigInt neg_test_int32(-66);
    BigInt test_string("12345678901234567890");
    BigInt neg_test_string("-12345678901234567890");
    
    ASSERT_TRUE(test.get_data());
    ASSERT_EQ(test.get_size(), 1);
    ASSERT_EQ(test.get_sign(), 0);

    ASSERT_TRUE(test_int32.get_data());
    ASSERT_EQ(test_int32.get_size(), 3);
    ASSERT_EQ(test_int32.get_sign(), 0);

    ASSERT_TRUE(neg_test_int32.get_data());
    ASSERT_EQ(neg_test_int32.get_size(), 2);
    ASSERT_EQ(neg_test_int32.get_sign(), 1);  

    ASSERT_TRUE(test_string.get_data());
    ASSERT_EQ(test_string.get_size(), 20);
    ASSERT_EQ(test_string.get_sign(), 0);  

    ASSERT_TRUE(neg_test_string.get_data());
    ASSERT_EQ(neg_test_string.get_size(), 20);
    ASSERT_EQ(neg_test_string.get_sign(), 1);   
}

TEST(TestBigInt, TestPlus){
    BigInt test1;
    BigInt test2 = {"999999"};
    BigInt test_int32(123);
    BigInt neg_test_int32(-66);
    BigInt test_string("12345678901234567890");
    BigInt neg_test_string("-12345678901234567890");

    BigInt result = test_int32 + test1;
    std::string test_out = {"123"};
    std::reverse(test_out.begin(), test_out.end());

    ASSERT_EQ(result.get_size(), 3);
    ASSERT_EQ(result.get_sign(), 0);
    for(size_t i = 0; i < result.get_size(); i++){
        ASSERT_EQ(result.get_data()[i], test_out[i]);
    }

    result = test_int32 + neg_test_int32;
    test_out = {"57"};
    std::reverse(test_out.begin(), test_out.end());

    ASSERT_EQ(result.get_size(), 2);
    ASSERT_EQ(result.get_sign(), 0);
    for(size_t i = 0; i < result.get_size(); i++){
        ASSERT_EQ(result.get_data()[i], test_out[i]);
    }

    result = neg_test_int32 + neg_test_int32;
    test_out = {"132"};
    std::reverse(test_out.begin(), test_out.end());

    ASSERT_EQ(result.get_size(), 3);
    ASSERT_EQ(result.get_sign(), 1);
    for(size_t i = 0; i < result.get_size(); i++){
        ASSERT_EQ(result.get_data()[i], test_out[i]);
    }

    result = neg_test_string + test_string;
    test_out = {"0"};
    std::reverse(test_out.begin(), test_out.end());

    ASSERT_EQ(result.get_size(), 1);
    ASSERT_EQ(result.get_sign(), 0);
    for(size_t i = 0; i < result.get_size(); i++){
        ASSERT_EQ(result.get_data()[i], test_out[i]);
    }

    result = test2 + test2;
    test_out = {"1999998"};
    std::reverse(test_out.begin(), test_out.end());

    ASSERT_EQ(result.get_size(), 7);
    ASSERT_EQ(result.get_sign(), 0);
    for(size_t i = 0; i < result.get_size(); i++){
        ASSERT_EQ(result.get_data()[i], test_out[i]);
    }

    result = test2 + 1;
    test_out = {"1000000"};
    std::reverse(test_out.begin(), test_out.end());

    ASSERT_EQ(result.get_size(), 7);
    ASSERT_EQ(result.get_sign(), 0);
    for(size_t i = 0; i < result.get_size(); i++){
        ASSERT_EQ(result.get_data()[i], test_out[i]);  
    }
}

TEST(TestBigInt, TestMinus){
    BigInt test1;
    BigInt test_int32(123);
    BigInt neg_test_int32(-66);
    BigInt test_string("12345678901234567890");
    BigInt neg_test_string("-12345678901234567890");

    BigInt result = test_int32 - test1;
    std::string test_out = {"123"};
    std::reverse(test_out.begin(), test_out.end());

    ASSERT_EQ(result.get_size(), 3);
    ASSERT_EQ(result.get_sign(), 0);
    for(size_t i = 0; i < result.get_size(); i++){
        ASSERT_EQ(result.get_data()[i], test_out[i]);
    }

    result = test_int32 - neg_test_int32;
    test_out = {"189"};
    std::reverse(test_out.begin(), test_out.end());

    ASSERT_EQ(result.get_size(), 3);
    ASSERT_EQ(result.get_sign(), 0);
    for(size_t i = 0; i < result.get_size(); i++){
        ASSERT_EQ(result.get_data()[i], test_out[i]);
    }

    result = neg_test_int32 - neg_test_int32;
    test_out = {"132"};
    std::reverse(test_out.begin(), test_out.end());

    ASSERT_EQ(result.get_size(), 3);
    ASSERT_EQ(result.get_sign(), 1);
    for(size_t i = 0; i < result.get_size(); i++){
        ASSERT_EQ(result.get_data()[i], test_out[i]);
    }

    result = test_string - neg_test_string;
    test_out = {"24691357802469135780"};
    std::reverse(test_out.begin(), test_out.end());

    ASSERT_EQ(result.get_size(), 20);
    ASSERT_EQ(result.get_sign(), 0);
    for(size_t i = 0; i < result.get_size(); i++){
        ASSERT_EQ(result.get_data()[i], test_out[i]);
    }

    result = neg_test_int32 - neg_test_int32;
    test_out = {"132"};
    std::reverse(test_out.begin(), test_out.end());

    ASSERT_EQ(result.get_size(), 3);
    ASSERT_EQ(result.get_sign(), 1);
    for(size_t i = 0; i < result.get_size(); i++){
        ASSERT_EQ(result.get_data()[i], test_out[i]);
    }

    result = test_int32 - 88;
    test_out = {"35"};
    std::reverse(test_out.begin(), test_out.end());

    ASSERT_EQ(result.get_size(), 2);
    ASSERT_EQ(result.get_sign(), 0);
    for(size_t i = 0; i < result.get_size(); i++){
        ASSERT_EQ(result.get_data()[i], test_out[i]);
    }
}

TEST(TestBigInt, TestMul){
    BigInt test1;
    BigInt test_int32(123);
    BigInt neg_test_int32(-66);

    BigInt result = test_int32 * test_int32;
    std::string test_out = {"15129"};
    std::reverse(test_out.begin(), test_out.end());

    ASSERT_EQ(result.get_size(), 5);
    ASSERT_EQ(result.get_sign(), 0);
    for(size_t i = 0; i < result.get_size(); i++){
        ASSERT_EQ(result.get_data()[i], test_out[i]);
    }

    result = test_int32 * neg_test_int32;
    test_out = {"8118"};
    std::reverse(test_out.begin(), test_out.end());

    ASSERT_EQ(result.get_size(), 4);
    ASSERT_EQ(result.get_sign(), 1);
    for(size_t i = 0; i < result.get_size(); i++){
        ASSERT_EQ(result.get_data()[i], test_out[i]);
    }

    result = test_int32 * 999;
    test_out = {"122877"};
    std::reverse(test_out.begin(), test_out.end());

    ASSERT_EQ(result.get_size(), 6);
    ASSERT_EQ(result.get_sign(), 0);
    for(size_t i = 0; i < result.get_size(); i++){
        ASSERT_EQ(result.get_data()[i], test_out[i]);
    }   

    result = test_int32 * 0;
    test_out = {"0"};
    std::reverse(test_out.begin(), test_out.end());

    ASSERT_EQ(result.get_size(), 1);
    ASSERT_EQ(result.get_sign(), 0);
    for(size_t i = 0; i < result.get_size(); i++){
        ASSERT_EQ(result.get_data()[i], test_out[i]);
    }
}

TEST(TestBigInt, TestEq){
    BigInt test1("333"), test2("333");

    ASSERT_TRUE(test1 == test2);

    test1 = test1 + 35;
    test2 = test2 - 20;
    ASSERT_FALSE(test1 == test2);
}

TEST(TestBigInt, TestNe){
    BigInt test1("333"), test2("333");

    ASSERT_FALSE(test1 != test2);

    test1 = test1 + 35;
    test2 = test2 - 20;
    ASSERT_TRUE(test1 != test2);
}

TEST(TestBigInt, TestGt){
    BigInt test1("213"), test2("333"), test3("-111"), test4("-124");

    ASSERT_TRUE(test1 > test3);
    ASSERT_TRUE(test2 > test1);
    ASSERT_TRUE(test3 > test4);
}

TEST(TestBigInt, TestLt){
    BigInt test1("213"), test2("333"), test3("-111"), test4("-124");

    ASSERT_FALSE(test1 < test3);
    ASSERT_FALSE(test2 < test1);
    ASSERT_FALSE(test3 < test4);
}

TEST(TestBigInt, TestGe){
    BigInt test1("213"), test2("333"), test3("-111"), test4("-124"), test5("333");

    ASSERT_TRUE(test1 >= test3);
    ASSERT_TRUE(test2 >= test1);
    ASSERT_TRUE(test3 >= test4);
    ASSERT_TRUE(test2 >= test5);
}

TEST(TestBigInt, TestLe){
    BigInt test1("213"), test2("333"), test3("-111"), test4("-124"), test5("333");

    ASSERT_FALSE(test1 <= test3);
    ASSERT_FALSE(test2 <= test1);
    ASSERT_FALSE(test3 <= test4);
    ASSERT_TRUE(test2 <= test5);
}

int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}