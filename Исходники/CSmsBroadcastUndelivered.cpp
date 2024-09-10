void CSmsBroadcastUndelivered::ScanRawTable()
{
    Int64 startTime;
    AutoPtr<ISystem> system;
    CSystem::AcquireSingleton((ISystem**)&system);
    system->GetNanoTime(&startTime);

    //HashMap<SmsReferenceKey, Integer> multiPartReceivedCount = new HashMap<SmsReferenceKey, Integer>(4);
    AutoPtr<IHashMap> multiPartReceivedCount;
    CHashMap::New(4, (IHashMap**)&multiPartReceivedCount);

    //HashSet<SmsReferenceKey> oldMultiPartMessages = new HashSet<SmsReferenceKey>(4);
    AutoPtr<IHashSet> oldMultiPartMessages;
    CHashSet::New(4, (IHashSet**)&oldMultiPartMessages);

    AutoPtr<ICursor> cursor = NULL;
    //try {
        mResolver->Query(sRawUri, PDU_PENDING_MESSAGE_PROJECTION, String(NULL), NULL, String(NULL), (ICursor**)&cursor);
        if (cursor == NULL) {
            //Rlog->E(TAG, "error getting pending message cursor");
            Logger::E(TAG, "error getting pending message cursor");
            return;
        }

        Boolean isCurrentFormat3gpp2 = InboundSmsHandler::IsCurrentFormat3gpp2();
        Boolean next = FALSE;
        while (cursor->MoveToNext(&next), next) {
            AutoPtr<InboundSmsTracker> tracker;
            //try {
                tracker = new InboundSmsTracker(cursor, isCurrentFormat3gpp2);
            //} Catch (IllegalArgumentException e) {
            //    Rlog->E(TAG, "error loading SmsTracker: " + e);
            //    continue;
            //}

            if (tracker->GetMessageCount() == 1) {
                // deliver single-part message
                BroadcastSms(tracker);
            } else {
                AutoPtr<SmsReferenceKey> reference = new SmsReferenceKey(tracker);
                AutoPtr<IInterface> obj;
                multiPartReceivedCount->Get(TO_IINTERFACE(reference), (IInterface**)&obj);
                IInteger32* receivedCount = IInteger32::Probe(obj);

                // get partial segment expire age from resource which in config.xml
                // Add this function for international roaming requirement.
                AutoPtr<IResources> res;
                mContext->GetResources((IResources**)&res);
                String expireAgeString;
                res->GetString(R::string::config_partial_segment_expire_age, &expireAgeString);
                Int64 expireAge = StringUtils::ParseInt64(expireAgeString);
                if (obj == NULL) {
                    // first segment seen
                    multiPartReceivedCount->Put(TO_IINTERFACE(reference), CoreUtils::Convert(1));
                    Int64 currentTimeMillis;
                    system->GetCurrentTimeMillis(&currentTimeMillis);
                    if (tracker->GetTimestamp() < (currentTimeMillis - expireAge)) {
                        // older than 30 days; delete if we don't find all the segments
                        oldMultiPartMessages->Add(TO_IINTERFACE(reference));
                    }
                } else {
                    //Int32 newCount = receivedCount + 1;
                    Int32 newCount;
                    receivedCount->GetValue(&newCount);
                    ++newCount;
                    if (newCount == tracker->GetMessageCount()) {
                        // looks like we've got all the pieces; send a single tracker
                        // to state machine which will find the other pieces to broadcast
                        if (DBG) {
                            //Rlog->D(TAG, "found complete multi-part message");
                            Logger::D(TAG, "found complete multi-part message");
                        }
                        BroadcastSms(tracker);
                        // don't delete this old message until after we broadcast it
                        oldMultiPartMessages->Remove(TO_IINTERFACE(reference));
                    } else {
                        multiPartReceivedCount->Put(TO_IINTERFACE(reference), CoreUtils::Convert(newCount));
                    }
                }
            }
        }
        // Delete old incomplete message segments
        AutoPtr<ArrayOf<IInterface*> > array;
        oldMultiPartMessages->ToArray((ArrayOf<IInterface*>**)&array);
        Int32 size = array->GetLength();
        for (Int32 i = 0; i < size; ++i) {
            AutoPtr<IInterface> obj = (*array)[i];
            AutoPtr<SmsReferenceKey> message = (SmsReferenceKey*)(IObject::Probe(obj));
            Int32 rows;
            mResolver->Delete(sRawUri, InboundSmsHandler::SELECT_BY_REFERENCE,
                    message->GetDeleteWhereArgs(), &rows);
            if (rows == 0) {
                //Rlog->E(TAG, "No rows were deleted from raw table!");
                Logger::E(TAG, "No rows were deleted from raw table!");
            } else if (DBG) {
                //Rlog->D(TAG, "Deleted " + rows + " rows from raw table for incomplete "
                //        + message.mMessageCount + " part message");
                Logger::D(TAG, "Deleted %d rows from raw table for incomplete %d part message",
                        rows, message->mMessageCount);
            }
        }
    //} Catch (SQLException e) {
    //    Rlog->E(TAG, "error reading pending SMS messages", e);
    //} finally {
        if (cursor != NULL) {
            ICloseable::Probe(cursor)->Close();
        }
        if (DBG)
        {
            //Rlog->D(TAG, "finished scanning raw table in "
            //    + ((System->NanoTime() - startTime) / 1000000) + " ms");
            Int64 endTime;
            system->GetNanoTime(&endTime);
            Logger::D(TAG, "finished scanning raw table in %lld ms", (endTime - startTime) / 1000000);
        }
    //}
}