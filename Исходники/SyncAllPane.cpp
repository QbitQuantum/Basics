void CSyncAllPane::refresh() {

    if (UICustomization::verboseUIDebugging) {
        StringBuffer msg;
        msg.sprintf("%s: state %d ", __FUNCTION__, state);
        printLog(msg.c_str(), LOG_DEBUG);
    }

    if (state == SYNCALL_PANE_STATE_NORMAL) {
        labelText.LoadString(IDS_SYNCALL);
        if (mouseOver) {
            statusIcon.SetIcon(iconSyncAll);
        } else {
            statusIcon.SetIcon(NULL);
        }
    }
    else {  // SYNCALL_PANE_STATE_SYNC
        labelText.LoadString(IDS_CANCEL_SYNC);
        statusIcon.SetIcon(iconCancel);
    }
    label.SetWindowText(labelText);

}