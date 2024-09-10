static void _fiber_trampoline(unsigned int y, unsigned int x)
{
    hlt_fiber* fiber;

    // Magic from from libtask/task.c to turn the two words back into a pointer.
    unsigned long z;
    z = (x << 16);
    z <<= 16;
    z |= y;
    fiber = (hlt_fiber*)z;

    // Via recycling a fiber can run an arbitrary number of user jobs. So
    // this trampoline is really a loop that yields after it has finished its
    // run() function, and expects a new run function once it's resumed.

    while ( 1 ) {
        assert(fiber->run);

        hlt_fiber_func run = fiber->run;
        void* cookie = fiber->cookie;

        assert(fiber->state == RUNNING);

        if ( ! _setjmp(fiber->trampoline) ) {
            (*run)(fiber, cookie);
        }

        if ( ! _setjmp(fiber->fiber) ) {
            fiber->run = 0;
            fiber->cookie = 0;
            fiber->state = IDLE;
            _longjmp(fiber->parent, 1);
        }
    }

    // Cannot be reached.
    abort();
}