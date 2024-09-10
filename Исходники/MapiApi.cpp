void CMapiFolderList::ChangeName( nsString& name)
{
  if (name.IsEmpty()) {
    name.AssignLiteral("1");
    return;
  }
  PRUnichar lastC = name.Last();
  if ((lastC >= '0') && (lastC <= '9')) {
    lastC++;
    if (lastC > '9') {
      lastC = '1';
      name.SetCharAt( lastC, name.Length() - 1);
      name.AppendLiteral("0");
    }
    else {
      name.SetCharAt( lastC, name.Length() - 1);
    }
  }
  else {
    name.AppendLiteral(" 2");
  }
}