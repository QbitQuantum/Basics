static TACommandVerdict powl_cmd(TAThread thread,TAInputStream stream)
{
    long double x, y, res;

    // Prepare

    x = readLongDouble(&stream);
    y = readLongDouble(&stream);
    errno = 0;
    
    START_TARGET_OPERATION(thread);
    
    // Execute

    res = powl(x, y);
    
    END_TARGET_OPERATION(thread);
    
    // Response
    
    writeLongDouble(thread, res);
    writeInt(thread, errno);

    sendResponse(thread);
    return taDefaultVerdict;
}