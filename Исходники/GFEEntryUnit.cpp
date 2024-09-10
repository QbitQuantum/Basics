bool __fastcall TEntryForm::InValidDouble(AnsiString label, TEditPlus *edit)
{
  AnsiString ud = edit->Text;
  if (ud[1] == '-')
    ud.Delete(1,1);
  if (strspn(ud.c_str(), "0123456789.") == (unsigned)ud.Length())
    return false;
  AnsiString msg = "The field "+label+" contains the value '"+edit->Text+"'."
                  +" This is invalid for a non null double field";
  Application->MessageBox(msg.c_str(), "Invalid Double", ID_OK);
  return true;
}