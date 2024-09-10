VOID
FORCEINLINE
CompleteDPC(
    IN PVOID DeviceExtension,
    IN pblk_req vbr,
    IN ULONG MessageID
    )
{
    PSCSI_REQUEST_BLOCK Srb      = (PSCSI_REQUEST_BLOCK)vbr->req;
    PADAPTER_EXTENSION  adaptExt = (PADAPTER_EXTENSION)DeviceExtension;
#ifndef USE_STORPORT
    PRHEL_SRB_EXTENSION srbExt   = (PRHEL_SRB_EXTENSION)Srb->SrbExtension;
    UNREFERENCED_PARAMETER( MessageID );
#endif
    RemoveEntryList(&vbr->list_entry);

#ifdef USE_STORPORT
    if(!adaptExt->dump_mode && adaptExt->dpc_ok) {
        InsertTailList(&adaptExt->complete_list, &vbr->list_entry);
        StorPortIssueDpc(DeviceExtension,
                         &adaptExt->completion_dpc,
                         ULongToPtr(MessageID),
                         NULL);
        return;
    }
    CompleteSRB(DeviceExtension, Srb);
#else
   if (Srb->DataTransferLength > srbExt->Xfer) {
       Srb->DataTransferLength = srbExt->Xfer;
       Srb->SrbStatus = SRB_STATUS_DATA_OVERRUN;
    }
    ScsiPortNotification(RequestComplete,
                         DeviceExtension,
                         Srb);
    if(srbExt->call_next) {
        ScsiPortNotification(NextLuRequest,
                         DeviceExtension,
                         Srb->PathId,
                         Srb->TargetId,
                         Srb->Lun);
    }
    if (adaptExt->flush_state == FlushRequested) {
        adaptExt->flush_state = FlushInflight;
        RhelDoFlush(DeviceExtension);
    }
#endif
}