static void request_cancel(struct mp_input_src *src)
{
    struct priv *p = src->priv;

    MP_VERBOSE(src, "Exiting...\n");
    atomic_store(&p->cancel_requested, true);

    // The thread might not be peforming I/O at the exact moment when
    // CancelIoEx is called, so call it in a loop until it succeeds or the
    // thread exits
    do {
        if (CancelIoEx(p->file, NULL))
            break;
    } while (WaitForSingleObject(p->thread, 1) != WAIT_OBJECT_0);
}