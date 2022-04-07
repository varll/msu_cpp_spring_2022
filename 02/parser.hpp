#include <iostream>
#include <functional>
#include <string>

using DigitTokenCallback = std::function<void(uint64_t)>;
using StringTokenCallback = std::function<void(std::string)>;
using Callback = std::function<void()>;

class TokenParser
{
public:
    DigitTokenCallback digit_callback;
    StringTokenCallback string_callback;
    Callback start_callback;
    Callback end_callback;

    TokenParser();

    // Устанавливаем callback-функцию перед стартом парсинга.
    void SetStartCallback(Callback func);

    // Устанавливаем callback-функцию после окончания парсинга.
    void SetEndCallback(Callback func);

    // Устанавливаем callback-функцию для обработки чисел.
    void SetDigitTokenCallback(DigitTokenCallback func);

    void SetStringTokenCallback(StringTokenCallback func);

    bool IsULLINT64(const std::string &token);

    void Parse(const std::string &text);
};