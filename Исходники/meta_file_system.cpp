size_t MetaFileSystem::WriteFile(u32 handle, const u8 *pointer, s64 size)
{
	std::lock_guard<std::recursive_mutex> guard(lock);
	IFileSystem *sys = GetHandleOwner(handle);
	if (sys)
		return sys->WriteFile(handle,pointer,size);
	else
		return 0;
}