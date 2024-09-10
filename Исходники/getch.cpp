extern "C" int __cdecl _kbhit_nolock()
{
    // If a character has been pushed back, return TRUE:
    if (chbuf != -1)
        return TRUE;

    if (__dcrt_lowio_console_input_handle == -2)
        __dcrt_lowio_initialize_console_input();

    if (__dcrt_lowio_console_input_handle == -1)
        return FALSE;

    HANDLE const console_handle = reinterpret_cast<HANDLE>(__dcrt_lowio_console_input_handle);

    // Peek at all pending console events:
    DWORD num_pending;
    if (GetNumberOfConsoleInputEvents(console_handle, &num_pending) == 0)
        return FALSE;

    if (num_pending == 0)
        return FALSE;

    __crt_scoped_stack_ptr<INPUT_RECORD> const input_buffer(_malloca_crt_t(INPUT_RECORD, num_pending));
    if (input_buffer.get() == nullptr)
        return FALSE;

    DWORD num_peeked;
    if (PeekConsoleInput(console_handle, input_buffer.get(), num_pending, &num_peeked) == 0)
        return FALSE;

    if (num_peeked == 0 || num_peeked > num_pending)
        return FALSE;

    // Scan all of the peeked events to determine if any is a key event
    // that should be recognized:
    for (INPUT_RECORD* p = input_buffer.get(); num_peeked > 0; --num_peeked, ++p)
    {
        if (p->EventType != KEY_EVENT)
            continue;

        if (!p->Event.KeyEvent.bKeyDown)
            continue;

        if (p->Event.KeyEvent.uChar.AsciiChar == 0 &&
            _getextendedkeycode(&p->Event.KeyEvent) == nullptr)
            continue;

        return TRUE;
    }

    return FALSE;
}