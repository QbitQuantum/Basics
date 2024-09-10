bool tryToDisassemble(const MacroAssemblerCodePtr& codePtr, size_t size, const char* prefix, PrintStream& out)
{
    ud_t disassembler;
    ud_init(&disassembler);
    ud_set_input_buffer(&disassembler, static_cast<unsigned char*>(codePtr.executableAddress()), size);
#if CPU(X86_64)
    ud_set_mode(&disassembler, 64);
#else
    ud_set_mode(&disassembler, 32);
#endif
    ud_set_pc(&disassembler, bitwise_cast<uintptr_t>(codePtr.executableAddress()));
    ud_set_syntax(&disassembler, UD_SYN_ATT);
    
    uint64_t currentPC = disassembler.pc;
    while (ud_disassemble(&disassembler)) {
        char pcString[20];
        print(pcString, sizeof(pcString), currentPC);
        out.printf("%s%16s: %s\n", prefix, pcString, ud_insn_asm(&disassembler));
        currentPC = disassembler.pc;
    }
    
    return true;
}