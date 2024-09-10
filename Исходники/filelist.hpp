	void swap(FileListItem& rhs) noexcept
	{
		using std::swap;
		strName.swap(rhs.strName);
		swap(Selected, rhs.Selected);
		swap(PrevSelected, rhs.PrevSelected);
		swap(ShowFolderSize, rhs.ShowFolderSize);
		swap(ShortNamePresent, rhs.ShortNamePresent);
		swap(Colors, rhs.Colors);
		swap(NumberOfLinks, rhs.NumberOfLinks);
		swap(NumberOfStreams, rhs.NumberOfStreams);
		swap(UserFlags, rhs.UserFlags);
		swap(UserData, rhs.UserData);
		swap(Callback, rhs.Callback);
		swap(Position, rhs.Position);
		swap(SortGroup, rhs.SortGroup);
		swap(DizText, rhs.DizText);
		swap(DeleteDiz, rhs.DeleteDiz);
		strOwner.swap(rhs.strOwner);
		swap(CustomColumnData, rhs.CustomColumnData);
		swap(CustomColumnNumber, rhs.CustomColumnNumber);
		swap(CRC32, rhs.CRC32);
		swap(FileAttr, rhs.FileAttr);
		swap(CreationTime, rhs.CreationTime);
		swap(AccessTime, rhs.AccessTime);
		swap(WriteTime, rhs.WriteTime);
		swap(ChangeTime, rhs.ChangeTime);
		swap(FileSize, rhs.FileSize);
		swap(AllocationSize, rhs.AllocationSize);
		swap(StreamsSize, rhs.StreamsSize);
		strShortName.swap(rhs.strShortName);
		swap(ReparseTag, rhs.ReparseTag);
		ContentData.swap(rhs.ContentData);
	}