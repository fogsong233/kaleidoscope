#include <gtest/gtest.h>
import std;
import kaleidoscope;

namespace {
using namespace Kaleidoscope;

TEST(AST, checkAST1) {
    using namespace Parser;
    auto ss1 = std::stringstream{"def foo(x y) x+foo(y, 4.0);"};
    astParse(ss1);
    auto ss2 = std::stringstream{"extern foo(x y);"};
    astParse(ss2);
    auto ss3 = std::stringstream{"foo(1.0, 2.0);"};
    astParse(ss3);
    auto ss4 = std::stringstream{"def foo(x y) x+y y;"};
    astParse(ss4);
}

TEST(AST, checkAST2) {
    using namespace Parser;
    auto ss5 = std::istringstream("def foo(x y) x + y \n" "extern bar(x);\n" "foo(1,2);\n");
    astParse(ss5);
}
}  // namespace
