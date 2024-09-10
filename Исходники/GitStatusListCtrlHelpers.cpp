bool CSorter::operator() (const CTGitPath* entry1 , const CTGitPath* entry2) const
{
#define SGN(x) ((x)==0?0:((x)>0?1:-1))

	int result = 0;
	switch (sortedColumn)
	{
	case 7: // File size
		{
			if (result == 0)
			{
				__int64 fileSize1 = entry1->IsDirectory() ? 0 : entry1->GetFileSize();
				__int64 fileSize2 = entry2->IsDirectory() ? 0 : entry2->GetFileSize();
				
				result = int(fileSize1 - fileSize2);
			}
		}
	case 6: //Last Modification Date
		{
			if (result == 0)
			{
				__int64 writetime1 = entry1->GetLastWriteTime();
				__int64 writetime2 = entry2->GetLastWriteTime();

				FILETIME* filetime1 = (FILETIME*)(__int64*)&writetime1;
				FILETIME* filetime2 = (FILETIME*)(__int64*)&writetime2;

				result = CompareFileTime(filetime1, filetime2);
			}
		}
	case 5: //Del Number
		{
			if (result == 0)
			{
//				result = entry1->lock_comment.CompareNoCase(entry2->lock_comment);
				result = A2L(entry1->m_StatDel)-A2L(entry2->m_StatDel);
			}
		}
	case 4: //Add Number
		{
			if (result == 0)
			{
				//result = entry1->lock_owner.CompareNoCase(entry2->lock_owner);
				result = A2L(entry1->m_StatAdd)-A2L(entry2->m_StatAdd);
			}
		}

	case 3: // Status
		{
			if (result == 0)
			{
				result = entry1->GetActionName(entry1->m_Action).CompareNoCase(entry2->GetActionName(entry2->m_Action));
			}
		}
	case 2: //Ext file
		{
			if (result == 0)
			{
				result = entry1->GetFileExtension().CompareNoCase(entry2->GetFileExtension());
			}
		}
	case 1: // File name
		{
			if (result == 0)
			{
				result = entry1->GetFileOrDirectoryName().CompareNoCase(entry2->GetFileOrDirectoryName());
			}
		}
	case 0: // Full path column
		{
			if (result == 0)
			{
				result = CTGitPath::Compare(entry1->GetGitPathString(), entry2->GetGitPathString());
			}
		}
	} // switch (m_nSortedColumn)
	if (!ascending)
		result = -result;

	return result < 0;
}