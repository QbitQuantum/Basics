uint64_t osNumaMask(void)
{
    uint64_t numaMask;
    if (!GetNumaNodeProcessorMask(0, &numaMask))
    {
        return 1;
    }
    return numaMask;
}