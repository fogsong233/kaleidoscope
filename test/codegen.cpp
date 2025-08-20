#include <gtest/gtest.h>
#include "llvm/Support/raw_ostream.h"
import std;
import kaleidoscope;

using namespace Kaleidoscope;

template <class Exp>
void printCodegen(std::unique_ptr<Exp> exp) {
    static_assert(Util::depTrue<Exp>, "you should not use this");
}

// Overload for types derived from AST::Expr
template <class Exp>
    requires std::is_base_of_v<AST::Expr, Exp>
void printCodegen(std::unique_ptr<Exp> exp) {
    // Implementation for AST::Expr derived types
    if(exp) {
        auto code = exp->codegen();
        if(code)
            code->print(llvm::outs());
    }
}

void printCodegen(std::unique_ptr<AST::Function> func) {
    if(func) {
        auto code = func->codegen();
        if(code)
            code->print(llvm::outs());
    }
}

void printCodegen(std::unique_ptr<AST::Prototype> proto) {
    if(proto) {
        auto code = proto->codegen();
        if(code)
            code->print(llvm::outs());
    }
}

void astParseWithCodegen(std::istream& stream) {
    getNxtToken(stream);
    std::println("start parsing");
    while(true) {
        // std::println("Parse {}", curToken);
        switch(curToken) {
            case Token::tEOF: return;
            // Having top-level semicolons allows the parser know you are done, split.
            case ';': getNxtToken(stream); break;
            case Token::tDEF: {
                auto exp = Parser::parseFuncDefinition(stream);
                printCodegen(std::move(exp));
                break;
            }
            case Token::tEXTERN: {
                auto exp = Parser::parseExtern(stream);
                printCodegen(std::move(exp));
                break;
            }
            default: {
                auto exp = Parser::parseTopLevelExpr(stream);
                printCodegen(std::move(exp));
                break;
            }
        }
    }
}

TEST(CodegenTest, codegen1) {
    std::istringstream input("def foo(x y) x + y\n" "extern bar(x);\n" "foo(1, 2);\n" "bar(3);\n");
    astParseWithCodegen(input);
}

TEST(CodegenTest, codegen2) {
    std::istringstream input("def tst(x) 1 + 2 + x");
    astParseWithCodegen(input);
}

TEST(CodegenTest, codegenWithOpt) {
    std::istringstream input("def test(x) (1+2+x)*(x+(1+2));");
    astParseWithCodegen(input);
}

TEST(CodegenTest, topLevel) {
    std::istringstream input("4 + 5; 3 + 1;");
    astParseWithCodegen(input);
}
