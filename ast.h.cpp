#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>

enum class ASTNodeType {
    SYS_CONFIG, CLASS_DECL, INIT_BLOCK, FUNCTION_DECL,
    BLOCK, ASSIGNMENT, RETURN_STMT, PRINT_STMT
};

struct ASTNode {
    ASTNodeType type;
    virtual ~ASTNode() = default;
};

struct Assignment : public ASTNode {
    std::string identifier;
    std::string value;

    Assignment(const std::string& id, const std::string& val) {
        type = ASTNodeType::ASSIGNMENT;
        identifier = id;
        value = val;
    }
};

struct ReturnStmt : public ASTNode {
    std::string returnValue;

    ReturnStmt(const std::string& val) {
        type = ASTNodeType::RETURN_STMT;
        returnValue = val;
    }
};

struct FunctionDecl : public ASTNode {
    std::string name;
    std::vector<std::shared_ptr<ASTNode>> body;

    FunctionDecl(const std::string& n) {
        type = ASTNodeType::FUNCTION_DECL;
        name = n;
    }
};

struct ClassDecl : public ASTNode {
    std::string name;
    std::vector<std::shared_ptr<ASTNode>> members;

    ClassDecl(const std::string& n) {
        type = ASTNodeType::CLASS_DECL;
        name = n;
    }
};

#endif
