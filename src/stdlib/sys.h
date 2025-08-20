#ifndef sys_H
#define sys_H

// Your code here

#include <cstdlib>
#include <fstream>   // std::ifstream, std::ofstream
#include <sstream>   // std::stringstream
#include <iostream>  // std::cout, std::cerr
#include "./str.h"
#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

/// putchard - putchar that takes a double and returns 0.
extern "C" {
    inline DLLEXPORT double ext(double x) {
        if(x < 1)
            return 1;
        std::println("GoodBye~");
        std::exit(0);
        return 0;
    }

    inline DLLEXPORT double cat(double pathD) {
        auto path = doubleToStr(pathD);
        std::println("path is {}", path);
        std::ifstream file(path);
        if(!file)
            return 1;
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::println("{}", buffer.str());
        return 0;
    }
};

#endif  // str_H
