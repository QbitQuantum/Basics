void kmGLSetCurrentContext(void *contextRef)
{
    km_mat4_stack_context *current_context = registerContext(contextRef);
    pthread_setspecific(current_context_key, current_context);
}