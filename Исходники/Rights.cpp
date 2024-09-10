//---------------------------------------------------------------------------
void __fastcall TRightsFrame::SetText(UnicodeString value)
{
  if (Text != value)
  {
    UnicodeString RightsStr = value;

    int P = RightsStr.LowerCase().Pos(FAddXToDirectoriesSuffix);
    bool AAddXToDirectories = (P > 0);
    if (AAddXToDirectories)
    {
      RightsStr.Delete(P, FAddXToDirectoriesSuffix.Length());
    }
    RightsStr = DeleteChar(DeleteChar(RightsStr, L'('), L')').Trim();
    TRights R = Rights;
    if (((RightsStr.Length() == 3) || (RightsStr.Length() == 4)) &&
        IsNumber(RightsStr))
    {
      R.Octal = RightsStr;
    }
    else
    {
      R.Text = RightsStr;
    }

    Rights = R;
    AddXToDirectories = AAddXToDirectories;
  }
}