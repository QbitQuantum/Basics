Rewriter* Rewriter::createRewriter(void* ic_rtn_addr, int num_orig_args, int num_temp_regs, const char* debug_name) {
    assert(num_temp_regs <= 2 && "unsupported");

    static StatCounter rewriter_nopatch("rewriter_nopatch");

    ICInfo* ic = getICInfo(ic_rtn_addr);
    if (ic == NULL) {
        rewriter_nopatch.log();
        return NULL;
    }

    assert(ic->getCallingConvention() == llvm::CallingConv::C && "Rewriter[1] only supports the C calling convention!");
    return new Rewriter(ic->startRewrite(debug_name), num_orig_args, num_temp_regs);
}