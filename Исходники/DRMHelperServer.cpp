// -----------------------------------------------------------------------------
// CDRMHelperServer::CheckExpirationL().
// This function check the time for rights to expire
// -----------------------------------------------------------------------------
//
void CDRMHelperServer::CheckExpirationL(
        const TDesC8& aUri ,
        const TUint8& aPermType ,
        const TUint8& aRegType ,
        TTime& aEndTime )
    {
#ifdef _DRM_TESTING
    WriteL(_L8("CheckExpiration"));
#endif


    RPointerArray<CDRMPermission> rights;
    RArray<TTimeBased> timeList;
    TBool stop = EFalse;
    TInt i = 0;
    TInt err = 0;
    TTimeIntervalYears years(KTimeIntervalYears);
    TTime time = Time::MinTTime();
    TTimeBased item;
    TTimeIntervalSeconds interval = 0;
    RPointerArray<HBufC8> imsi;

    aEndTime = Time::MinTTime();


    TRAP( err , iDrm.GetDBEntriesL(aUri, rights) );
    CleanupClosePushL(rights);
    if ( err == KErrCANoRights || err == KErrCANoPermission )
        {
        aEndTime = Time::MinTTime();
        err = KErrNone;
        stop = ETrue;
        }
    User::LeaveIfError(err);

    TRAP( err, iDrm.GetSupportedIndividualsL( imsi ) );

    if ( err )
        {
        imsi.ResetAndDestroy();
        }

    time.HomeTime();
    // Goes through all the rights associated to this specific URI
    CleanupClosePushL(timeList);

    for (i = 0; i < rights.Count() && !stop; i++)
        {
        CheckPermission( rights[i], aPermType, item, interval ,imsi );
        if (interval.Int()>0 ||
            (item.StartTime()==Time::MinTTime()&&item.EndTime()==Time::MaxTTime()))
            {
            stop = ETrue;
            aEndTime = Time::MaxTTime();
            }
        else
            {
            if (aRegType == CDRMHelperServer::EActive && item.StartTime()>time)
                {
                // dont count future time for active usage
                }
            else
                {
                err = timeList.Append( item );
                if ( err )
                    {
                    rights.ResetAndDestroy();
                    imsi.ResetAndDestroy();
                    }
                User::LeaveIfError(err);
                }
            }
        }
    rights.ResetAndDestroy();
    imsi.ResetAndDestroy();

    // if there were no inactivated interval- or full-rights then calculate the expiration date
    // based on what we stored to timeList
    if( !stop )
        {
        time.HomeTime(); // preset time to current time. This is what we compare against.
        TTime temp;
        TTime pastTime;
        temp = time;
        pastTime = Time::MinTTime();

        TBool action = ETrue;

        // Loop while there are still items in the list and we have done something
        while( action && timeList.Count() > 0 )
            {
            action = EFalse;
            for ( i = 0 ; i < timeList.Count() ; i++ ) // go through the whole timeList
                {
#ifdef _DRM_TESTING
                _LIT8(KCount , "time list count: %d");
                TBuf8<40> buf;
                buf.Format( KCount , timeList.Count());
                WriteL( buf );
#endif
                if ( timeList[i].StartTime() <= time && timeList[i].EndTime() > time )
                    {
                    // Case1: valid rights
                    time = timeList[i].EndTime();
                    timeList.Remove(i);
                    action = ETrue;
#ifdef _DRM_TESTING
                    WriteL(_L8("case 1:"));
                    WriteTimeL( time );
#endif
                    }
                else if ( timeList[i].StartTime() <= time && timeList[i].EndTime() <= time )
                    {
                    // Case2: expired rights
                    if (timeList[i].EndTime()>pastTime) // just in case there is no valid rights
                        {
                        pastTime = timeList[i].EndTime(); // save the latest end time from the expired rights
                        }
                    timeList.Remove(i);
                    action = ETrue;
#ifdef _DRM_TESTING
                    WriteL(_L8("case 2:"));
#endif
                    }
                else if ( timeList[i].StartTime() > time && timeList[i].EndTime() <= time )
                    {
                    // Case3: Illegal case. Start time after end-time.
                    timeList.Remove(i);
                    action = ETrue;
#ifdef _DRM_TESTING
                    WriteL(_L8("case 3:"));
#endif
                    }
                else
                    {
                    // Case4: Only thing left is the not yet valid -rights
#ifdef _DRM_TESTING
                    WriteL(_L8("case 4:"));
#endif
                    }
                }
            }

        if (temp<time)
            {
            aEndTime = time;   // time has been changed, so we use it, otherwise it means there is no valid rights
            }
        else
            {
            aEndTime = pastTime;
            }


#ifdef _DRM_TESTING
        WriteL(_L8("expiration date:"));
        WriteTimeL( aEndTime );
#endif
        }

#ifdef _DRM_TESTING
    WriteL(_L8("Endtime calculation is done:"));
    WriteTimeL( aEndTime );
#endif

    timeList.Reset();
    CleanupStack::PopAndDestroy(&timeList); // timeList
    CleanupStack::PopAndDestroy(&rights); // rights
    }