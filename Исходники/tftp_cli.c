///////////////////////////////////////////////////////
// End of transfer : 
///////////////////////////////////////////////////////
static void StopTransfer (void)
{
    // stop transfer
    WSAAsyncSelect (sTC.s, hTftpClientWnd, 0, 0);
    KillTimer(hTftpClientWnd, WM_CLIENT_DATA);
    KillTimer(hTftpClientWnd, WM_CLIENT_ACK);
    // free resource
    closesocket (sTC.s);      sTC.s = INVALID_SOCKET;
    CloseHandle (sTC.hFile);  sTC.hFile = INVALID_HANDLE_VALUE;
    sTC.bConnected = TFTP_NOTCONNECTED;
    // reinit buttons
    EnableWindow (GetDlgItem (GetParent(hTftpClientWnd), IDC_CLIENT_SEND_BUTTON), TRUE);
    EnableWindow (GetDlgItem (GetParent(hTftpClientWnd), IDC_CLIENT_GET_BUTTON), TRUE);
    EnableWindow (GetDlgItem (GetParent(hTftpClientWnd), IDC_CLIENT_BREAK_BUTTON), FALSE);
    SetDlgItemText (GetParent(hTftpClientWnd), IDC_CLIENT_BLOCK, "");
    SendDlgItemMessage (GetParent(hTftpClientWnd), IDC_CLIENT_PROGRESS, PBM_SETPOS, 0, 0);

} // StopTransfer