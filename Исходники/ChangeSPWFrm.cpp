//---------------------------------------------------------------------------
void __fastcall TChangeSPWForm::cxButton1Click(TObject *Sender)
{
	String Oldpwstr = TEOldPassword->Text;
	String Newpwstr1 = TENewPassword1->Text;
	String Newpwstr2 = TENewPassword2->Text;

	if("" != Oldpwstr)
	{
		if(("" != Newpwstr1)&&("" != Newpwstr2))
		{
			if(Newpwstr1 == Newpwstr2)
			{
				ADOQuery1->Close();
				ADOQuery1->SQL->Clear();
				ADOQuery1->SQL->Add("Select * from XTSET");
				ADOQuery1->Open();
		  //		String tmpstr = ADOQuery1->FieldByName("CARDMM")->AsString;
				//ShowMessage(tmpstr);

				unsigned int cmplen = 12;
				if(!strnicmp(DECSuperPassword, Oldpwstr.t_str(), 12))//tmpstr == Oldpwstr)
				{
					if(Newpwstr1 == Newpwstr2)
					{
						if(12 == Newpwstr1.Length())
						{
							char CDPW[8];
							char Enchar[9];
							ZeroMemory(CDPW, 8);
							ZeroMemory(Enchar, 9);

							String tmppwstr = Newpwstr1;
							for(int i = 0; i < 6; i++)
							{
								int tmpint = StrToInt("0x"+tmppwstr.SubString(i*2+1, 2));
								IntToUChar(tmpint, &CDPW[i]);
							}
							EncrptyCardMMProc(0, CDPW, Enchar);

							memcpy(SuperPasword, CDPW, 6);
							memcpy(DECSuperPassword, tmppwstr.t_str(), 12);

							char Inbasechar[16];
							ZeroMemory(Inbasechar, 16);
							for(int t = 0; t<8; t++)
							{
								char tmp;
								tmp = Enchar[t]>>4;
								tmp = tmp&0x0f;
					 //			itoa(tmp, &Inbasechar[t*2], 16);
					 			if(tmp >= 10)
									Inbasechar[t*2] = tmp+55;
								if(tmp <10)
									Inbasechar[t*2] = tmp+48;
								tmp = Enchar[t]&0x0f;
					 //			itoa(tmp, &Inbasechar[t*2+1], 16);
					 			if(tmp >= 10)
									Inbasechar[t*2+1] = tmp+55;
								if(tmp <10)
									Inbasechar[t*2+1] = tmp+48;
							}

							String stortstr = Inbasechar;
							ADOQuery1->Edit();
							ADOQuery1->FieldByName("SuperPW")->AsAnsiString = Inbasechar;
							ADOQuery1->Post();

				   /*			String tmpCARDPassword = ADOQuery1->FieldByName("CARDMM")->AsAnsiString;
							for(int i = 0; i<6; i++)
							{
								int tmpint = StrToInt("0x"+tmpCARDPassword.SubString(i*2+1, 2));
								IntToUChar(tmpint, &CARDPassword[i]);
							}        */

							MessageBox(this->Handle, "³¬¼¶ÃÜÂëÐÞ¸Ä³É¹¦£¡", "³É¹¦", MB_OK|MB_ICONEXCLAMATION);
							this->Close();
						}
						else
							MessageBox(this->Handle, "³¬¼¶ÃÜÂë±ØÐëÎª12Î»", "´íÎó", MB_OK|MB_ICONERROR);
					}
					else
						MessageBox(this->Handle, "ÇëÊäÈëÁ½´ÎÏàÍ¬µÄÐÂÃÜÂë£¡", "´íÎó", MB_OK|MB_ICONERROR);
				}