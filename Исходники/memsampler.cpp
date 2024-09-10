void CMemoryView::HandleDeletedChunk(TUint32 aAddress)
{
    TChunkInfo chunkInfo(aAddress);
    TInt pos = iChunkList.Find(chunkInfo, TChunkInfo::Match);
    if (pos < 0)
    {
        PrintWarning(_L("Couldn't handle deletion of chunk 0x%08x: %d"), aAddress, pos);
    }
    else
    {
        TChunkInfo& c = iChunkList[pos];

        // Rejuvenate chunks that haven't been updated since this one last was.
        const TInt numChunks = iChunkList.Count();
        for (TInt i = 0; i < numChunks; ++i)
        {
            TChunkInfo& d = iChunkList[i];
            if (d.iUpdateCount > c.iUpdateCount)
            {
                --d.iUpdateCount;
            }
        }

        iChunkList.Remove(pos);
        if (iChunkList.Count() <= iNumConsoleLines)
        {
            iVerticalOffset = 0;
        }
    }
}