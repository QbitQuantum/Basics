static TACommandVerdict tgammal_cmd(TAThread thread,TAInputStream stream)
{
    long double x, res;

    x = readLongDouble(&stream);

    START_TARGET_OPERATION(thread);

    errno = 0;
    res = tgammal(x);

    END_TARGET_OPERATION(thread);

    writeInt(thread, errno);
    writeLongDouble(thread, res);
    sendResponse(thread);

    return taDefaultVerdict;
}