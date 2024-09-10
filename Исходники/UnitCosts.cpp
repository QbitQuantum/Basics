//---------------------------------------------------------------------------
void __fastcall TFormCosts::Button1Click(TObject *Sender)
{
    if(Edit1->Text != "" && Edit2->Text != "")
    {
        if(CheckBox1->Checked)
        {
            //if(StrToInt(Label4->Caption) - StrToInt(Edit2->Text) >= 0)
            //{
                if(ComboBox1->Text == "Одноразовый")
                {
                    int Income = IniFile->ReadInteger("Resource", "ofMonth", 0) - StrToInt(Edit2->Text);
                    IniFile->WriteInteger("Resource", "ofMonth", Income);
                }             
                if(ADOQuery1->Active)
                {
                    ADOQuery1->Active = false;
                }
                ADOQuery1->SQL->Text = "INSERT INTO Costs VALUES('"+IntToStr(FilingYID())+"', '"+Edit1->Text+"', '"+Edit2->Text+"', '"+ComboBox1->Text+"', '"+DateTimePicker1->Date+"', '1', '0')";
                ADOQuery1->ExecSQL();
            /*}
            else
            {
                ShowMessage("Недостаточно средств!");
            }*/
        }
        else
        {
            if(ADOQuery1->Active)
            {
                ADOQuery1->Active = false;
            }
            ADOQuery1->SQL->Text = "INSERT INTO Costs VALUES('"+IntToStr(FilingYID())+"', '"+Edit1->Text+"', '"+Edit2->Text+"', '"+ComboBox1->Text+"', '"+DateTimePicker1->Date+"', '0', '0')";
            ADOQuery1->ExecSQL();
        }
        
        
    }
    else
    {    
        ShowMessage("Заполните поля!");
    }
    if(ADOQuery1->Active)
	{
		ADOQuery1->Active = false;
        ADOQuery2->Active = false;
	}
	ADOQuery1->SQL->Text = "SELECT * FROM Costs";
    ADOQuery2->SQL->Text = "SELECT * FROM Costs";
	ADOQuery1->Active = true;
    ADOQuery2->Active = true;
    Label4->Caption = IniFile->ReadString("Resource", "ofMonth", "0");
    ShowScrollBar(DBGrid1->Handle, SB_BOTH, false);
}