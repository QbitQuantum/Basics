SCM_EXPORT void
scm_call_continuation(ScmObj cont, ScmObj ret)
{
    struct scm_continuation_frame *frame;
#if SCM_NESTED_CONTINUATION_ONLY
    ScmObj dst;
#endif
    DECLARE_INTERNAL_FUNCTION("scm_call_continuation");

    frame = CONTINUATION_FRAME(cont);

    if (frame != INVALID_CONTINUATION_OPAQUE
#if SCM_NESTED_CONTINUATION_ONLY
        && (dst = continuation_stack_unwind(cont), CONTINUATIONP(dst))
#endif
        )
    {
        /* Don't refer cont because it may already be invalidated by
         * continuation_stack_unwind(). */
        exit_dynamic_extent(frame->dyn_ext);

        frame->ret_val = ret;
        LONGJMP(frame->c_env, scm_true);
        /* NOTREACHED */
    } else {
        ERR("expired continuation");
    }
}