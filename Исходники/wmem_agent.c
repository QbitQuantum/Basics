static TACommandVerdict wmemcpy_cmd(TAThread thread,TAInputStream stream)
{
    wchar_t* ws1;
    wchar_t* ws2;
    size_t n;
    wchar_t* res;
    
    // Prepare
    ws1 = readPointer(&stream);
    ws2 = readPointer(&stream);
    n = readSize(&stream);
    
    // Execute
    START_TARGET_OPERATION(thread);
    res = wmemcpy( ws1, ws2, n);
    END_TARGET_OPERATION(thread);
    
    // Response
    writePointer(thread, res);
    sendResponse(thread);
    
    return taDefaultVerdict;
}