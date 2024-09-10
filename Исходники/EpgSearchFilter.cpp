int EpgSearchFilter::FilterTimers(CFileItemList &results)
{
    int iRemoved(0);
    if (!g_PVRManager.IsStarted())
        return iRemoved;

    std::vector<CFileItemPtr> timers = g_PVRTimers->GetActiveTimers();
    // TODO inefficient!
    for (unsigned int iTimerPtr = 0; iTimerPtr < timers.size(); iTimerPtr++)
    {
        CFileItemPtr fileItem = timers.at(iTimerPtr);
        if (!fileItem || !fileItem->HasPVRTimerInfoTag())
            continue;

        CPVRTimerInfoTagPtr timer = fileItem->GetPVRTimerInfoTag();
        if (!timer)
            continue;

        for (int iResultPtr = 0; iResultPtr < results.Size(); iResultPtr++)
        {
            const CEpgInfoTagPtr epgentry(results.Get(iResultPtr)->GetEPGInfoTag());
            if (!epgentry ||
                    *epgentry->ChannelTag() != *timer->ChannelTag() ||
                    epgentry->StartAsUTC()   <  timer->StartAsUTC() ||
                    epgentry->EndAsUTC()     >  timer->EndAsUTC())
                continue;

            results.Remove(iResultPtr);
            iResultPtr--;
            ++iRemoved;
        }
    }

    return iRemoved;
}