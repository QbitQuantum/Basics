void
ListHookedDevice::terminate(void)
{
    if (! lock_) return;

    {
        IOLockWrapper::ScopedLock lk(lock_);

        last_ = NULL;

        for (int i = 0; i < MAXNUM; ++i) {
            HookedDevice* p = getItem(i);
            if (! p) continue;

            p->terminate();
        }
    }

    reset();

    IOLockWrapper::free(lock_);
}