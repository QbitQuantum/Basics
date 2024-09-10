GLDEF_C void CallTestsL(void)
//
// Call all tests
//
{
    test.Title();
    test.Start(_L("Start Benchmarking ..."));

    test.Next(gSessionPath);

    ParseCommandLine();

    AllocateBuffers();
    RProcess().SetPriority(EPriorityBackground);

    TInt r = HAL::Get(HAL::EFastCounterFrequency, gFastCounterFreq);
    test_KErrNone(r);
    test.Printf(_L("HAL::EFastCounterFrequency %d\n"), gFastCounterFreq);

    test.Printf(_L("gReadCachingOn %d  gWriteCachingOn %d gFlushAfterWrite %d gFileSequentialModeOn %d\n"),
                gReadCachingOn, gWriteCachingOn, gFlushAfterWrite, gFileSequentialModeOn);

    TestFileSeek();

    // read once
    TestFileRead(KMaxFileSize, gMisalignedReadWrites, EFalse);

    // re-read
    TestFileRead(KMaxFileSize, gMisalignedReadWrites, ETrue);

    TestFileReadCPU(gMisalignedReadWrites);

    // append to file
    TestFileWrite(KMaxFileSize, gMisalignedReadWrites, EFalse);

    // update (overwrite) file
    TestFileWrite(KMaxFileSize, gMisalignedReadWrites, ETrue);

    TestFileWriteCPU(gMisalignedReadWrites);

    TestFileDelete();

//	TestDirRead();
//	PrintDirResults();
#ifdef SYMBIAN_ENABLE_64_BIT_FILE_SERVER_API
    TestLargeFileDelete();
#endif //SYMBIAN_ENABLE_64_BIT_FILE_SERVER_API

    TestMkDir();

    RecursiveRmDir(gSessionPath);

    DeAllocateBuffers();

    test.End();
    test.Close();
}