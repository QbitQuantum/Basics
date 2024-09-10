bool tryToDisassemble(const MacroAssemblerCodePtr<DisassemblyPtrTag>& codePtr, size_t size, const char* prefix, PrintStream& out)
{
    A64DOpcode arm64Opcode;

    uint32_t* currentPC = codePtr.untaggedExecutableAddress<uint32_t*>();
    size_t byteCount = size;

    while (byteCount) {
        char pcString[20];
        snprintf(pcString, sizeof(pcString), "0x%lx", reinterpret_cast<unsigned long>(currentPC));
        out.printf("%s%16s: %s\n", prefix, pcString, arm64Opcode.disassemble(currentPC));
        currentPC++;
        byteCount -= sizeof(uint32_t);
    }

    return true;
}