int32_t sk_atomic_conditional_inc(int32_t* addr) {
    while (true) {
        LONG value = static_cast<int32_t const volatile&>(*addr);
        if (value == 0) {
            return 0;
        }
        if (_InterlockedCompareExchange(reinterpret_cast<LONG*>(addr),
                                        value + 1,
                                        value) == value) {
            return value;
        }
    }
}