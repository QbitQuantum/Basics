void StackVisitor::Frame::print(int indent)
{
    if (!this->callFrame()) {
        log(indent, "frame 0x0\n");
        return;
    }

    CodeBlock* codeBlock = this->codeBlock();
    logF(indent, "frame %p {\n", this->callFrame());

    {
        indent++;

        CallFrame* callFrame = m_callFrame;
        CallFrame* callerFrame = this->callerFrame();
        void* returnPC = callFrame->hasReturnPC() ? callFrame->returnPC().value() : nullptr;

        log(indent, "name: ", functionName(), "\n");
        log(indent, "sourceURL: ", sourceURL(), "\n");

        bool isInlined = false;
#if ENABLE(DFG_JIT)
        isInlined = isInlinedFrame();
        log(indent, "isInlinedFrame: ", isInlinedFrame(), "\n");
        if (isInlinedFrame())
            logF(indent, "InlineCallFrame: %p\n", m_inlineCallFrame);
#endif

        logF(indent, "callee: %p\n", callee());
        logF(indent, "returnPC: %p\n", returnPC);
        logF(indent, "callerFrame: %p\n", callerFrame);
        unsigned locationRawBits = callFrame->callSiteAsRawBits();
        logF(indent, "rawLocationBits: %u 0x%x\n", locationRawBits, locationRawBits);
        logF(indent, "codeBlock: %p ", codeBlock);
        if (codeBlock)
            dataLog(*codeBlock);
        dataLog("\n");
        if (codeBlock && !isInlined) {
            indent++;

            if (callFrame->callSiteBitsAreBytecodeOffset()) {
                unsigned bytecodeOffset = callFrame->bytecodeOffset();
                log(indent, "bytecodeOffset: ", bytecodeOffset, " of ", codeBlock->instructions().size(), "\n");
#if ENABLE(DFG_JIT)
            } else {
                log(indent, "hasCodeOrigins: ", codeBlock->hasCodeOrigins(), "\n");
                if (codeBlock->hasCodeOrigins()) {
                    CallSiteIndex callSiteIndex = callFrame->callSiteIndex();
                    log(indent, "callSiteIndex: ", callSiteIndex.bits(), " of ", codeBlock->codeOrigins().size(), "\n");

                    JITCode::JITType jitType = codeBlock->jitType();
                    if (jitType != JITCode::FTLJIT) {
                        JITCode* jitCode = codeBlock->jitCode().get();
                        logF(indent, "jitCode: %p start %p end %p\n", jitCode, jitCode->start(), jitCode->end());
                    }
                }
#endif
            }
            unsigned line = 0;
            unsigned column = 0;
            computeLineAndColumn(line, column);
            log(indent, "line: ", line, "\n");
            log(indent, "column: ", column, "\n");

            indent--;
        }
        indent--;
    }
    log(indent, "}\n");
}