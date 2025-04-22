#include "lexer.h"
#include <iostream>

int main() {
    std::string code = R"(
        SYS_CONFIG {
            ENABLE_LOGGING = true;
            THREAD_COUNT = 8;
        }

        CLASS : NeuralNet {
            INIT : Layer {
                LAYER_SIZE = 128;
                ACTIVATION = "ReLU";
            }
        }
    )";

    Lexer lexer(code);
    auto tokens = lexer.tokenize();

    for (const auto& token : tokens) {
        std::cout << "Token: [" << (int)token.type << "] - " << token.value << "\n";
    }

    return 0;
}
