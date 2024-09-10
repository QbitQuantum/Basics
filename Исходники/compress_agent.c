static TACommandVerdict compress2_cmd(TAThread thread,TAInputStream stream)
{
    Bytef * dest, *source;
    uLongf destLen, sourceLen;
    int res, level;

    dest = readPointer(&stream);
    destLen = readULong(&stream);
    source = readPointer(&stream);
    sourceLen = readULong(&stream);
    level = readInt(&stream);

    ta_debug_printf("level==%d\n", level);
    ta_debug_printf("source==%s\n", source);

    START_TARGET_OPERATION(thread);

    if(level==-1)
        res = compress2(dest, &destLen, source, sourceLen,
                                                Z_DEFAULT_COMPRESSION);
    else
        res = compress2(dest, &destLen, source, sourceLen, level);

    END_TARGET_OPERATION(thread);

    ta_debug_printf("dest==%s\n", dest);

    writePointer(thread, dest);
    writeULong(thread, destLen);
    writeInt(thread, res);

    sendResponse(thread);

    return taDefaultVerdict;
}