#include "parser.h"

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

Token Parser::peek() {
    return current < tokens.size() ? tokens[current] : Token{TokenType::END_OF_FILE, ""};
}

Token Parser::advance() {
    return current < tokens.size() ? tokens[current++] : Token{TokenType::END_OF_FILE, ""};
}

bool Parser::match(TokenType type, const std::string& value) {
    Token token = peek();
    if (token.type == type && (value.empty() || token.value == value)) {
        advance();
        return true;
    }
    return false;
}

std::shared_ptr<ASTNode> Parser::parse() {
    if (match(TokenType::KEYWORD, "CLASS")) return parseClass();
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseClass() {
    match(TokenType::SYMBOL, ":");
    std::string name = advance().value;
    auto cls = std::make_shared<ClassDecl>(name);

    if (match(TokenType::SYMBOL, "{")) {
        while (!match(TokenType::SYMBOL, "}")) {
            if (match(TokenType::KEYWORD, "FUNCTION")) {
                cls->members.push_back(parseFunction());
            } else {
                advance(); // Skip for now
            }
        }
    }

    return cls;
}

std::shared_ptr<ASTNode> Parser::parseFunction() {
    match(TokenType::SYMBOL, ":");
    std::string name = advance().value;
    auto func = std::make_shared<FunctionDecl>(name);

    if (match(TokenType::SYMBOL, "(")) {
        while (!match(TokenType::SYMBOL, ")")) advance(); // Skip args for now
    }

    if (match(TokenType::SYMBOL, "{")) {
        while (!match(TokenType::SYMBOL, "}")) {
            if (match(TokenType::KEYWORD, "RETURN")) {
                func->body.push_back(parseReturn());
            } else {
                func->body.push_back(parseAssignment());
            }
        }
    }

    return func;
}

std::shared_ptr<ASTNode> Parser::parseAssignment() {
    std::string id = advance().value;
    match(TokenType::SYMBOL, "=");
    std::string val = advance().value;
    match(TokenType::SYMBOL, ";");
    return std::make_shared<Assignment>(id, val);
}

std::shared_ptr<ASTNode> Parser::parseReturn() {
    std::string val = advance().value;
    match(TokenType::SYMBOL, ";");
    return std::make_shared<ReturnStmt>(val);
}
