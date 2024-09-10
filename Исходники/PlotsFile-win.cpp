void PlotsFile::preallocate(const std::string& p_path, unsigned long long p_size) throw (std::exception) {
	bool granted = setPrivilege();

	HANDLE out = CreateFileA(p_path.c_str(), GENERIC_WRITE, 0, 0, OPEN_ALWAYS, FILE_FLAG_NO_BUFFERING, 0);
	if(out == INVALID_HANDLE_VALUE) {
		std::ostringstream msg;
		msg << "Unable to open the output file: " << GetLastError();
		throw std::runtime_error(msg.str().c_str());
	}

	LARGE_INTEGER targetPointer;
	targetPointer.QuadPart = p_size;
	SetFilePointerEx(out, targetPointer, 0, FILE_BEGIN);
	if(SetEndOfFile(out) == 0) {
		CloseHandle(out);

		std::ostringstream msg;
		msg << "Unable to extend output file: " << GetLastError();
		throw std::runtime_error(msg.str().c_str());
	}

	if(granted) {
		if(SetFileValidData(out, p_size) == 0) {
			CloseHandle(out);

			std::ostringstream msg;
			msg << "Unable to prevent zero filling: " << GetLastError();
			throw std::runtime_error(msg.str().c_str());
		}
	}

	CloseHandle(out);
}