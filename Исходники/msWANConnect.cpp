//_______________________________________________________________________
static Boolean connect (short ref)
{
	MidiName name = MidiGetName(ref);
	if (!name) return false;
	if (gAddr.SetAddress (name)) {
		MidiConnect (gSrc, ref, true);
		return true;
	}
	if (strlen(name) >= 31) {
		MidiConnect (gSrc, ref, true);
		return true;
	}
	return false;
}