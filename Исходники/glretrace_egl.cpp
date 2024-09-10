static void retrace_eglMakeCurrent(trace::Call &call) {
    if (!call.ret->toSInt()) {
        // Previously current rendering context and surfaces (if any) remain
        // unchanged.
        return;
    }

    glws::Drawable *new_drawable = getDrawable(call.arg(1).toUIntPtr());
    Context *new_context = getContext(call.arg(3).toUIntPtr());

    // Try to support GL_OES_surfaceless_context by creating a dummy drawable.
    if (new_context && !new_drawable) {
        if (!null_drawable) {
            null_drawable = glretrace::createDrawable(last_profile);
        }
        new_drawable = null_drawable;
    }

    glretrace::makeCurrent(call, new_drawable, new_context);
}