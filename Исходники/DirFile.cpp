uint8* DirFile::getObject(const std::string& name, uint32* sizep)
{
	FileSystem* filesys = FileSystem::get_instance();
	IDataSource* ids = filesys->ReadFile(path + name);
	if (!ids) return 0;

	uint32 size = ids->getSize();
	if (size == 0) return 0;

	uint8* buf = new uint8[size];
	ids->read(buf, size);
	delete ids;

	if (sizep) *sizep = size;

	return buf;
}