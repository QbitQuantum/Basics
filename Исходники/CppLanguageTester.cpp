void CCppLanguageTester::test_cpp_alloc_physical_memory()
{
    MEMORYSTATUS startMemoryStatus = {0}; 
    MEMORYSTATUS afterNewMemoryStatus = {0};
    MEMORYSTATUS afterAccessMemoryStatus = {0};

    GlobalMemoryStatus(&startMemoryStatus);
    
    //申请分配10M的内存空间
    const int nAllocSize = 10 * 1024 * 1024;
    BYTE *pBuff = new BYTE[ nAllocSize ];
    GlobalMemoryStatus(&afterNewMemoryStatus);

    ZeroMemory(pBuff, nAllocSize);
    GlobalMemoryStatus(&afterAccessMemoryStatus);

    delete [] pBuff;

    FTLTRACE(TEXT("Memory Status: Start -> AfterNew -> AfterAccess\n")), 
    FTLTRACE(TEXT("  AvailPhys: %fM -> %fM -> %fM\n"), 
        (float)startMemoryStatus.dwAvailPhys/1024/1024,
        (float)afterNewMemoryStatus.dwAvailPhys/1024/1024,
        (float)afterAccessMemoryStatus.dwAvailPhys/1024/1024);
    FTLTRACE(TEXT("  AvailVirtual: %fM -> %fM -> %fM\n"), 
        (float)startMemoryStatus.dwAvailVirtual/1024/1024,
        (float)afterNewMemoryStatus.dwAvailVirtual/1024/1024,
        (float)afterAccessMemoryStatus.dwAvailVirtual/1024/1024);

    //调用new以后内存即会分配
    CPPUNIT_ASSERT(startMemoryStatus.dwAvailPhys - afterNewMemoryStatus.dwAvailPhys >= nAllocSize);
    
}