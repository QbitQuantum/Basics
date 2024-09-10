int64_t CQueueStorage::Impl::SaveLocalPath(const CLocalPath& path)
{
	std::unordered_map<wxString, int64_t, wxStringHash, fast_equal>::const_iterator it = localPaths_.find(path.GetPath());
	if (it != localPaths_.end())
		return it->second;

	Bind(insertLocalPathQuery_, path_table_column_names::path, path.GetPath());

	int res;
	do {
		res = sqlite3_step(insertLocalPathQuery_);
	} while (res == SQLITE_BUSY);

	sqlite3_reset(insertLocalPathQuery_);

	if (res == SQLITE_DONE)
	{
		int64_t id = sqlite3_last_insert_rowid(db_);
		localPaths_[path.GetPath()] = id;
		return id;
	}

	return -1;
}