static void ssbDiscardTopSlot(PVBOXDISPDEV pDev)
{
    SSB *pSSB = &pDev->aSSB[--pDev->cSSB];

    if (pSSB->pBuffer)
    {
        EngFreeMem (pSSB->pBuffer);
        pSSB->pBuffer = NULL;
    }

    pSSB->ident = 0;
}