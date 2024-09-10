wxInt32 CViewTransfersGrid::FormatSpeed(wxInt32 item, wxString& strBuffer) const {
    float          fTransferSpeed = 0;
    FILE_TRANSFER* transfer = wxGetApp().GetDocument()->file_transfer(item);

    if (transfer) {
        if (transfer->xfer_active)
            fTransferSpeed = transfer->xfer_speed / 1024;
        else
            fTransferSpeed = 0.0;
    }

    strBuffer.Printf(wxT(" %.2f KBps"), fTransferSpeed);

    return 0;
}