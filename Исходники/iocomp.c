VOID
NTAPI
IopFreeMiniPacket(PIOP_MINI_COMPLETION_PACKET Packet)
{
    PKPRCB Prcb = KeGetCurrentPrcb();
    PNPAGED_LOOKASIDE_LIST List;

    /* Use the P List */
    List = (PNPAGED_LOOKASIDE_LIST)Prcb->
            PPLookasideList[LookasideCompletionList].P;
    List->L.TotalFrees++;

    /* Check if the Free was within the Depth or not */
    if (ExQueryDepthSList(&List->L.ListHead) >= List->L.Depth)
    {
        /* Let the balancer know */
        List->L.FreeMisses++;

        /* Use the L List */
        List = (PNPAGED_LOOKASIDE_LIST)Prcb->
                PPLookasideList[LookasideCompletionList].L;
        List->L.TotalFrees++;

        /* Check if the Free was within the Depth or not */
        if (ExQueryDepthSList(&List->L.ListHead) >= List->L.Depth)
        {
            /* All lists failed, use the pool */
            List->L.FreeMisses++;
            ExFreePool(Packet);
            return;
        }
    }

    /* The free was within dhe Depth */
    InterlockedPushEntrySList(&List->L.ListHead, (PSLIST_ENTRY)Packet);
}