VOID vReleaseCrtc(PDEV* ppdev)
{
    // 80x/805i/928 and 928PCI chips have a bug where if I/O registers
    // are left unlocked after accessing them, writes to memory with
    // similar addresses can cause writes to I/O registers.  The problem
    // registers are 0x40, 0x58, 0x59 and 0x5c.  We will simply always
    // leave the index set to an innocuous register (namely, the text
    // mode cursor start scan line):

    OUTP(ppdev->pjIoBase, CRTC_INDEX, 0xa);

    if (!gbCrtcCriticalSection)
        RIP("Hadn't yet acquired Critical Section");
    gbCrtcCriticalSection = FALSE;
    EngReleaseSemaphore(ppdev->csCrtc);
}