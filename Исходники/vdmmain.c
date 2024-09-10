VOID
NTAPI
INIT_FUNCTION
Ki386VdmEnablePentiumExtentions(IN BOOLEAN Enable)
{
    ULONG EFlags, Cr4;
    
    /* Save interrupt state and disable them */
    EFlags = __readeflags();
    _disable();
    
    /* Enable or disable VME as required */
    Cr4 = __readcr4();
    __writecr4(Enable ? Cr4 | CR4_VME : Cr4 & ~CR4_VME);
    
    /* Restore interrupt state */
    __writeeflags(EFlags);
}