bool CGUIDialogPluginSettings::TranslateSingleString(const CStdString &strCondition, vector<CStdString> &condVec)
{
  CStdString strTest = strCondition;
  strTest.ToLower();
  strTest.TrimLeft(" ");
  strTest.TrimRight(" ");

  int pos1 = strTest.Find("(");
  int pos2 = strTest.Find(",");
  int pos3 = strTest.Find(")");
  if (pos1 >= 0 && pos2 > pos1 && pos3 > pos2)
  {
    condVec.push_back(strTest.Left(pos1));
    condVec.push_back(strTest.Mid(pos1 + 1, pos2 - pos1 - 1));
    condVec.push_back(strTest.Mid(pos2 + 1, pos3 - pos2 - 1));
    return true;
  }
  return false;
}