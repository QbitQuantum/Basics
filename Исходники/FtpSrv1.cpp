//---------------------------------------------------------------------------
// This event handler is called by the FTP component once it has built the   
// directory listing. We can use this handler to alter the listing, adding
// or removing some info. This sample add the 'virtual' directory.
void __fastcall TFtpServerForm::FtpServer1AlterDirectory(TObject *Sender,
      TFtpCtrlSocket *Client, TFtpString &Directory, bool Detailed)
{
    AnsiString Buf;

    if (UpperCase(Client->Directory) != "C:\\")
        return;
    // Add our 'virtual' directory to the list
    if (Detailed) {
        // We need to format directory lines according to the Unix standard
        Buf =
        "drwxrwxrwx   1 ftp      ftp            0 Apr 30 19:00 VIRTUAL\r\n";
        Client->DataStream->Write(&Buf[1], Buf.Length());
    }
}