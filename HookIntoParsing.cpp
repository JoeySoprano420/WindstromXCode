auto ast = parser.parse();
staticCheck(ast);
generateLLVM(ast);
