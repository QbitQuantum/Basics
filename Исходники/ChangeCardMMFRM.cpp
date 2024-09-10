void __fastcall TChangeCardMMForm::cxButton1Click(TObject *Sender)
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
                ADOQuery1->SQL->Add("Select * from WXTSET");
                ADOQuery1->Open();
                //		String tmpstr = ADOQuery1->FieldByName("CARDMM")->AsString;
                //ShowMessage(tmpstr);
                String oldpw = ADOQuery1->FieldByName("CARDMM")->AsString.Trim();

                unsigned int cmplen = 12;
                if(oldpw == Oldpwstr)//tmpstr == Oldpwstr)
                {
                    if(Newpwstr1 == Newpwstr2)
                    {
                        if(12 == Newpwstr1.Length())
                        {


                            ADOQuery1->Edit();
                            ADOQuery1->FieldByName("CARDMM")->AsAnsiString = Newpwstr1;
                            ADOQuery1->Post();
                            ADOQuery1->Close();

                            unsigned char TCARDPassword[16];
                            AnsiString tmpCARDPassword = Newpwstr1;
                            memcpy(TCARDPassword, tmpCARDPassword.c_str(), 16);

                            for(int i = 0; i < 6; i++)
                            {
                                int tmpint = StrToInt("0x"+tmpCARDPassword.SubString(i*2+1, 2));
                                IntToUChar(tmpint, &CARDPassword[i]);
                            }

                            MessageBox(this->Handle, "密码修改成功！", "成功", MB_OK|MB_ICONEXCLAMATION);
                            this->Close();
                        }
                        else
                            MessageBox(this->Handle, "密码必须为12位", "错误", MB_OK|MB_ICONERROR);
                    }
                    else
                        MessageBox(this->Handle, "请输入两次相同的新密码！", "错误", MB_OK|MB_ICONERROR);
                }
                else
                {
                    MessageBox(this->Handle, "旧密码错误!", "错误", MB_OK|MB_ICONERROR);
                }
                ADOQuery1->Close();
            }
            else
            {
                //	ShowMessage("两次输入的密码不一致！");
                MessageBox(this->Handle, "两次输入的密码不一致！", "错误", MB_OK|MB_ICONERROR);
            }
        }
    }
    else
        MessageBox(this->Handle, "旧密码不为空！", "错误", MB_OK|MB_ICONERROR);
}