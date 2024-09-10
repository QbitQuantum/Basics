void IoCompletionPortScheduler::registerDevice(
    SharedRandomAccessDevice pDevice)
{
    int hFile = pDevice->getHandle();
    if (hFile == -1) {
        return;
    }
    if (!CreateIoCompletionPort(
            HANDLE(hFile),
            hCompletionPort,
            0,
            threads.size()))
    {
        throw SysCallExcn("CreateIoCompletionPort failed for device");
    }

    // REVIEW:  is it OK to do nothing for unregister?
}