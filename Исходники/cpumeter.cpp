TInt CCpuMeter::Construct()
{
    iNumCpus = NumberOfCpus();
    iNullThreads = (RThread*)User::AllocZ(iNumCpus*sizeof(RThread));
    iDelta = (TInt*)User::AllocZ(iNumCpus*sizeof(TInt));
    iMeas[0] = (TTimeIntervalMicroSeconds*)User::AllocZ(iNumCpus*sizeof(TTimeIntervalMicroSeconds));
    iMeas[1] = (TTimeIntervalMicroSeconds*)User::AllocZ(iNumCpus*sizeof(TTimeIntervalMicroSeconds));
    if (!iNullThreads || !iDelta || !iMeas[0] || !iMeas[1])
        return KErrNoMemory;
    TFullName kname;
    _LIT(KLitKernelName, "ekern.exe*");
    _LIT(KLitNull, "::Null");
    TFindProcess fp(KLitKernelName);
    test_KErrNone(fp.Next(kname));
    test.Printf(_L("Found kernel process: %S\n"), &kname);
    kname.Append(KLitNull);
    TInt i;
    for (i=0; i<iNumCpus; ++i)
    {
        TFullName tname(kname);
        TFullName tname2;
        if (i>0)
            tname.AppendNum(i);
        TFindThread ft(tname);
        test_KErrNone(ft.Next(tname2));
        TInt r = iNullThreads[i].Open(ft);
        test_KErrNone(r);
        iNullThreads[i].FullName(tname2);
        test.Printf(_L("Found and opened %S\n"), &tname2);
    }
    for (i=0; i<iNumCpus; ++i)
        iNullThreads[i].GetCpuTime(iMeas[0][i]);
    iNextMeas = 1;
    return KErrNone;
}