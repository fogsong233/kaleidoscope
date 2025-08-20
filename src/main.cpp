#include "./stdlib/std.h"
import std;
import kaleidoscope;

int main(int argc, char** argv) {
    std::println("testing...");
    print(1046047097);
    cat(1043);
    ext(0);
    using namespace Kaleidoscope;
    initLLVM();
    Parser::defaultBinopPrecedenceCtor();
    Jit::startJitConsole();
    return 0;
}
