GUID *
AFSValidateProcessEntry( IN HANDLE  ProcessId,
                         IN BOOLEAN bProcessTreeLocked)
{

    GUID *pAuthGroup = NULL;
    NTSTATUS ntStatus = STATUS_SUCCESS;
    AFSProcessCB *pProcessCB = NULL, *pParentProcessCB = NULL;
    AFSDeviceExt *pDeviceExt = (AFSDeviceExt *)AFSDeviceObject->DeviceExtension;
    ULONGLONG ullProcessID = (ULONGLONG)ProcessId;
    UNICODE_STRING uniSIDString;
    ULONG ulSIDHash = 0;
    AFSSIDEntryCB *pSIDEntryCB = NULL;
    ULONG ulSessionId = 0;
    ULONGLONG ullTableHash = 0;
    AFSThreadCB *pParentThreadCB = NULL;
    UNICODE_STRING uniGUID;
    BOOLEAN bImpersonation = FALSE;

    __Enter
    {

        uniSIDString.Length = 0;
        uniSIDString.MaximumLength = 0;
        uniSIDString.Buffer = NULL;

        if ( !bProcessTreeLocked)
        {

            AFSDbgTrace(( AFS_SUBSYSTEM_LOCK_PROCESSING,
                          AFS_TRACE_LEVEL_VERBOSE,
                          "AFSValidateProcessEntry Acquiring Control ProcessTree.TreeLock lock %p SHARED %08lX\n",
                          pDeviceExt->Specific.Control.ProcessTree.TreeLock,
                          PsGetCurrentThread()));

            AFSAcquireShared( pDeviceExt->Specific.Control.ProcessTree.TreeLock,
                              TRUE);
        }

        AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                      AFS_TRACE_LEVEL_VERBOSE,
                      "%s Entry for ProcessID %I64X\n",
                      __FUNCTION__,
                      ullProcessID));

        ntStatus = AFSLocateHashEntry( pDeviceExt->Specific.Control.ProcessTree.TreeHead,
                                       ullProcessID,
                                       (AFSBTreeEntry **)&pProcessCB);

        if( !NT_SUCCESS( ntStatus) ||
            pProcessCB == NULL)
        {

            if ( !bProcessTreeLocked)
            {

                AFSReleaseResource( pDeviceExt->Specific.Control.ProcessTree.TreeLock);

                AFSAcquireExcl( pDeviceExt->Specific.Control.ProcessTree.TreeLock,
                                TRUE);
            }

            ntStatus = AFSLocateHashEntry( pDeviceExt->Specific.Control.ProcessTree.TreeHead,
                                           ullProcessID,
                                           (AFSBTreeEntry **)&pProcessCB);

            if( !NT_SUCCESS( ntStatus) ||
                pProcessCB == NULL)
            {

                AFSProcessCreate( 0,
                                  ProcessId,
                                  0,
                                  0);
            }

            if( !NT_SUCCESS( ntStatus) ||
                pProcessCB == NULL)
            {

                AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                              AFS_TRACE_LEVEL_ERROR,
                              "%s Failed to locate process entry for ProcessID %I64X\n",
                              __FUNCTION__,
                              ullProcessID));

                try_return( ntStatus = STATUS_UNSUCCESSFUL);
            }

            if ( !bProcessTreeLocked)
            {

                AFSConvertToShared( pDeviceExt->Specific.Control.ProcessTree.TreeLock);
            }
        }

        //
        // Locate and lock the ParentProcessCB if we have one
        //

        if( pProcessCB->ParentProcessId != 0)
        {

            AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                          AFS_TRACE_LEVEL_VERBOSE,
                          "%s Locating process entry for Parent ProcessID %I64X\n",
                          __FUNCTION__,
                          pProcessCB->ParentProcessId));

            ntStatus = AFSLocateHashEntry( pDeviceExt->Specific.Control.ProcessTree.TreeHead,
                                           (ULONGLONG)pProcessCB->ParentProcessId,
                                           (AFSBTreeEntry **)&pParentProcessCB);

            if( NT_SUCCESS( ntStatus) &&
                pParentProcessCB != NULL)
            {
                AFSAcquireExcl( &pParentProcessCB->Lock,
                                TRUE);

                AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                              AFS_TRACE_LEVEL_VERBOSE,
                              "%s Located process entry for Parent ProcessID %I64X\n",
                              __FUNCTION__,
                              pProcessCB->ParentProcessId));
            }
        }
        else
        {

            AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                          AFS_TRACE_LEVEL_VERBOSE,
                          "%s No parent ID for ProcessID %I64X\n",
                          __FUNCTION__,
                          ullProcessID));
        }

        AFSAcquireExcl( &pProcessCB->Lock,
                        TRUE);

#if defined(_WIN64)

        //
        // Mark the process as 64-bit if it is.
        //

        if( !IoIs32bitProcess( NULL))
        {

            SetFlag( pProcessCB->Flags, AFS_PROCESS_FLAG_IS_64BIT);
        }
        else
        {

            ClearFlag( pProcessCB->Flags, AFS_PROCESS_FLAG_IS_64BIT);
        }
#endif

        //
        // Locate the SID for the caller
        //

        ntStatus = AFSGetCallerSID( &uniSIDString, &bImpersonation);

        if( !NT_SUCCESS( ntStatus))
        {

            AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                          AFS_TRACE_LEVEL_ERROR,
                          "%s Failed to locate callers SID for ProcessID %I64X\n",
                          __FUNCTION__,
                          ullProcessID));

            try_return( ntStatus);
        }

        ulSessionId = AFSGetSessionId( (HANDLE)ullProcessID, &bImpersonation);

        if( ulSessionId == (ULONG)-1)
        {

            AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                          AFS_TRACE_LEVEL_ERROR,
                          "%s Failed to retrieve session ID for ProcessID %I64X\n",
                          __FUNCTION__,
                          ullProcessID));

            try_return( ntStatus = STATUS_INSUFFICIENT_RESOURCES);
        }

        AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                      AFS_TRACE_LEVEL_VERBOSE,
                      "%s Retrieved callers SID %wZ for ProcessID %I64X Session %08lX\n",
                      __FUNCTION__,
                      &uniSIDString,
                      ullProcessID,
                      ulSessionId));

        //
        // If there is an Auth Group for the current process,
        // our job is finished.
        //

        if ( bImpersonation == FALSE)
        {
            pAuthGroup = pProcessCB->ActiveAuthGroup;

            if( pAuthGroup != NULL &&
                !AFSIsNoPAGAuthGroup( pAuthGroup))
            {

                uniGUID.Buffer = NULL;

                RtlStringFromGUID( *pAuthGroup,
                                   &uniGUID);

                AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                              AFS_TRACE_LEVEL_VERBOSE,
                              "%s Located valid AuthGroup GUID %wZ for SID %wZ ProcessID %I64X Session %08lX\n",
                              __FUNCTION__,
                              &uniGUID,
                              &uniSIDString,
                              ullProcessID,
                              ulSessionId));

                if( uniGUID.Buffer != NULL)
                {
                    RtlFreeUnicodeString( &uniGUID);
                }

                try_return( ntStatus = STATUS_SUCCESS);
            }

            //
            // The current process does not yet have an Auth Group.  Try to inherit
            // one from the parent process thread that created this process.
            //

            if( pParentProcessCB != NULL)
            {

                for ( pParentThreadCB = pParentProcessCB->ThreadList;
                      pParentThreadCB != NULL;
                      pParentThreadCB = pParentThreadCB->Next)
                {

                    if( pParentThreadCB->ThreadId == pProcessCB->CreatingThreadId)
                    {
                        break;
                    }
                }

                //
                // If the creating thread was found and it has a thread specific
                // Auth Group, use that even if it is the No PAG
                //

                if( pParentThreadCB != NULL &&
                    pParentThreadCB->ActiveAuthGroup != NULL &&
                    !AFSIsNoPAGAuthGroup( pParentThreadCB->ActiveAuthGroup))
                {
                    pProcessCB->ActiveAuthGroup = pParentThreadCB->ActiveAuthGroup;

                    uniGUID.Buffer = NULL;

                    RtlStringFromGUID( *(pProcessCB->ActiveAuthGroup),
                                       &uniGUID);

                    AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                                  AFS_TRACE_LEVEL_VERBOSE,
                                  "%s PID %I64X Session %08lX inherited Active AuthGroup %wZ from thread %I64X\n",
                                  __FUNCTION__,
                                  ullProcessID,
                                  ulSessionId,
                                  &uniGUID,
                                  pParentThreadCB->ThreadId));

                    if( uniGUID.Buffer != NULL)
                    {
                        RtlFreeUnicodeString( &uniGUID);
                    }
                }

                //
                // If the parent thread was not found or does not have an auth group
                //

                else if( pParentProcessCB->ActiveAuthGroup != NULL &&
                         !AFSIsNoPAGAuthGroup( pParentProcessCB->ActiveAuthGroup))
                {
                    pProcessCB->ActiveAuthGroup = pParentProcessCB->ActiveAuthGroup;

                    uniGUID.Buffer = NULL;

                    RtlStringFromGUID( *(pProcessCB->ActiveAuthGroup),
                                       &uniGUID);

                    AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                                  AFS_TRACE_LEVEL_VERBOSE,
                                  "%s PID %I64X Session %08lX inherited Active AuthGroup %wZ from parent PID %I64X\n",
                                  __FUNCTION__,
                                  ullProcessID,
                                  ulSessionId,
                                  &uniGUID,
                                  pParentProcessCB->TreeEntry.HashIndex));

                    if( uniGUID.Buffer != NULL)
                    {
                        RtlFreeUnicodeString( &uniGUID);
                    }
                }

                //
                // If an Auth Group was inherited, set it to be the active group
                //

                if( pProcessCB->ActiveAuthGroup != NULL &&
                    !AFSIsNoPAGAuthGroup( pParentProcessCB->ActiveAuthGroup))
                {
                    pAuthGroup = pProcessCB->ActiveAuthGroup;

                    uniGUID.Buffer = NULL;

                    RtlStringFromGUID( *(pProcessCB->ActiveAuthGroup),
                                       &uniGUID);

                    AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                                  AFS_TRACE_LEVEL_VERBOSE,
                                  "%s Returning(1) Active AuthGroup %wZ for SID %wZ PID %I64X Session %08lX\n",
                                  __FUNCTION__,
                                  &uniGUID,
                                  &uniSIDString,
                                  ullProcessID,
                                  ulSessionId));

                    if( uniGUID.Buffer != NULL)
                    {
                        RtlFreeUnicodeString( &uniGUID);
                    }

                    try_return( ntStatus);
                }
            }
        }

        //
        // If no Auth Group was inherited, assign one based upon the Session and SID
        //

        ntStatus = RtlHashUnicodeString( &uniSIDString,
                                         TRUE,
                                         HASH_STRING_ALGORITHM_DEFAULT,
                                         &ulSIDHash);

        if( !NT_SUCCESS( ntStatus))
        {

            AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                          AFS_TRACE_LEVEL_ERROR,
                          "%s Failed to hash SID %wZ for PID %I64X Session %08lX Status %08lX\n",
                          __FUNCTION__,
                          &uniSIDString,
                          ullProcessID,
                          ulSessionId,
                          ntStatus));

            try_return( ntStatus);
        }

        ullTableHash = ( ((ULONGLONG)ulSessionId << 32) | ulSIDHash);

        AFSAcquireShared( pDeviceExt->Specific.Control.AuthGroupTree.TreeLock,
                          TRUE);

        ntStatus = AFSLocateHashEntry( pDeviceExt->Specific.Control.AuthGroupTree.TreeHead,
                                       (ULONGLONG)ullTableHash,
                                       (AFSBTreeEntry **)&pSIDEntryCB);

        if( !NT_SUCCESS( ntStatus) ||
            pSIDEntryCB == NULL)
        {

            AFSReleaseResource( pDeviceExt->Specific.Control.AuthGroupTree.TreeLock);

            AFSAcquireExcl( pDeviceExt->Specific.Control.AuthGroupTree.TreeLock,
                            TRUE);

            ntStatus = AFSLocateHashEntry( pDeviceExt->Specific.Control.AuthGroupTree.TreeHead,
                                           (ULONGLONG)ullTableHash,
                                           (AFSBTreeEntry **)&pSIDEntryCB);

            if( !NT_SUCCESS( ntStatus) ||
                pSIDEntryCB == NULL)
            {

                pSIDEntryCB = (AFSSIDEntryCB *)AFSExAllocatePoolWithTag( NonPagedPool,
                                                                         sizeof( AFSSIDEntryCB),
                                                                         AFS_AG_ENTRY_CB_TAG);

                if( pSIDEntryCB == NULL)
                {

                    AFSReleaseResource( pDeviceExt->Specific.Control.AuthGroupTree.TreeLock);

                    try_return( ntStatus = STATUS_INSUFFICIENT_RESOURCES);
                }

                RtlZeroMemory( pSIDEntryCB,
                               sizeof( AFSSIDEntryCB));

                pSIDEntryCB->TreeEntry.HashIndex = (ULONGLONG)ullTableHash;

                while( ExUuidCreate( &pSIDEntryCB->AuthGroup) == STATUS_RETRY);

                uniGUID.Buffer = NULL;

                RtlStringFromGUID( pSIDEntryCB->AuthGroup,
                                   &uniGUID);

                AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                              AFS_TRACE_LEVEL_VERBOSE,
                              "%s  SID %wZ PID %I64X Session %08lX generated NEW AG %wZ\n",
                              __FUNCTION__,
                              &uniSIDString,
                              ullProcessID,
                              ulSessionId,
                              &uniGUID));

                if( uniGUID.Buffer != NULL)
                {
                    RtlFreeUnicodeString( &uniGUID);
                }

                if( pDeviceExt->Specific.Control.AuthGroupTree.TreeHead == NULL)
                {
                    pDeviceExt->Specific.Control.AuthGroupTree.TreeHead = (AFSBTreeEntry *)pSIDEntryCB;
                }
                else
                {
                    AFSInsertHashEntry( pDeviceExt->Specific.Control.AuthGroupTree.TreeHead,
                                        &pSIDEntryCB->TreeEntry);
                }
            }

            AFSConvertToShared( pDeviceExt->Specific.Control.AuthGroupTree.TreeLock);
        }


        AFSReleaseResource( pDeviceExt->Specific.Control.AuthGroupTree.TreeLock);

        //
        // Store the auth group into the process cb
        //

        pProcessCB->ActiveAuthGroup = &pSIDEntryCB->AuthGroup;

        uniGUID.Buffer = NULL;

        RtlStringFromGUID( pSIDEntryCB->AuthGroup,
                           &uniGUID);

        AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                      AFS_TRACE_LEVEL_VERBOSE,
                      "%s SID %wZ PID %I64X Session %08lX assigned AG %wZ\n",
                      __FUNCTION__,
                      &uniSIDString,
                      ullProcessID,
                      ulSessionId,
                      &uniGUID));

        if( uniGUID.Buffer != NULL)
        {
            RtlFreeUnicodeString( &uniGUID);
        }

        //
        // Set the AFS_PROCESS_LOCAL_SYSTEM_AUTH flag if the process SID
        // is LOCAL_SYSTEM
        //

        if( AFSIsLocalSystemSID( &uniSIDString))
        {
            SetFlag( pProcessCB->Flags, AFS_PROCESS_LOCAL_SYSTEM_AUTH);

            AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                          AFS_TRACE_LEVEL_VERBOSE,
                          "%s Setting PID %I64X Session %08lX with LOCAL SYSTEM AUTHORITY\n",
                          __FUNCTION__,
                          ullProcessID,
                          ulSessionId));
        }

        //
        // Return the auth group
        //

        pAuthGroup = pProcessCB->ActiveAuthGroup;

        uniGUID.Buffer = NULL;

        RtlStringFromGUID( *(pProcessCB->ActiveAuthGroup),
                           &uniGUID);

        AFSDbgTrace(( AFS_SUBSYSTEM_AUTHGROUP_PROCESSING,
                      AFS_TRACE_LEVEL_VERBOSE,
                      "%s Returning(2) Active AuthGroup %wZ for SID %wZ PID %I64X Session %08lX\n",
                      __FUNCTION__,
                      &uniGUID,
                      &uniSIDString,
                      ullProcessID,
                      ulSessionId));

        if( uniGUID.Buffer != NULL)
        {
            RtlFreeUnicodeString( &uniGUID);
        }

try_exit:

        if( pProcessCB != NULL)
        {

            if( bImpersonation == FALSE &&
                !BooleanFlagOn( pProcessCB->Flags, AFS_PROCESS_FLAG_ACE_SET) &&
                NT_SUCCESS( ntStatus))
            {
                ntStatus = AFSProcessSetProcessDacl( pProcessCB);

                if( !NT_SUCCESS( ntStatus))
                {
                    pAuthGroup = NULL;
                }
                else
                {
                    SetFlag( pProcessCB->Flags, AFS_PROCESS_FLAG_ACE_SET);
                }
            }

            AFSReleaseResource( &pProcessCB->Lock);
        }

        if( pParentProcessCB != NULL)
        {
            AFSReleaseResource( &pParentProcessCB->Lock);
        }

        if( uniSIDString.Length > 0)
        {
            RtlFreeUnicodeString( &uniSIDString);
        }

        if ( !bProcessTreeLocked)
        {

            AFSReleaseResource( pDeviceExt->Specific.Control.ProcessTree.TreeLock);
        }
    }

    return pAuthGroup;
}