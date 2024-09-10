int entrypoint() {
        struct DIS_fixed disasm_data;
        uint32_t ep = getEntryPoint();
        uint32_t remaining_size = getFilesize() - ep;
        uint32_t current_offset = DisassembleAt(&disasm_data, ep, remaining_size);


        return 0;
}