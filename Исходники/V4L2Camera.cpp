MemoryStream::MemoryStream(char* buf, size_t sz)
    : buffer(buf), size(sz), bytesWritten(0)
{
    if ((file = pipe(pipefd) ? NULL : fdopen(pipefd[1], "w")))
        createThread(runThread, this);
}