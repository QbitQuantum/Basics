static TACommandVerdict wcsspn_cmd(TAThread thread,TAInputStream stream)
{
    wchar_t* ws1;
    wchar_t* ws2;
    size_t res;

    // Prepare
    ws1 = (wchar_t*)readPointer(&stream);
    ws2 = (wchar_t*)readPointer(&stream);

    START_TARGET_OPERATION(thread);

    // Execute
    res = wcsspn(ws1, ws2);

    END_TARGET_OPERATION(thread);

    // Response
    writeSize(thread, res);
    sendResponse(thread);

    return taDefaultVerdict;
}