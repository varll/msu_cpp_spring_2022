#include "parser.hpp"
#include "gtest/gtest.h"


void digit_callback(std::vector<uint64_t> &numbers, uint64_t digit){
    numbers.push_back(digit);
}

void string_callback(std::vector<std::string> &strings, std::string str){
    strings.push_back(str);
}

void start_callback(std::vector<uint64_t> &numbers, std::vector<std::string> &strings){
    numbers.push_back(0ull);
    strings.push_back("start");
}

void end_callback(std::vector<uint64_t> &numbers, std::vector<std::string> &strings){
    std::sort(numbers.begin(), numbers.end());
}


TEST(TestParser, TestSingleTokens){
    TokenParser parser;
    std::vector<uint64_t> numbers;
    std::vector<std::string> strings;
    parser.SetDigitTokenCallback(digit_callback);
    parser.SetStringTokenCallback(string_callback);
    std::string test_text1 = "8";
    std::string test_text2 = "A";

    parser.Parse(test_text1, numbers, strings);
    ASSERT_EQ(numbers.size(), 1);
    ASSERT_EQ(strings.size(), 0);
    ASSERT_EQ(numbers[0], 8ull);

    strings.clear();
    numbers.clear();

    parser.Parse(test_text2, numbers, strings);
    ASSERT_EQ(numbers.size(), 0);
    ASSERT_EQ(strings.size(), 1);
    ASSERT_EQ(strings[0], "A");
}

//Проверка, что правильно парсим числа, краевые условия это ноль и (2^64 - 1) 
TEST(TestParser, TestNumbers){
    TokenParser parser;
    std::vector<uint64_t> numbers;
    std::vector<std::string> strings;
    parser.SetDigitTokenCallback(digit_callback);
    parser.SetStringTokenCallback(string_callback);
    std::string test_text = "0 \t\t4\n\n23 234234 00124 18446744073709551615\t";
    std::vector<uint64_t> test_out = {0ull ,4ull, 23ull, 234234ull, 124ull, 18446744073709551615ull};
    
    parser.Parse(test_text, numbers, strings);
    ASSERT_EQ(numbers.size(), 6);
    ASSERT_EQ(strings.size(), 0);
    for (size_t i; i<test_out.size(); i++)
        ASSERT_EQ(numbers[i], test_out[i]);

}


//Проверям, что правильно парсим строки
TEST(TestParser, TestStrings){
    TokenParser parser;
    std::vector<uint64_t> numbers;
    std::vector<std::string> strings;
    parser.SetDigitTokenCallback(digit_callback);
    parser.SetStringTokenCallback(string_callback);
    std::string test_text = "\t\ta  0413ядракон_@!$!%^ \n\n-1 18446744073709551616 131458446744073709551615\n \t";
    std::vector<std::string> test_out = {"a" ,"0413ядракон_@!$!%^", "-1", "18446744073709551616", "131458446744073709551615"};

    parser.Parse(test_text, numbers, strings);
    ASSERT_EQ(numbers.size(), 0);
    ASSERT_EQ(strings.size(), 5);
    for (size_t i; i<test_out.size(); i++)
        ASSERT_EQ(strings[i], test_out[i]);

}


//Если не были установленны callback функции, то ничего не делаем
TEST(TestParser, TestEmptyCallback){
    TokenParser parser;
    std::vector<uint64_t> numbers;
    std::vector<std::string> strings;
    std::string test_text = "afqwrdsggsd";
    
    parser.Parse(test_text, numbers, strings);
    ASSERT_EQ(numbers.size(), 0);
    ASSERT_EQ(strings.size(), 0);
}


//Проверяем, что callback для старта добавил в начало нужные вещи, а в конце числа были отсортированы
TEST(TestParser, TestStartEndCallback){
    TokenParser parser;
    std::vector<uint64_t> numbers;
    std::vector<std::string> strings;
    parser.SetDigitTokenCallback(digit_callback);
    parser.SetStringTokenCallback(string_callback);
    parser.SetStartCallback(start_callback);
    parser.SetEndCallback(end_callback);

    std::string test_text = "afqwrdsggsd -2 1451 002\t\t\n";
    std::vector<std::string> strings_out = {"start" ,"afqwrdsggsd", "-2"};
    std::vector<uint64_t> numbers_out = {0ull , 2ull, 1451ull};

    parser.Parse(test_text, numbers, strings);
    ASSERT_EQ(numbers.size(), 3);
    ASSERT_EQ(strings.size(), 3);
    for (size_t i; i<strings_out.size(); i++){
        ASSERT_EQ(strings[i], strings_out[i]);
        ASSERT_EQ(numbers[i], numbers_out[i]);
    }
}


TEST(TestParser, TestEmptyText){
    TokenParser parser;
    std::vector<uint64_t> numbers;
    std::vector<std::string> strings;
    parser.SetDigitTokenCallback(digit_callback);
    parser.SetStringTokenCallback(string_callback);
    std::string test_text = "";
    
    parser.Parse(test_text, numbers, strings);
    ASSERT_EQ(numbers.size(), 0);
    ASSERT_EQ(strings.size(), 0);

    test_text = "      ";
    parser.Parse(test_text, numbers, strings);
    ASSERT_EQ(numbers.size(), 0);
    ASSERT_EQ(strings.size(), 0);
}


int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
