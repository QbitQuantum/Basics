void NexusFlagItem::dismount(DismountMode dismountMode)
{
    if(isGhost())      // Server only
        return;
    if(getDatabase() == NULL)  // must be in database, switching levels makes database NULL
        return;

    if(dismountMode == DISMOUNT_MOUNT_WAS_KILLED)
    {
        // Should getting shot up count as a flag drop event for statistics purposes?
        if(mMount && mMount->getClientInfo())
            mMount->getClientInfo()->getStatistics()->mFlagDrop += mFlagCount + 1;

        dropFlags(mFlagCount + 1);    // Drop at least one flag plus as many as the ship carries

        // Now delete the flag itself
        removeFromDatabase(false);
        deleteObject();
    }
    else
    {
        GameType *gameType = getGame()->getGameType();
        if(!gameType)        // Crashed here once, don't know why, so I added the check
            return;

        gameType->itemDropped(mMount, this, dismountMode); // Sends messages; no flags actually dropped here; server only method
        dropFlags(mFlagCount);                             // Only dropping the flags we're carrying, not the "extra" one that comes when we die
    }
}