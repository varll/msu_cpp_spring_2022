#include "parser.hpp"
#include "gtest/gtest.h"
#include <vector>

std::vector<uint64_t> numbers;
std::vector<std::string> strings;

void digit_callback(uint64_t digit){
    numbers.push_back(digit);
}

void string_callback(std::string str){
    strings.push_back(str);
}

void start_callback(){
    numbers.push_back(0ull);
    strings.push_back("start");
}

void end_callback(){
    std::sort(numbers.begin(), numbers.end());
}

//Проверка, что правильно парсим числа, краевые условия это ноль и (2^64 - 1) 
TEST(TestParser, TestNumbers){
    TokenParser parser;
    parser.SetDigitTokenCallback(digit_callback);
    parser.SetStringTokenCallback(string_callback);
    std::string test_text = "0 \t\t4\n\n23 234234 00124 18446744073709551615\t";
    std::vector<uint64_t> test_out = {0ull ,4ull, 23ull, 234234ull, 124ul, 18446744073709551615ull};
    parser.Parse(test_text);

    ASSERT_EQ(numbers.size(), 6);
    ASSERT_EQ(strings.size(), 0);
    for (size_t i; i<test_out.size(); i++)
        ASSERT_EQ(numbers[i], test_out[i]);

    numbers.clear();
    strings.clear();
}

//Проверям, что правильно парсим строки
TEST(TestParser, TestStrings){
    TokenParser parser;
    parser.SetDigitTokenCallback(digit_callback);
    parser.SetStringTokenCallback(string_callback);
    std::string test_text = "\t\ta  ядракон_@!$!%^ \n\n-1 18446744073709551616 131458446744073709551615\n \t";
    std::vector<std::string> test_out = {"a" ,"ядракон_@!$!%^", "-1", "18446744073709551616", "131458446744073709551615"};
    parser.Parse(test_text);

    ASSERT_EQ(numbers.size(), 0);
    ASSERT_EQ(strings.size(), 5);
    for (size_t i; i<test_out.size(); i++)
        ASSERT_EQ(strings[i], test_out[i]);

    numbers.clear();
    strings.clear();
}

//Если не были установленны callback функции, то ничего не делаем
TEST(TestParser, TestEmptyCallback){
    TokenParser parser;
    std::string test_text = "afqwrdsggsd";
    parser.Parse(test_text);

    ASSERT_EQ(numbers.size(), 0);
    ASSERT_EQ(strings.size(), 0);
}

//Проверяем, что callback для старта добавил в начало нужные вещи, а в конце числа были отсортированы
TEST(TestParser, TestStartEndCallback){
    TokenParser parser;
    parser.SetDigitTokenCallback(digit_callback);
    parser.SetStringTokenCallback(string_callback);
    parser.SetStartCallback(start_callback);
    parser.SetEndCallback(end_callback);

    std::string test_text = "afqwrdsggsd -2 1451 002\t\t\n";
    std::vector<std::string> strings_out = {"start" ,"afqwrdsggsd", "-2"};
    std::vector<uint64_t> numbers_out = {0ull , 2ull, 1451ull};

    parser.Parse(test_text);

    ASSERT_EQ(numbers.size(), 3);
    ASSERT_EQ(strings.size(), 3);
    for (size_t i; i<strings_out.size(); i++){
        ASSERT_EQ(strings[i], strings_out[i]);
        ASSERT_EQ(numbers[i], numbers_out[i]);
    }

    numbers.clear();
    strings.clear();
}


TEST(TestParser, TestEmptyText){
    TokenParser parser;
    parser.SetDigitTokenCallback(digit_callback);
    parser.SetStringTokenCallback(string_callback);
    std::string test_text = "";
    parser.Parse(test_text);
    
    ASSERT_EQ(numbers.size(), 0);
    ASSERT_EQ(strings.size(), 0);

    numbers.clear();
    strings.clear();
}


int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
