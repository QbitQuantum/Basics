//------------------------------------------------------------------------
bool XmlRepresentationHelper::startPage (FIDString name, int32 unitID)
{
	if (!checkState (kInPage))
		return false;

	StringWriter writer (stream);
	String string;
	if (unitID != -1)
		string.printf ("<%s %s=\"%s\" %s=\"%d\">", PAGE_TAG, ATTR_NAME, name, ATTR_UNITID, unitID);
	else
		string.printf ("<%s %s=\"%s\">", PAGE_TAG, ATTR_NAME, name);
	writer.write (string);
	writer.write (ENDLINE_A);

	return true;
}