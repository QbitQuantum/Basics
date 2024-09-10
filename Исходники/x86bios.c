BOOLEAN
NTAPI
HalpBiosDisplayReset(VOID)
{
#if 0
    X86_BIOS_REGISTERS Registers;
    ULONG OldEflags;

    /* Save flags and disable interrupts */
    OldEflags = __readeflags();
    _disable();

    /* Set AH = 0 (Set video mode), AL = 0x12 (640x480x16 vga) */
    Registers.Eax = 0x12;

    /* Call INT 0x10 */
    x86BiosCall(0x10, &Registers);

    // FIXME: check result

    /* Restore previous flags */
    __writeeflags(OldEflags);
#endif
    return TRUE;
}