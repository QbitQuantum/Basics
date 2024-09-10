PSHV_GLOBAL_DATA
ShvVpAllocateGlobalData (
    VOID
    )
{
    PHYSICAL_ADDRESS lowest, highest;
    PSHV_GLOBAL_DATA data;
    ULONG cpuCount, size;

    //
    // The entire address range is OK for this allocation
    //
    lowest.QuadPart = 0;
    highest.QuadPart = lowest.QuadPart - 1;

    //
    // Query the number of logical processors, including those potentially in
    // groups other than 0. This allows us to support >64 processors.
    //
    cpuCount = KeQueryActiveProcessorCountEx(ALL_PROCESSOR_GROUPS);

    //
    // Each processor will receive its own slice of per-virtual processor data.
    //
    size = FIELD_OFFSET(SHV_GLOBAL_DATA, VpData) + cpuCount * sizeof(SHV_VP_DATA);

    //
    // Allocate a contiguous chunk of RAM to back this allocation and make sure
    // that it is RW only, instead of RWX, by using the new Windows 8 API.
    //
#if TARGETVERSION > 7
	data = (PSHV_GLOBAL_DATA)MmAllocateContiguousNodeMemory(size,
		lowest,
		highest,
		lowest,
		PAGE_READWRITE,
		MM_ANY_NODE_OK);
#else
	data = (PSHV_GLOBAL_DATA)MmAllocateContiguousMemory(size, highest);
#endif // TARGETVERSION > 7

	if (data != NULL)
    {
        //
        // Zero out the entire data region
        //
        __stosq((PULONGLONG)data, 0, size / sizeof(ULONGLONG));
    }

    //
    // Return what is hopefully a valid pointer, otherwise NULL.
    //
    return data;
}