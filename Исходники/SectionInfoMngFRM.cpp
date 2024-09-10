void __fastcall TSectionInfoManageFRM::cxButton2Click(TObject *Sender)
{
	if((!cxTextEdit6->Text.IsEmpty())&&(!cxTextEdit14->Text.IsEmpty())&&(-1 != cxComboBox1->ItemIndex))
	{
        USERADOQ->Close();
        String checksqlstr = "select * from SYSUSER where USERNAME='******'";
        USERADOQ->SQL->Clear();
        USERADOQ->SQL->Add(checksqlstr);
        USERADOQ->Open();
        if(!USERADOQ->IsEmpty())
        {
            ShowMessage("该用户名已经存在，请更换!");
            USERADOQ->Close();
            return;
        }
        USERADOQ->Close();
		if(cxTextEdit14->Text.IsEmpty()||(8!=cxTextEdit14->Text.Length()))
        {
            ShowMessage("密码不能为空，且密码长度必须为8位!");
            return;
        }

        char OLPW[8];
        char ENPW[9];
        ZeroMemory(OLPW, 8);
        ZeroMemory(ENPW, 9);
        String tmppwstr = cxTextEdit14->Text;
        for(int i=0; i<4; i++)
        {
            int tmpint = StrToInt("0x"+tmppwstr.SubString(i*2+1, 2));
        	IntToUChar(tmpint, &OLPW[i]);
        }
        EncrptyCardMMProc(0, OLPW, ENPW);

		char Inbasechar[17];
        ZeroMemory(Inbasechar, 17);
        for(int t = 0; t<8; t++)
        {
            char tmp;
            tmp = ENPW[t]>>4;
            tmp = tmp&0x0f;
            if(tmp >= 10)
                Inbasechar[t*2] = tmp+55;
            if(tmp <10)
                Inbasechar[t*2] = tmp+48;
            tmp = ENPW[t]&0x0f;
            if(tmp >= 10)
                Inbasechar[t*2+1] = tmp+55;
            if(tmp <10)
                Inbasechar[t*2+1] = tmp+48;
        }

        String stortstr = Inbasechar;

		USERADOT->InsertRecord(ARRAYOFCONST((cxTextEdit6->Text, Inbasechar, cxComboBox1->ItemIndex+1, cxComboBox1->Text)));
	}