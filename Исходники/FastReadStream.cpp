FastReadStream::~FastReadStream() {
    delete pHeaders;
    if (pBuffer) VirtualFree(pBuffer, 0, MEM_RELEASE);
}