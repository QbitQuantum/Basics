FileOutputStream::~FileOutputStream()
{
    flushBuffer();
    flushInternal();
    closeHandle();
}