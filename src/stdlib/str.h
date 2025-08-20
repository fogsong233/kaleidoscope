#ifndef str_H
#define str_H

// Your code here

#include <print>
#include <string>
#include <cstdint>
#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

inline std::string doubleToStr(double X) {
    auto schars = std::to_string(uint_least64_t(X));
    auto chars = std::string(schars.begin() + 1, schars.end());
    std::println("get chars {}", chars);
    auto len = chars.length();
    std::string txt;
    for(int i = 0; i < len; i += 3) {
        char asciiCode = std::stoi(chars.substr(i, 3));
        std::println("get char {}", chars.substr(i, 3));
        txt += asciiCode;
    }
    return txt;
}

/// putchard - putchar that takes a double and returns 0.
extern "C" {
    inline DLLEXPORT double print(double X) {
        std::println("from kaleidoscope: {}", doubleToStr(X));
        return 0;
    }
};

#endif  // str_H
