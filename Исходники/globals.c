char *Loc::toChars()
{
    OutBuffer buf;

    if (filename)
    {
        buf.printf("%s", filename);
    }

    if (linnum)
    {
        buf.printf("(%d", linnum);
        if (global.params.showColumns && charnum)
            buf.printf(",%d", charnum);
        buf.writeByte(')');
    }
    return buf.extractString();
}