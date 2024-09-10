void OutputStream::printf (const char* pf, ...)
{
    unsigned int bufSize = 256;
    HeapBlock <char> buf (bufSize);

    for (;;)
    {
        va_list list;
        va_start (list, pf);

        const int num = CharacterFunctions::vprintf (buf, bufSize, pf, list);

        va_end (list);

        if (num > 0)
        {
            write (buf, num);
            break;
        }
        else if (num == 0)
        {
            break;
        }

        bufSize += 256;
        buf.malloc (bufSize);
    }
}