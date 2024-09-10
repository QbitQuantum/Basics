bool SignalHandler::processing() {
    signal_printf("%s[%d]: checking whether processing for SH %s: idle_flag %d, waiting for callback %d, wait_flag %d\n", 
                  FILE__, __LINE__, getThreadStr(getThreadID()), idle(), waitingForCallback(), wait_flag);

    if (idle()) return false;
    if (waitingForCallback()) return false;
    if (wait_flag) return false;

    return true;
}