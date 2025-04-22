#include "ast.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <iostream>

using namespace llvm;

LLVMContext context;
IRBuilder<> builder(context);
std::unique_ptr<Module> module = std::make_unique<Module>("Windstrom", context);

void generateLLVM(const std::shared_ptr<ASTNode>& node) {
    if (node->type == ASTNodeType::CLASS_DECL) {
        auto cls = std::static_pointer_cast<ClassDecl>(node);
        for (auto& member : cls->members) {
            if (member->type == ASTNodeType::FUNCTION_DECL) {
                auto func = std::static_pointer_cast<FunctionDecl>(member);
                FunctionType* funcType = FunctionType::get(builder.getVoidTy(), false);
                Function* function = Function::Create(funcType, Function::ExternalLinkage, func->name, module.get());

                BasicBlock* entry = BasicBlock::Create(context, "entry", function);
                builder.SetInsertPoint(entry);

                for (auto& stmt : func->body) {
                    if (stmt->type == ASTNodeType::RETURN_STMT) {
                        builder.CreateRetVoid();
                    }
                }
            }
        }
    }
}
