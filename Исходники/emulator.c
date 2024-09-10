VOID EmulatorResume(VOID)
{
    /* Resume the VDM */
    ResumeEventThread();
    VgaRefreshDisplay();
    VDDResumeUserHook();
}