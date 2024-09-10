size_t GDAFile::findColumn(const Common::UString &name) const {
	ColumnNameMap::const_iterator c = _columnNameMap.find(name);
	if (c != _columnNameMap.end())
		return c->second;

	size_t column = findColumn(Common::hashStringCRC32(name.toLower(), Common::kEncodingUTF16LE));
	_columnNameMap[name] = column;

	return column;
}