static void retrace_glXCreateContext(trace::Call &call) {
    unsigned long long orig_context = call.ret->toUIntPtr();
    if (!orig_context) {
        return;
    }

    Context *share_context = getContext(call.arg(2).toUIntPtr());

    Context *context = glretrace::createContext(share_context);
    context_map[orig_context] = context;
}