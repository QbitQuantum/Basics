AudioConverterStream::~AudioConverterStream()
{
    if (isProxy)
    {
        return;
    }

    delete subConverter;
    acmStreamUnprepareHeader(stream, &header, 0);
    acmStreamClose(stream, 0);
    free(outBuffer);
}