void DefaultValidator::applyUpper(NAString &value) const
{
  switch (caseSensitive()) {
    case CASE_SENSITIVE:	return;
    case CASE_INSENSITIVE:	value.toUpper(); return;
    case CASE_SENSITIVE_ANSI:	{
				  // Make copy of value so we can own its data()
				  // for casting away const-ness.
				  NAString tmp(value);
				  char *s = (char *)tmp.data();
				  for (NABoolean quoted = FALSE; *s; s++) {
				    if (*s == '"')
				      quoted = !quoted;
				    else if (!quoted)
#pragma nowarn(1506)   // warning elimination 
				      *s = toupper(*s);
#pragma warn(1506)  // warning elimination 
				  }
				  value = tmp;
				  return;
    				}
    default:			CMPASSERT(FALSE);
  }
}