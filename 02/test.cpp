#include "parser.hpp"
#include "gtest/gtest.h"


TEST(TestParser, TestSingleTokens){
    TokenParser parser;
    std::vector<uint64_t> numbers;
    std::vector<std::string> strings;
    parser.SetDigitTokenCallback([&](uint64_t digit){numbers.push_back(digit); });
    parser.SetStringTokenCallback([&](std::string str){strings.push_back(str); });
    std::string test_text1 = "8";
    std::string test_text2 = "A";

    parser.Parse(test_text1);
    ASSERT_EQ(numbers.size(), 1);
    ASSERT_EQ(strings.size(), 0);
    ASSERT_EQ(numbers[0], 8ull);

    strings.clear();
    numbers.clear();

    parser.Parse(test_text2);
    ASSERT_EQ(numbers.size(), 0);
    ASSERT_EQ(strings.size(), 1);
    ASSERT_EQ(strings[0], "A");
}

//Проверка, что правильно парсим числа, краевые условия это ноль и (2^64 - 1) 
TEST(TestParser, TestNumbers){
    TokenParser parser;
    std::vector<uint64_t> numbers;
    std::vector<std::string> strings;
    parser.SetDigitTokenCallback([&](uint64_t digit){numbers.push_back(digit); });
    parser.SetStringTokenCallback([&](std::string str){strings.push_back(str); });
    std::string test_text = "0 \t\t4\n\n23 234234 00124 18446744073709551615\t";
    std::vector<uint64_t> test_out = {0ull ,4ull, 23ull, 234234ull, 124ull, 18446744073709551615ull};
    
    parser.Parse(test_text);
    ASSERT_EQ(numbers.size(), 6);
    ASSERT_EQ(strings.size(), 0);

    ASSERT_EQ(numbers, test_out);
}


//Проверям, что правильно парсим строки
TEST(TestParser, TestStrings){
    TokenParser parser;
    std::vector<uint64_t> numbers;
    std::vector<std::string> strings;
    parser.SetDigitTokenCallback([&](uint64_t digit){numbers.push_back(digit); });
    parser.SetStringTokenCallback([&](std::string str){strings.push_back(str); });
    std::string test_text = "\t\ta  0413ядракон_@!$!%^ \n\n-1 18446744073709551616 131458446744073709551615\n \t";
    std::vector<std::string> test_out = {"a" ,"0413ядракон_@!$!%^", "-1", "18446744073709551616", "131458446744073709551615"};

    parser.Parse(test_text);
    ASSERT_EQ(numbers.size(), 0);
    ASSERT_EQ(strings.size(), 5);

    ASSERT_EQ(strings, test_out);
}


//Если не были установленны callback функции, то ничего не делаем
TEST(TestParser, TestEmptyCallback){
    TokenParser parser;
    std::vector<uint64_t> numbers;
    std::vector<std::string> strings;
    std::string test_text = "afqwrdsggsd";
    
    parser.Parse(test_text);
    ASSERT_EQ(numbers.size(), 0);
    ASSERT_EQ(strings.size(), 0);
}


//Проверяем, что callback для старта добавил в начало нужные вещи, а в конце числа были отсортированы
TEST(TestParser, TestStartEndCallback){
    TokenParser parser;
    std::vector<uint64_t> numbers;
    std::vector<std::string> strings;
    parser.SetDigitTokenCallback([&](uint64_t digit){numbers.push_back(digit); });
    parser.SetStringTokenCallback([&](std::string str){strings.push_back(str); });
    parser.SetStartCallback([&](){numbers.push_back(0ull); strings.push_back("start"); });
    parser.SetEndCallback([&](){std::sort(numbers.begin(), numbers.end()); });

    std::string test_text = "afqwrdsggsd -2 1451 002\t\t\n";
    std::vector<std::string> strings_out = {"start" ,"afqwrdsggsd", "-2"};
    std::vector<uint64_t> numbers_out = {0ull , 2ull, 1451ull};

    parser.Parse(test_text);
    ASSERT_EQ(numbers.size(), 3);
    ASSERT_EQ(strings.size(), 3);
    
    ASSERT_EQ(strings, strings_out);
    ASSERT_EQ(numbers, numbers_out);
}


TEST(TestParser, TestEmptyText){
    TokenParser parser;
    std::vector<uint64_t> numbers;
    std::vector<std::string> strings;
    parser.SetDigitTokenCallback([&](uint64_t digit){numbers.push_back(digit); });
    parser.SetStringTokenCallback([&](std::string str){strings.push_back(str); });
    std::string test_text = "";
    
    parser.Parse(test_text);
    ASSERT_EQ(numbers.size(), 0);
    ASSERT_EQ(strings.size(), 0);

    test_text = "      ";
    parser.Parse(test_text);
    ASSERT_EQ(numbers.size(), 0);
    ASSERT_EQ(strings.size(), 0);
}


int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}