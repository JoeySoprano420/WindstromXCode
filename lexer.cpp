#include "lexer.h"
#include <cctype>

static const std::unordered_map<std::string, TokenType> keywords = {
    {"SYS_CONFIG", TokenType::KEYWORD}, {"CLASS", TokenType::KEYWORD},
    {"INIT", TokenType::KEYWORD}, {"FUNCTION", TokenType::KEYWORD},
    {"MAIN", TokenType::KEYWORD}, {"PRINT", TokenType::KEYWORD},
    {"FOR", TokenType::KEYWORD}, {"IN", TokenType::KEYWORD},
    {"TO", TokenType::KEYWORD}, {"RETURN", TokenType::KEYWORD},
    {"IF", TokenType::KEYWORD}, {"THEN", TokenType::KEYWORD},
    {"BREAK", TokenType::KEYWORD}
};

Lexer::Lexer(const std::string& src) : source(src), pos(0) {}

char Lexer::peek() {
    return pos < source.size() ? source[pos] : '\0';
}

char Lexer::get() {
    return pos < source.size() ? source[pos++] : '\0';
}

void Lexer::skipWhitespace() {
    while (std::isspace(peek())) get();
}

Token Lexer::nextToken() {
    skipWhitespace();
    char c = peek();

    if (std::isalpha(c) || c == '_') {
        std::string ident;
        while (std::isalnum(peek()) || peek() == '_') {
            ident += get();
        }

        if (keywords.count(ident))
            return {keywords.at(ident), ident};
        return {TokenType::IDENTIFIER, ident};
    }

    if (std::isdigit(c)) {
        std::string number;
        while (std::isdigit(peek())) number += get();
        return {TokenType::NUMBER, number};
    }

    if (c == '"') {
        get(); // consume "
        std::string str;
        while (peek() != '"' && peek() != '\0') {
            str += get();
        }
        get(); // consume closing "
        return {TokenType::STRING, str};
    }

    if (std::ispunct(c)) {
        std::string sym(1, get());
        return {TokenType::SYMBOL, sym};
    }

    if (c == '\0') return {TokenType::END_OF_FILE, ""};

    get();
    return {TokenType::END_OF_FILE, ""};
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    Token token;
    do {
        token = nextToken();
        tokens.push_back(token);
    } while (token.type != TokenType::END_OF_FILE);
    return tokens;
}
