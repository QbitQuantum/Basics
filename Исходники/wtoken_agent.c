static TACommandVerdict wcstok_cmd(TAThread thread,TAInputStream stream)
{
    wchar_t* stringp, *buff, *delim, *res;

/*
    freopen(NULL, "a+", stdout);
    orient=fwide(stdout, 0);
    wprintf(L"Before wcstok(wprintf): mode==%ls\n", orient>0?L"Wide": orient<0?L"Byte":L"Non oriented");
    wprintf(L"Test==%ls\n", test);
    ta_debug_printf("Before wcstok(printf): mode==%s\n", orient>0?"Wide": orient<0?"Byte":"Non oriented");
*/    

    // Prepare       
    stringp=(wchar_t*)readPointer(&stream);
    delim=(wchar_t*)readPointer(&stream);
    buff=(wchar_t*)readPointer(&stream);    

    // Execute    
    START_TARGET_OPERATION(thread);
    res = wcstok(stringp, delim, &buff);
    END_TARGET_OPERATION(thread);

    // Response    
    writePointer(thread, res);
    writePointer(thread, buff);

    sendResponse(thread);

    return taDefaultVerdict;
}