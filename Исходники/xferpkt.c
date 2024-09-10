VOID EnqueueFreeTransferPacket(PDEVICE_OBJECT Fdo, PTRANSFER_PACKET Pkt)
{
    PFUNCTIONAL_DEVICE_EXTENSION fdoExt = Fdo->DeviceExtension;
    PCLASS_PRIVATE_FDO_DATA fdoData = fdoExt->PrivateFdoData;
    KIRQL oldIrql;
    ULONG newNumPkts;
    
    ASSERT(!Pkt->SlistEntry.Next);

    InterlockedPushEntrySList(&fdoData->FreeTransferPacketsList, &Pkt->SlistEntry);
    newNumPkts = InterlockedIncrement(&fdoData->NumFreeTransferPackets);
    ASSERT(newNumPkts <= fdoData->NumTotalTransferPackets);

    /*
     *  If the total number of packets is larger than MinWorkingSetTransferPackets,
     *  that means that we've been in stress.  If all those packets are now
     *  free, then we are now out of stress and can free the extra packets.
     *  Free down to MaxWorkingSetTransferPackets immediately, and
     *  down to MinWorkingSetTransferPackets lazily (one at a time).
     */
    if (fdoData->NumFreeTransferPackets >= fdoData->NumTotalTransferPackets){

        /*
         *  1.  Immediately snap down to our UPPER threshold.
         */
        if (fdoData->NumTotalTransferPackets > MaxWorkingSetTransferPackets){
            SINGLE_LIST_ENTRY pktList;
            PSINGLE_LIST_ENTRY slistEntry;
            PTRANSFER_PACKET pktToDelete;

            DBGTRACE(ClassDebugTrace, ("Exiting stress, block freeing (%d-%d) packets.", fdoData->NumTotalTransferPackets, MaxWorkingSetTransferPackets));

            /*
             *  Check the counter again with lock held.  This eliminates a race condition
             *  while still allowing us to not grab the spinlock in the common codepath.
             *
             *  Note that the spinlock does not synchronize with threads dequeuing free
             *  packets to send (DequeueFreeTransferPacket does that with a lightweight
             *  interlocked exchange); the spinlock prevents multiple threads in this function
             *  from deciding to free too many extra packets at once.
             */
            SimpleInitSlistHdr(&pktList);
            KeAcquireSpinLock(&fdoData->SpinLock, &oldIrql);
            while ((fdoData->NumFreeTransferPackets >= fdoData->NumTotalTransferPackets) && 
                   (fdoData->NumTotalTransferPackets > MaxWorkingSetTransferPackets)){
                   
                pktToDelete = DequeueFreeTransferPacket(Fdo, FALSE);   
                if (pktToDelete){
                    SimplePushSlist(&pktList, &pktToDelete->SlistEntry);
                    InterlockedDecrement(&fdoData->NumTotalTransferPackets);    
                }
                else {
                    DBGTRACE(ClassDebugTrace, ("Extremely unlikely condition (non-fatal): %d packets dequeued at once for Fdo %p. NumTotalTransferPackets=%d (1).", MaxWorkingSetTransferPackets, Fdo, fdoData->NumTotalTransferPackets));
                    break;
                }
            }
            KeReleaseSpinLock(&fdoData->SpinLock, oldIrql);

            while (slistEntry = SimplePopSlist(&pktList)){
                pktToDelete = CONTAINING_RECORD(slistEntry, TRANSFER_PACKET, SlistEntry);
                DestroyTransferPacket(pktToDelete);
            }

        }

        /*
         *  2.  Lazily work down to our LOWER threshold (by only freeing one packet at a time).
         */
        if (fdoData->NumTotalTransferPackets > MinWorkingSetTransferPackets){
            /*
             *  Check the counter again with lock held.  This eliminates a race condition
             *  while still allowing us to not grab the spinlock in the common codepath.
             *
             *  Note that the spinlock does not synchronize with threads dequeuing free
             *  packets to send (DequeueFreeTransferPacket does that with a lightweight
             *  interlocked exchange); the spinlock prevents multiple threads in this function
             *  from deciding to free too many extra packets at once.
             */
            PTRANSFER_PACKET pktToDelete = NULL; 

            DBGTRACE(ClassDebugTrace, ("Exiting stress, lazily freeing one of %d/%d packets.", fdoData->NumTotalTransferPackets, MinWorkingSetTransferPackets));
            
            KeAcquireSpinLock(&fdoData->SpinLock, &oldIrql);
            if ((fdoData->NumFreeTransferPackets >= fdoData->NumTotalTransferPackets) &&
                (fdoData->NumTotalTransferPackets > MinWorkingSetTransferPackets)){
                
                pktToDelete = DequeueFreeTransferPacket(Fdo, FALSE);
                if (pktToDelete){
                    InterlockedDecrement(&fdoData->NumTotalTransferPackets);    
                }
                else {
                    DBGTRACE(ClassDebugTrace, ("Extremely unlikely condition (non-fatal): %d packets dequeued at once for Fdo %p. NumTotalTransferPackets=%d (2).", MinWorkingSetTransferPackets, Fdo, fdoData->NumTotalTransferPackets));
                }
            }
            KeReleaseSpinLock(&fdoData->SpinLock, oldIrql);

            if (pktToDelete){
                DestroyTransferPacket(pktToDelete);
            }
        }

    }
  
}