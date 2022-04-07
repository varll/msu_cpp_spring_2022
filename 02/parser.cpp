#include "parser.hpp"

TokenParser::TokenParser(){
    digit_callback = nullptr;
    string_callback = nullptr;
    start_callback = nullptr;
    end_callback = nullptr;
}

void TokenParser::SetStartCallback(Callback func){
    start_callback = func;
}

void TokenParser::SetEndCallback(Callback func){
    end_callback = func;
}

void TokenParser::SetDigitTokenCallback(DigitTokenCallback func){
    digit_callback = func;
}

void TokenParser::SetStringTokenCallback(StringTokenCallback func){
    string_callback = func;
}

bool TokenParser::IsULLINT64(const std::string &token){
    const std::string max_value = "18446744073709551615";
    //Токен состоит только из цифр
    for (std::string::const_iterator i = token.begin(); i!=token.end(); i++)
        if (!std::isdigit(*i))
            return false;

    //Токен влезает в uint64_t
    if (token.length() < max_value.length() || (token.length() == max_value.length() && token <= max_value))
        return true;

    return false;
}

void TokenParser::Parse(const std::string &text){
    std::string token;

    if (start_callback != nullptr)
        start_callback();

    std::string::const_iterator i = text.begin();
    while(i != text.end()){
        while ((*i == '\t' || *i == '\n' || *i == ' ') && i != text.end())
            i++;

        while (*i != '\t' && *i != '\n' && *i != ' ' && i != text.end()){
            token += *i;
            i++;
        }

        if(!token.empty()){
            if (IsULLINT64(token)){
                if (digit_callback != nullptr)
                    digit_callback(std::stoull(token));
            }
            else{
                if (string_callback != nullptr)
                    string_callback(token);
            }
            token.clear();
        }
    }

    if(end_callback != nullptr)
        end_callback();
}