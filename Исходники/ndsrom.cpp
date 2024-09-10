void NDSFile::readNames(Common::SeekableReadStream &nds, uint32 offset, uint32 length) {
	if (!nds.seek(offset + 8))
		throw Common::Exception(Common::kSeekError);

	uint32 index = 0;
	while (((uint32) nds.pos()) < (offset + length)) {
		Resource res;

		byte nameLength = nds.readByte();

		Common::UString name;

		name.readFixedASCII(nds, nameLength);
		name.tolower();

		res.name  = setFileType(name, kFileTypeNone);
		res.type  = getFileType(name);
		res.index = index++;

		_resources.push_back(res);
	}

	while (!_resources.empty() && _resources.back().name.empty())
		_resources.pop_back();
}