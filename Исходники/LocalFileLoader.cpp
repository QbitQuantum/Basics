LocalFileLoader::LocalFileLoader(const std::string &filename)
	: filesize_(0), filename_(filename) {
	if (filename.empty()) {
		ERROR_LOG(FILESYS, "LocalFileLoader can't load empty filenames");
		return;
	}
#ifndef _WIN32

	fd_ = open(filename.c_str(), O_RDONLY | O_CLOEXEC);
	if (fd_ == -1) {
		return;
	}
#if PPSSPP_PLATFORM(ANDROID) || (defined(_FILE_OFFSET_BITS) && _FILE_OFFSET_BITS < 64)
	off64_t off = lseek64(fd_, 0, SEEK_END);
	filesize_ = off;
	lseek64(fd_, 0, SEEK_SET);
#else
	off_t off = lseek(fd_, 0, SEEK_END);
	filesize_ = off;
	lseek(fd_, 0, SEEK_SET);
#endif

#else // _WIN32

	const DWORD access = GENERIC_READ, share = FILE_SHARE_READ, mode = OPEN_EXISTING, flags = FILE_ATTRIBUTE_NORMAL;
#if PPSSPP_PLATFORM(UWP)
	handle_ = CreateFile2(ConvertUTF8ToWString(filename).c_str(), access, share, mode, nullptr);
#else
	handle_ = CreateFile(ConvertUTF8ToWString(filename).c_str(), access, share, nullptr, mode, flags, nullptr);
#endif
	if (handle_ == INVALID_HANDLE_VALUE) {
		return;
	}
	LARGE_INTEGER end_offset;
	const LARGE_INTEGER zero = { 0 };
	if (SetFilePointerEx(handle_, zero, &end_offset, FILE_END) == 0) {
		// Couldn't seek in the file. Close it and give up? This should never happen.
		CloseHandle(handle_);
		handle_ = INVALID_HANDLE_VALUE;
		return;
	}
	filesize_ = end_offset.QuadPart;
	SetFilePointerEx(handle_, zero, nullptr, FILE_BEGIN);
#endif // _WIN32
}