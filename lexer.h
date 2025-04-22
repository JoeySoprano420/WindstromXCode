#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <unordered_map>

enum class TokenType {
    KEYWORD, IDENTIFIER, SYMBOL, STRING, NUMBER, END_OF_FILE
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    explicit Lexer(const std::string& src);

    std::vector<Token> tokenize();

private:
    std::string source;
    size_t pos;
    char peek();
    char get();
    void skipWhitespace();
    Token nextToken();
};

#endif
