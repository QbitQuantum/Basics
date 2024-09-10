// Get the process ID of the process.
uint32_t GCToOSInterface::GetCurrentProcessId()
{
    return getpid();
}