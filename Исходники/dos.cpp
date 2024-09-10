/* windows NT DOS dir syntax.
 * looks like:
 *            1         2         3         4         5
 *  012345678901234567890123456789012345678901234567890
 *  06-29-95  03:05PM       <DIR>          muntemp
 *  05-02-95  10:03AM               961590 naxp11e.zip
 *  05-17-2007  07:58PM       <DIR>          muntemp
 *  09-09-2008  03:50AM                 1506 naxp11e.zip
 *  04-06-1995  02:03
 *  07-13-1995  11:39
 *  05-27-11  09:31       <DIR>          3

 *  The date time directory indicator and FindData.cFileName
 *  are always in a fixed position.  The file
 *  size always ends at position 37.
 */
BOOL WINAPI idPRParceDos(const FTPServerInfo* Server, FTPFileInfo* p, char *entry, int entry_len)
{
	NET_FileEntryInfo  entry_info;
	char              *e, *m;
	int offset = 0;
	CHECK((entry_len < 11), FALSE);

	if(entry[10] == ' ')
		offset = 2;

	CHECK((entry_len < 38+offset || entry[17+offset]!=' '), FALSE)
	CHECK((!net_parse_dos_date_time(entry, entry_info.date)), FALSE)
	// <DIR> | digits
	e = SkipSpace(SkipNSpace(entry+15));

	if(StrCmp(e, "<DIR> ",5,FALSE) == 0)
	{
		entry_info.FileType = NET_DIRECTORY;
		m = SkipSpace(e+5);
	}
	else
	{
		m = SkipNSpace(e);
		*m = 0;
		entry_info.size = AtoI(e,(__int64)-1);
		m = SkipSpace(m+1);
		CHECK((entry_info.size == -1), FALSE)
	}

	StrCpy(entry_info.FindData.cFileName, m, ARRAYSIZE(entry_info.FindData.cFileName));
	return ConvertEntry(&entry_info,p);
}