static void inline
DisableFPUException (void)
{
    unsigned short usCW;

    /* Some OS/2 PM API calls modify the FPU Control Word,
     * but forget to restore it.
     *
     * This can result in XCPT_FLOAT_INVALID_OPCODE exceptions,
     * so to be sure, we disable Invalid Opcode FPU exception
     * before using FPU stuffs.
     */
    usCW = _control87 (0, 0);
    usCW = usCW | EM_INVALID | 0x80;
    _control87 (usCW, MCW_EM | 0x80);
}