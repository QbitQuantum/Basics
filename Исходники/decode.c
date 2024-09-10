int main(int argc, char *argv[])
{
    double res = 0.;
    int i;
#ifndef X64
    int j;
#endif
    char *buf;
#ifdef LINUX
    stack_t sigstack;
#endif

#ifdef USE_DYNAMO
    dynamorio_app_init();
    dynamorio_app_start();
#endif
  
#ifdef LINUX
    /* our modrm16 tests clobber esp so we need an alternate stack */
    sigstack.ss_sp = (char *) malloc(ALT_STACK_SIZE);
    sigstack.ss_size = ALT_STACK_SIZE;
    sigstack.ss_flags = SS_ONSTACK;
    i = sigaltstack(&sigstack, NULL);
    assert(i == 0);
    intercept_signal(SIGILL, (handler_3_t) signal_handler, true);
    intercept_signal(SIGSEGV, (handler_3_t) signal_handler, true);
#else
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) our_top_handler);
#endif

    buf = allocate_mem(7*256+1, ALLOW_READ|ALLOW_WRITE|ALLOW_EXEC);
    assert(buf != NULL);

#ifndef X64
    print("Jumping to a sequence of every addr16 modrm byte\n");
    for (j=0; j<256; j++) {
        int mod = ((j >> 6) & 0x3); /* top 2 bits */
        int reg = ((j >> 3) & 0x7); /* middle 3 bits */
        int rm  = (j & 0x7);        /* bottom 3 bits */
# if defined(LINUX) || defined(X64)
        buf[j*7 + 0] = 0x65; /* gs: */
# else
        buf[j*7 + 0] = 0x64; /* fs: */
# endif
        buf[j*7 + 1] = 0x67; /* addr16 */
        buf[j*7 + 2] = 0x8b; /* load */
# ifdef WINDOWS
        /* Windows can't handle stack pointer being off */
        if (reg == 4) { /* xsp */
            buf[j*7 + 3] = j | 0x8;
        } else
            buf[j*7 + 3] = j; /* nearly every single modrm byte */
# else
        buf[j*7 + 3] = j; /* every single modrm byte */
# endif
        if (mod == 1) {
            buf[j*7 + 4] = 0x03; /* disp */
            buf[j*7 + 5] = 0xc3;
        } else if (mod == 2 || (mod == 0 && rm == 6)) {
            buf[j*7 + 4] = 0x03; /* disp */
            buf[j*7 + 5] = 0x00; /* disp */
        } else {
            buf[j*7 + 4] = 0xc3; /* ret */
            buf[j*7 + 5] = 0xc3;
        }
        buf[j*7 + 6] = 0xc3;
    }
    buf[256*7] = 0xcc;
    print_access_vio = false;
    for (j=0; j<256; j++) {
        i = SIGSETJMP(mark);
        if (i == 0)
            test_modrm16(&buf[j*7]);
        else
            continue;
    }
    print("Done with modrm test: tested %d\n", j);
    count = 0;
    print_access_vio = true;
#endif /* !X64 */

    /* multi-byte nop tests (case 9862) */
    i = SIGSETJMP(mark);
    if (i == 0) {
        print("Testing nops\n");
        test_nops();
        print("Done with nops\n");
    }

    /* SSE3 and 3DNow instrs will not run on all processors so we can't have this
     * regression test fully test everything: for now its main use is running
     * manually on the proper machines, or manually verifying decoding of these,
     * but we'll leave as a suite/ regression test.
     */

    /* SSE3 tests: mostly w/ modrm of (%edx) */
    i = SIGSETJMP(mark);
    if (i == 0) {
        print("Testing SSE3\n");
        test_sse3(buf);
        print("Should not get here\n");
    }

    /* 3D-Now tests: mostly w/ modrm of (%ebx) */
    i = SIGSETJMP(mark);
    if (i == 0) {
        print("Testing 3D-Now\n");
        test_3dnow(buf);
        print("Should not get here\n");
    }

    /* case 6962: far call/jmp tests 
     * Note that DR currently gets the target address wrong for all of these
     * since we skip the segment and only care about the address:
     * not going to fix that anytime soon.
     */
    print("Testing far call/jmp\n");
    test_far_cti();

#ifdef WINDOWS /* FIXME i#105: crashing on Linux so disabling for now */
    /* PR 242815: data16 mbr */
    print("Testing data16 mbr\n");
    test_data16_mbr();
#endif

    /* i#1024: rip-rel ind branch */
    print("Testing rip-rel ind branch\n");
    func_ptr = actual_call_target;
    test_rip_rel_ind();

#ifdef LINUX
    free(sigstack.ss_sp);
#endif

    print("All done\n");

#ifdef USE_DYNAMO
    dynamorio_app_stop();
    dynamorio_app_exit();
#endif
    return 0;
}