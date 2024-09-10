void DbFile::delRecord(DbRecord& record)
{
	record.getPage()->delRecord(record.getCursor());
}