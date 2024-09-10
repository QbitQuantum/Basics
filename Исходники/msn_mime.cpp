void MimeHeaders::addULong(const char* name, unsigned lValue)
{
	MimeHeader& H = mVals[allocSlot()];
	H.name = name;

	char szBuffer[20];
	_ultoa(lValue, szBuffer, 10);
	H.value = mir_strdup(szBuffer); 
	H.flags = 2;
}