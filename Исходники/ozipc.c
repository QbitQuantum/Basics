s64int OzSend(s64int pid, void *buffer, u64int size)
{
    return Send(lookupPid(pid), buffer, size);
}