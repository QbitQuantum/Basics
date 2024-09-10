AST::Ptr SymEval::simplifyStack(AST::Ptr ast, Address addr, ParseAPI::Function *func, ParseAPI::Block *block) {
    if (!ast) return ast;
    // Let's experiment with simplification
    StackAnalysis sA(func);
    StackAnalysis::Height sp = sA.findSP(block, addr);
    StackAnalysis::Height fp = sA.find(block, addr, MachRegister::getFramePointer(func->isrc()->getArch()));

    StackVisitor sv(addr, func, sp, fp);

    AST::Ptr simplified = ast->accept(&sv);

    return simplified;
}