/*____________________________________________________________________*/
int Open (void)
{
	refNum= MidiOpen( ApplName);
	if (refNum > 0) {
		myFilterPtr = NewFilter();
		if (!myFilterPtr) {
			Close ();
			return false;
		}
		MidiConnect( refNum, refNum, true);
		MidiSetFilter( refNum, myFilterPtr);
		return true;
	}
	return false;
}