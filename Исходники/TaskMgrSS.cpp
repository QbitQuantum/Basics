BOOL TaskMgrSS::CreateTaskSet(TASKSETFUNC     pFunc,
                              VOID*           pArg,
                              UINT            uTaskCount,
                              TASKSETHANDLE*  pInDepends,
                              UINT            uInDepends,
                              OPTIONAL LPCSTR szSetName,
                              TASKSETHANDLE*  pOutHandle )
{
    TASKSETHANDLE           hSet;
    TASKSETHANDLE           hSetParent = TASKSETHANDLE_INVALID;
    TASKSETHANDLE*          pDepends = pInDepends;
    UINT                    uDepends = uInDepends;
    BOOL                    bResult = FALSE;


    //  Validate incomming parameters
    if( 0 == uTaskCount || NULL == pFunc )
    {
        return FALSE;
    }

    //
    //  Allocate and setup the internal taskset
    //
    hSet = AllocateTaskSet();

    mSets[ hSet ].muRefCount        = 2;
    mSets[ hSet ].muStartCount      = uDepends;
    mSets[ hSet ].mpvArg            = pArg;
    mSets[ hSet ].muSize            = uTaskCount;
    mSets[ hSet ].muCompletionCount = uTaskCount;
    mSets[ hSet ].muTaskId          = uTaskCount;
    mSets[ hSet ].mhTaskset         = hSet;
    mSets[ hSet ].mpFunc            = pFunc;
    mSets[ hSet ].mbCompleted       = FALSE;
    //mSets[ hSet ].mhAssignedSlot    = TASKSETHANDLE_INVALID;

#ifdef PROFILEGPA
    //
    //  Track task name if profiling is enabled
    if( szSetName )
    {
        StringCbCopyA(
            mSets[ hSet ].mszSetName,
            sizeof( mSets[ hSet ].mszSetName ),
            szSetName );
    }
    else
    {
        StringCbCopyA(
            mSets[ hSet ].mszSetName,
            sizeof( mSets[ hSet ].mszSetName ),
            "Unnamed Task" );
    }
#else
    UNREFERENCED_PARAMETER( szSetName );
#endif // PROFILEGPA

    //
    //  Iterate over the dependency list and setup the successor
    //  pointers in each parent to point to this taskset.
    //
	if(uDepends == 0)
	{
		mTaskScheduler.AddTaskSet( hSet, uTaskCount );
	}
    else for( UINT uDepend = 0; uDepend < uDepends; ++uDepend )
    {
        TASKSETHANDLE       hDependsOn = pDepends[ uDepend ];

        if(hDependsOn == TASKSETHANDLE_INVALID)
            continue;

        TaskSet *pDependsOn = &mSets[ hDependsOn ];
        LONG     lPrevCompletion;

        //
        //  A taskset with a new successor is consider incomplete even if it
        //  already has completed.  This mechanism allows us tasksets that are
        //  already done to appear active and capable of spawning successors.
        //
        lPrevCompletion = _InterlockedExchangeAdd( (LONG*)&pDependsOn->muCompletionCount, 1 );

        pDependsOn->mSuccessorsLock.aquire();

        UINT uSuccessor;
        for( uSuccessor = 0; uSuccessor < MAX_SUCCESSORS; ++uSuccessor )
        {
            if( NULL == pDependsOn->Successors[ uSuccessor ] )
            {
                pDependsOn->Successors[ uSuccessor ] = &mSets[ hSet ];
                break;
            }
        }

        //
        //  If the successor list is full we have a problem.  The app
        //  needs to give us more space by increasing MAX_SUCCESSORS
        //
        if( uSuccessor == MAX_SUCCESSORS )
        {
            printf( "Too many successors for this task set.\nIncrease MAX_SUCCESSORS\n" );
            pDependsOn->mSuccessorsLock.release();
            goto Cleanup;
        }

        pDependsOn->mSuccessorsLock.release();

        //  
        //  Mark the set as completed for the successor adding operation.
        //
        CompleteTaskSet( hDependsOn );
    }

    //  Set output taskset handle
    *pOutHandle = hSet;

    bResult = TRUE;

Cleanup:

    return bResult;
}