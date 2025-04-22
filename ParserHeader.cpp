#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    std::shared_ptr<ASTNode> parse();

private:
    std::vector<Token> tokens;
    size_t current;

    Token peek();
    Token advance();
    bool match(TokenType type, const std::string& value = "");
    std::shared_ptr<ASTNode> parseClass();
    std::shared_ptr<ASTNode> parseFunction();
    std::shared_ptr<ASTNode> parseAssignment();
    std::shared_ptr<ASTNode> parseReturn();
};

#endif
