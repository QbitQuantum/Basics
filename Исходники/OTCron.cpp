// Make sure to call this regularly so the CronItems get a chance to process and expire.
void OTCron::ProcessCronItems()
{
	if (!m_bIsActivated)
		return;	// No Cron processing until Cron is activated.
	
	if (GetTransactionCount() < 10) // todo stop hardcoding.
	{
		OTLog::Error("Cron is out of transaction numbers!");
		return;
	}
	
	bool bNeedToSave = false;
	
	// loop through the cron items and tell each one to ProcessCron().
	// If the item returns true, that means leave it on the list. Otherwise,
	// if it returns false, that means "it's done: remove it."
	OTCronItem * pItem = NULL;
	
	for (mapOfCronItems::iterator ii = m_mapCronItems.begin(); ii != m_mapCronItems.end(); )
	{
		pItem = (*ii).second;
		
		OT_ASSERT(NULL != pItem);
		
        bool bVerifySig     = pItem->VerifySignature(*m_pServerNym);
        bool bProcessCron   = false;
        
        if (bVerifySig)
        {
            bProcessCron = pItem->ProcessCron();
            
            // false means "remove it".
            // ProcessCron returns true if should stay on the list.
            //
            if (false == bProcessCron)
                pItem->HookRemovalFromCron(NULL); // We give the hook a chance to do its thing.
        }
        else
            OTLog::Error("OTCron::ProcessCronItems: Signature failed to verify on cron item!\n");
            
        // -----------------------------------------------------

		// Remove it from the list.
        //
		if (false == bProcessCron)
		{
            OTLog::vOutput(0, "OTCron::ProcessCronItems: Removing expired or unverified cron item.\n");
			m_mapCronItems.erase(ii++);
			delete pItem;
			pItem = NULL;
			
			bNeedToSave = true; // We'll save to file at the bottom if anything was removed.
		} 
		else	// the special i++ and ++i arrangement here allows me to erase an item
		{		// from the list WHILE iterating through it  :-)   (Supposedly.)
			++ii;
		}
	} // for
	
	// Items were removed from Cron -- Save to storage!
	if (bNeedToSave)
		SaveCron();
}