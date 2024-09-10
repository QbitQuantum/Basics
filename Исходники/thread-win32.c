static void init_main_thread(void *addr)
{
    struct regs *context = (struct regs*)addr;
    /* we must convert the current main thread to a fiber to be able to
     * schedule other fibers */
    context->uc = ConvertThreadToFiber(NULL);
    context->stack_size = 0;
}