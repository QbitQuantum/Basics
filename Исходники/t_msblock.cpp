void TTestMsBlock::tFileAccess()
    {
    test.Start(_L("tFileAccess\n"));

    test.Next(_L("DriveInfo"));
    PrintDrvInfo(fsSession, msDrive->DriveNumber());

    TVolumeInfo volInfo;
    TInt err = fsSession.Volume(volInfo);
    test(err == KErrNone);

    test.Printf(_L("Memory 'in use' = %lx\n"), (volInfo.iSize - volInfo.iFree));
    test.Printf(_L("volInfo.iSize = %lx\n"), volInfo.iSize);
    test.Printf(_L("volInfo.iFree = %lx\n"), volInfo.iFree);

    //-- 1. create a file
    _LIT(KFile, "\\test_file.file");
    const TUint KFileSz = 54321;

    test.Next(_L("Write file\n"));
    err = CreateCheckableStuffedFile(fsSession, KFile, KFileSz);
    test_KErrNone(err);

    //-- 2. verify the file, just in case.
    test.Next(_L("Verify file\n"));
    err = VerifyCheckableFile(fsSession, KFile);
    test_KErrNone(err);

    //-- 3. delete the file
    test.Next(_L("Delete file\n"));
    fsSession.Delete(KFile);
    test.End();
    }