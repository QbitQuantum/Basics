static int walk_stack (MonoDomain *domain, MonoContext *ctx, MonoJitInfo *jit_info, void *user_data) {
    MemWriter *writer = (MemWriter*)user_data;
    MonoMethod *method =mono_jit_info_get_method (jit_info);
    if (!method) {
        writer->sprintf("%s", "jit_info no method!");
        return 0;
    }
    char const *m = get_method_image_name (method);
    m = m ? m : "NO_IMAGE_NAME";
    char const *n = mono_method_full_name (method, 1);
    if (n) {
        writer->sprintf ("[%s] %s [%08X]\n", m, n, mono_method_get_token (method));
        g_free (n);
    } else {
        writer->sprintf ("[%s] %s [%08X]\n", m, "NO_METHOD_NAME", mono_method_get_token (method));
    }
    return 0; /*一直walk, 直到栈帧尽头*/
}