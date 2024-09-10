Coroutine *qemu_coroutine_self(void)
{
    if (!current) {
        current = &leader.base;
        leader.fiber = ConvertThreadToFiber(NULL);
    }
    return current;
}