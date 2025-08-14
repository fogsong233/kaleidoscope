#include <gtest/gtest.h>
import std;
import kaleidoscope;

namespace {
using namespace Kaleidoscope;

TEST(Lexer, CheckToken) {
    auto ss = std::stringstream{"def main"};
    ASSERT_EQ(strParseToToken(ss), Token::tDEF);
    // ASSERT_EQ(strParseToToken(ss), Token::tIDENTIFIER);
    // ASSERT_EQ(strParseToToken(ss), Token::tEOF);
}
}  // namespace
