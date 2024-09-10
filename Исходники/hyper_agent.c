static TACommandVerdict tanhl_cmd(TAThread thread,TAInputStream stream)
{
    long double x, res;

    // Prepare

    x = readLongDouble(&stream);
    errno = 0;
    
    START_TARGET_OPERATION(thread);
    
    // Execute

    res = tanhl(x);
    
    END_TARGET_OPERATION(thread);
    
    // Response
    
    writeLongDouble(thread, res);
    writeInt(thread, errno);

    sendResponse(thread);
    return taDefaultVerdict;
}