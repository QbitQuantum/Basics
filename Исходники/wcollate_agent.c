static TACommandVerdict wcscoll_cmd(TAThread thread, TAInputStream stream)
{
    wchar_t* ws1;
    wchar_t* ws2;
    int res;
    int save_errno;

    // Prepare
    ws1 = ta_wcsalign(readWString(&stream)); //align on copy
    ws2 = ta_wcsalign(readWString(&stream)); //align on copy

    START_TARGET_OPERATION(thread);

    // Execute
    errno = 0;
    res = wcscoll(ws1, ws2);
    save_errno = errno;

    END_TARGET_OPERATION(thread);

    // Response
    writeInt(thread, res);
    writeInt(thread, save_errno);

    sendResponse(thread);
    
    ta_dealloc_memory(ws1);
    ta_dealloc_memory(ws2);

    return taDefaultVerdict;
}