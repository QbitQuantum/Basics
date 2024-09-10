static void retrace_memcpy(trace::Call &call) {
    void * dest = toPointer(call.arg(0));
    void * src  = toPointer(call.arg(1));
    size_t n    = call.arg(2).toUInt();

    if (!dest || !src || !n) {
        return;
    }

    memcpy(dest, src, n);
}