bool tryToDisassembleWithLLVM(
    const MacroAssemblerCodePtr& codePtr, size_t size, const char* prefix, PrintStream& out,
    InstructionSubsetHint)
{
    initializeLLVM();
    
    const char* triple;
#if CPU(X86_64)
    triple = "x86_64-apple-darwin";
#elif CPU(X86)
    triple = "x86-apple-darwin";
#elif CPU(ARM64)
    triple = "arm64-apple-darwin";
#else
#error "LLVM disassembler currently not supported on this CPU."
#endif

    char symbolString[symbolStringSize];
    
    LLVMDisasmContextRef disassemblyContext =
        llvm->CreateDisasm(triple, symbolString, 0, 0, symbolLookupCallback);
    RELEASE_ASSERT(disassemblyContext);
    
    char pcString[20];
    char instructionString[1000];
    
    uint8_t* pc = static_cast<uint8_t*>(codePtr.executableAddress());
    uint8_t* end = pc + size;
    
    while (pc < end) {
        snprintf(
            pcString, sizeof(pcString), "0x%lx",
            static_cast<unsigned long>(bitwise_cast<uintptr_t>(pc)));

        size_t instructionSize = llvm->DisasmInstruction(
            disassemblyContext, pc, end - pc, bitwise_cast<uintptr_t>(pc),
            instructionString, sizeof(instructionString));
        
        if (!instructionSize)
            snprintf(instructionString, sizeof(instructionString), ".byte 0x%02x", *pc++);
        else
            pc += instructionSize;
        
        out.printf("%s%16s: %s\n", prefix, pcString, instructionString);
    }
    
    llvm->DisasmDispose(disassemblyContext);
    
    return true;
}