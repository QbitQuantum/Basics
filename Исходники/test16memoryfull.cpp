// The memory gobbler thread
TInt CMBufAsyncMemFull::fThread2(TAny* aInput)
{
    CTest16MemoryFull* pTestObject = (CTest16MemoryFull*)aInput;
    // We need to introduce this new client thread to the MBufMgr
    pTestObject->MBufMgr()->SetContext();

    CTrapCleanup* aCleanup = CTrapCleanup::New();

    //Install active scheduler
    CActiveScheduler* aActSch = new CActiveScheduler;
    if(aActSch==NULL)
    {
        return KErrNoMemory;
    }
    CActiveScheduler::Install(aActSch);

    RTimer aTimer;
    TRequestStatus aTimerStatus;	// Request status associated with timer
    aTimer.CreateLocal();			// Create timer for this thread
    //-------------- substep 1 --------------------

    // Create some random sizes for allocation later
    TInt requested_size[KFactor2];
    for (TInt i=1; i<(KFactor2+1); i++)
    {
        requested_size[i-1] = i * i * KFactor2;
    }

    // Allocate two 5000-bytes long descriptors (Des1 & Des2):"));
    TBuf8<KFactor2*KFactor2*KFactor2> *aDes1=NULL;
    TRAPD(ret, aDes1 = new(ELeave) TBuf8<KFactor2*KFactor2*KFactor2> );
    if(ret!=KErrNone)
    {
        return ret;
    }

    aDes1->SetLength(requested_size[KFactor2-1]);

    //Fill in the Des1 with a pattern:"));
    pTestObject->FillDes(*aDes1, 0, requested_size[KFactor2-1], 2, 2);

#ifdef __CFLOG_ACTIVE
    __CFLOG_DECLARATION_VARIABLE;
    TRAP(ret, __CFLOG_CREATEL);
    if(ret!=KErrNone)
    {
        delete aDes1;
        return ret;
    }
    __CFLOG_OPEN;
#endif

    RMBufAllocator allocator;
    TUint time;

    RMBufChain aChain;
    RMBufChain bChain;
    TInt requestloop = 0;
    TBool isFillMe = ETrue;
    for (TInt i = 0 ; i<1000; i++)
    {

        if (isFillMe)
        {
            pTestObject->iThread2AllocTries++;
            //Use up mbuf memory by appending to a chain
            time = User::FastCounter();
            TRAP(ret,aChain.AllocL(requested_size[requestloop], allocator));
            time = User::FastCounter() - time;
            if (ret != KErrNone)
            {
                isFillMe = EFalse;
                pTestObject->iThread2MemoryFull++;
                pTestObject->iThread2LastMemoryFull = pTestObject->iThread2AllocTries - 1;
            }
            else
            {
                pTestObject->iThread2AllocTime += time;
                //Copy in Des1 into Chain
                aChain.CopyIn(aDes1->LeftTPtr(requested_size[requestloop]));
                if (aChain.Length() != requested_size[requestloop])
                {
                    pTestObject->iThread2SizeFails++;
                }
                // Now grow the chain
                bChain.Append(aChain);
            }
        }
        else
        {
            //Free some memory
            TInt length = bChain.Length();
            if (length > pTestObject->iThread2MaxLen)
            {
                pTestObject->iThread2MaxLen = length;
            }
            TInt trimOffset = length - requested_size[requestloop];
            if (trimOffset > 0)
            {
                time = User::FastCounter();
                bChain.TrimEnd(trimOffset);
                time = User::FastCounter() - time;
                pTestObject->iThread2FreeTime += time;
            }
            else
            {
                isFillMe = ETrue;
            }
        }

        //Sleep for 5ms
        aTimer.After(aTimerStatus,5000);
        User::WaitForRequest(aTimerStatus);

        requestloop++;
        if (requestloop>(KFactor2-1))
        {
            requestloop = 0;
        }
    }
    // Free the memory
    bChain.Free();

    delete aDes1;

    CActiveScheduler::Install(NULL);
    delete aActSch;
    delete aCleanup;

#ifdef __CFLOG_ACTIVE
    __CFLOG_CLOSE;
    __CFLOG_DELETE;
#endif

    return ret;
}