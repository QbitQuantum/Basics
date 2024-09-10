static void retrace_wglGetPbufferDCARB(trace::Call &call) {
    unsigned long long orig_hdc = call.ret->toUIntPtr();
    if (!orig_hdc) {
        return;
    }

    glws::Drawable *pbuffer = pbuffer_map[call.arg(0).toUIntPtr()];

    drawable_map[orig_hdc] = pbuffer;
}