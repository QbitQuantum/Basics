String SystemLinux::GetDataDirName(const String &sName) const
{
	// Return ".<name>"
	String sLower = sName;
	sLower.ToLower();
	return "." + sLower;
}