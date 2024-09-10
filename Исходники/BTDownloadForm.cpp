void __fastcall TBTDownloadFrm::FormShow(TObject *Sender)
{
	btcomo = 0x00;
    btcmd = 0x43;
    ZeroMemory(btreceivebuf, 16);
    btreceivelen = 16;
    btdir = "E:\\BT";
    btdirlen = strlen(btdir);
    btPosNo = 0;

	DownloadBTtag = true;
    ExitBTN->Left = (BTDownloadFrm->Width-ExitBTN->Width)/2;
    CSPanel->Caption = "下传按消费次数生成的补贴，请点击“下传消费次数补贴”！";
    JBPanel->Caption = "下传按职务生成的补贴，请点击“下传职务补贴”！";

    BTJPARAMADOQ->Close();
    BTJPARAMADOQ->SQL->Clear();
    BTJPARAMADOQ->SQL->Add("select * from BTJPARAM");
    BTJPARAMADOQ->Open();
    if(!BTJPARAMADOQ->IsEmpty())
    {
    	ComNoEdit->Text = BTJPARAMADOQ->FieldByName("SFJPORT")->AsString;
        MachNOEdit->Text = BTJPARAMADOQ->FieldByName("JH")->AsString;
        MaxNumEdit->Text = BTJPARAMADOQ->FieldByName("MAXBTNUM")->AsString;
        MaxXFEdit->Text = BTJPARAMADOQ->FieldByName("MAXXF")->AsString;
        PasswordEdit->Text = BTJPARAMADOQ->FieldByName("PASSWORD")->AsString;
        btPosNo = BTJPARAMADOQ->FieldByName("JH")->AsInteger;
        IntToChar(BTJPARAMADOQ->FieldByName("SFJPORT")->AsInteger, &btcomo);
    }
    else
    {
        CSBTDownBTN->Enabled = false;
        JBBTDownBTN->Enabled = false;
        ShowMessage("系统中无补贴机信息,请正确填写!");
    }
    BTJPARAMADOQ->Close();
}