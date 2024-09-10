int
InterruptMan_RegisterProcess(UID pid,
                             int irq,
                             int cnt) {

    ProcessInformation *pInfo = NULL;
    if(GetProcessReference(pid, &pInfo) != ProcessErrors_None)
        return -1;

    LockSpinlock(pInfo->lock);

    //Mark that this process is using interrupts
    pInfo->InterruptsUsed = 1;

    for(int i = irq; i < irq + cnt; i++) {

        bool irq_filled = FALSE;
        for(uint32_t j = 0; j < MAX_SUBSCRIBERS; j++) {
            if(irq_subscriber_pids[i][j] == 0) {
                irq_subscriber_pids[i][j] = pid;
                irq_filled = TRUE;
                SetInterruptEnableMode(i, TRUE);
                break;
            }
        }

        if(irq_filled == FALSE)
            __asm__ ("cli\n\thlt");

    }

    UnlockSpinlock(pInfo->lock);
    return 0;
}