void FileTabs::AddFile(const WString &file, Image img, bool make_active)
{
	InsertFile(GetCount(), file, img, make_active);
}