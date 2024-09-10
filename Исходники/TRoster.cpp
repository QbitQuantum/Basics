bool
TRoster::_IsSystemApp(RosterAppInfo* info) const
{
	BPath path;
	if (path.SetTo(&info->ref) != B_OK || path.GetParent(&path) != B_OK)
		return false;

	return !strcmp(path.Path(), fSystemAppPath.Path())
		|| !strcmp(path.Path(), fSystemServerPath.Path());
}