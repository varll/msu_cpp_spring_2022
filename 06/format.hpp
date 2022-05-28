#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::string process(const char* text, std::vector<std::string>& v){
    std::stringstream new_text;
    for(size_t i = 0; text[i] != '\0'; i++){
        if (text[i] == '{'){
            if (text[i+1] == '}'){
                throw std::runtime_error("value expected");
            }

            i++;
            size_t number = 0;
            while (text[i] != '}'){
                if (!isdigit(text[i])){
                    throw std::runtime_error("number expected");
                }

            number *= 10;
            number += text[i] - '0';
            i++;
            }

            if (number >= v.size()){
                throw std::runtime_error("out of range");
            }

            new_text << v[number];
        }
        else if (text[i] == '}'){
            throw std::runtime_error("expected opening");
        }
        else{
            new_text << text[i];
        }
    }
    return new_text.str();
}

template <typename T>
std::string process(const char* text, std::vector<std::string>& v, T&& arg){
    std::stringstream output;
    output << arg;
    v.push_back(output.str());
    return process(text, v);
}

template <typename T, typename... Args>
std::string process(const char* text, std::vector<std::string>& v, T&& arg, Args&&... args){
    std::stringstream output;
    output << arg;
    v.push_back(output.str());
    
    return process(text, v, std::forward<Args>(args)...);
}

template <typename... Args>
std::string format(const char* text, Args&&... args){
    std::vector<std::string> v;
    return process(text, v, std::forward<Args>(args)...);
}