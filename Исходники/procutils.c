__declspec(dllexport) int32_t OS_waitpid(int32_t pid, int32_t *statusp, int32_t flags) {
    _cwait (statusp, pid, WAIT_CHILD);
    return 0;
}