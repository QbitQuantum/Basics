void VfkStream::Open(const VectorMap<int, String>& fns)
{
	Close();
	charset = CHARSET_ISO8859_2;
	file_groups <<= fns;
	streams.SetCount(file_groups.GetCount());
	for(int i = 0; i < streams.GetCount(); i++)
		if(!streams[i].Open(file_groups[i]))
			throw Exc(NFormat("cannot open file '%s'", file_groups[i]));
	indexfilename = GetTempFileName("vfk");
	if(!indexfile.Open(indexfilename, FileStream::CREATE))
		throw Exc(NFormat("cannot create indexfile '%s'", indexfilename));
	String hdrname = "X_HEADER";
	Table& hdr = tables.Add(hdrname);
	hdr.name = hdr.rawname = hdrname;
	hdr.header = true;
	hdr.row_count = 0;
	ASSERT(hdr.columns.GetCount() == HDR_ID);
	hdr.AddColumn(Column("ID", STRING_V, 30));
	ASSERT(hdr.columns.GetCount() == HDR_ORD);
	hdr.AddColumn(Column("ORD", INT_V));
	ASSERT(hdr.columns.GetCount() == HDR_STR);
	hdr.AddColumn(Column("STR", STRING_V, 1000));
	ASSERT(hdr.columns.GetCount() == HDR_NUM);
	hdr.AddColumn(Column("NUM", DOUBLE_V));
	ASSERT(hdr.columns.GetCount() == HDR_DTM);
	hdr.AddColumn(Column("DTM", TIME_V));
	ASSERT(hdr.columns.GetCount() == HDR_COUNT);
	Scan();
}