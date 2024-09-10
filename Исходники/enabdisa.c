NTSTATUS WmipEnableDisableTrace(
    IN ULONG Ioctl,
    IN PWMITRACEENABLEDISABLEINFO TraceEnableInfo
    )
/*++

Routine Description:

    This routine will enable or disable a tracelog guid

Arguments:

   Ioctl is the IOCTL used to call this routine from UM
         
   TraceEnableInfo has all the info needed to enable or disable

Return Value:


--*/
{
    NTSTATUS Status;
    LPGUID Guid;
    PBGUIDENTRY GuidEntry;
    BOOLEAN RequestSent;
    BOOLEAN IsEnable;
    ULONG64 LoggerContext;
    
    PAGED_CODE();
    
    Guid = &TraceEnableInfo->Guid;
    
    Status = WmipCheckGuidAccess(Guid,
                                 TRACELOG_GUID_ENABLE,
                                 EtwpDefaultTraceSecurityDescriptor);

                
    if (NT_SUCCESS(Status))
    {

        //
        // The following code is serialized for Trace Guids. Only one 
        // control application can be enabling or disabling Trace Guids at a time. 
        // Must be taken before SMCritSection is taken. Otherwise deadlocks will result.
        //
        
        WmipEnterTLCritSection();

        IsEnable = TraceEnableInfo->Enable;

        //
        // Check for Heap and Crit Sec Tracing Guid.
        //

        if( IsEqualGUID(&HeapGuid,Guid)) {

            if(IsEnable){

	            SharedUserData->TraceLogging |= ENABLEHEAPTRACE;

                //
                // increment counter. The counter  
                // is composed of first two bytes
                //

                SharedUserData->TraceLogging += 0x00010000; 


            } else {

                SharedUserData->TraceLogging &= DISABLEHEAPTRACE;
            }

			WmipLeaveTLCritSection();
			return STATUS_SUCCESS;
        } else if(IsEqualGUID(&CritSecGuid,Guid)){  

            if(IsEnable) {

	            SharedUserData->TraceLogging |= ENABLECRITSECTRACE;

                //
                // increment counter. The counter  
                // is composed of first two bytes
                //

                SharedUserData->TraceLogging += 0x00010000; 

            } else {

                SharedUserData->TraceLogging &= DISABLECRITSECTRACE;
            }

			WmipLeaveTLCritSection();
			return STATUS_SUCCESS;

        } else if(IsEqualGUID(&NtdllTraceGuid,Guid)){  

            if(!IsEnable){

                SharedUserData->TraceLogging &= DISABLENTDLLTRACE;

            }
        }

        LoggerContext = TraceEnableInfo->LoggerContext;
        
        WmipEnterSMCritSection();

        GuidEntry = WmipFindGEByGuid(Guid, FALSE);
        
        if (GuidEntry == NULL )
        {
            //
            // The guid is not yet registered
            //
            if (IsEnable )
            {
                //
                // If the NtdllTraceGuid is not in list then we do not want to enable it
                // the NtdllTraceGuid will make an entry only to call starttrace
                //

                if(IsEqualGUID(&NtdllTraceGuid,Guid)){

                    Status = STATUS_ILLEGAL_FUNCTION;

                } else {

                    //
                    // If we are enabling a guid that is not yet registered
                    // we need to create the guid object for it
                    //

                    GuidEntry = WmipAllocGuidEntry();
                    if (GuidEntry != NULL)
                    {
                        //
                        // Initialize the guid entry and keep the ref count
                        // from creation. When tracelog enables we take a ref
                        // count and when it disables we release it
                        //
                        GuidEntry->Guid = *Guid;
                        GuidEntry->Flags |= GE_NOTIFICATION_TRACE_FLAG;
                        GuidEntry->LoggerContext = LoggerContext;
                        GuidEntry->EventRefCount = 1; 
                        InsertHeadList(WmipGEHeadPtr, &GuidEntry->MainGEList);
                        Status = STATUS_SUCCESS;                    
                    } else {
                        Status = STATUS_INSUFFICIENT_RESOURCES;
                    }
                }
            } 

        } else {
            //
            // The control guid is already registered so lets go and
            // enabled or disable it
            //
            if (WmipIsControlGuid(GuidEntry))
            {
                if (IsEnable)
                {
                    GuidEntry->LoggerContext = LoggerContext;
                    if (GuidEntry->Flags & GE_NOTIFICATION_TRACE_FLAG)
                    {
                        //
                        // We are trying to enable a trace guid that is already
                        // registered
                        //
                        GuidEntry->Flags |= GE_NOTIFICATION_TRACE_UPDATE;
                        Status = WmipEnableCollectOrEvent(GuidEntry,
                                             Ioctl,
                                             &RequestSent,
                                             LoggerContext);

                    } else {
                        GuidEntry->Flags |= GE_NOTIFICATION_TRACE_FLAG;
                        WmipReferenceGE(GuidEntry);

                        Status = WmipEnableCollectOrEvent(GuidEntry,
                                             Ioctl,
                                             &RequestSent,
                                             LoggerContext);
                        
                        if (!NT_SUCCESS(Status) &&
                            (GuidEntry->Flags & GE_NOTIFICATION_TRACE_FLAG)) {

                            //
                            // We failed to enable the trace event, and our
                            // flag is still set. Remove the flag and deref
                            // the guid entry.
                            //
                            // When we call WmipEnableCollectOrEvent above,
                            // we actually drop the SM lock for a little bit.
                            // That means it's possible for a disable call to
                            // come through at the same time, which would
                            // remove the flag and deref the guid entry itself.
                            //

                            GuidEntry->Flags &= ~GE_NOTIFICATION_TRACE_FLAG;
                            WmipUnreferenceGE(GuidEntry);
                        }
                    }

                } else {

                    if (GuidEntry->Flags & GE_NOTIFICATION_TRACE_FLAG)
                    {
                        //
                        // Send the disable collection call and then remove
                        // the refcount that was taken when we enabled
                        //
                        GuidEntry->Flags &= ~GE_NOTIFICATION_TRACE_FLAG;
                        Status = WmipDisableCollectOrEvent(GuidEntry,
                                                 Ioctl,
                                                 LoggerContext);
                        //
                        // Whether the Disable request succeeds or not
                        // we will remove the extra refcount since we 
                        // reset the NOTIFICATION_FLAG
                        //
                        GuidEntry->LoggerContext = 0;
                        WmipUnreferenceGE(GuidEntry);
                    } else {
                        Status = STATUS_WMI_ALREADY_DISABLED;
                    }
                }
            } else if ( IsListEmpty(&GuidEntry->ISHead)  && (! IsEnable) ) {
                //
                // If this GUID is not a control GUID, check to see if 
                // there are no instance sets for this GUID. If so, 
                // it is getting disabled before any instances 
                // registered it. Disable the GUID and clean up the GE. 
                //
                if (GuidEntry->Flags & GE_NOTIFICATION_TRACE_FLAG)
                {
                    GuidEntry->Flags &= ~GE_NOTIFICATION_TRACE_FLAG;
                    GuidEntry->LoggerContext = 0;
                    WmipUnreferenceGE(GuidEntry);
                }
                Status = STATUS_SUCCESS;

            } else if(!IsEqualGUID(&NtdllTraceGuid,Guid)){

                Status = STATUS_ILLEGAL_FUNCTION;

            }

            WmipUnreferenceGE(GuidEntry);
        }

        WmipLeaveSMCritSection();

        WmipLeaveTLCritSection();
    }
    return(Status);
}