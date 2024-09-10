uint32_t ranval(ranctx* x)
{
    spinLockLock(&x->lock);
    if (UNLIKELY(!x->initialized)) {
        x->initialized = true;
        char c;
        uint32_t seed = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&c));
        seed ^= static_cast<uint32_t>(getCurrentProcessID());
        x->a = 0xf1ea5eed;
        x->b = x->c = x->d = seed;
        for (int i = 0; i < 20; ++i) {
            (void) ranvalInternal(x);
        }
    }
    uint32_t ret = ranvalInternal(x);
    spinLockUnlock(&x->lock);
    return ret;
}