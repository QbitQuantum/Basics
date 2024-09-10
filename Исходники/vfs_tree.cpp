std::wstring FileDescription(const VfsFile& file)
{
	wchar_t timestamp[25];
	const time_t mtime = file.MTime();
	wcsftime(timestamp, ARRAY_SIZE(timestamp), L"%a %b %d %H:%M:%S %Y", localtime(&mtime));

	wchar_t buf[200];
	swprintf_s(buf, ARRAY_SIZE(buf), L"(%c; %6lu; %ls) %ls", file.Loader()->LocationCode(), (unsigned long)file.Size(), timestamp, file.Name().string().c_str());
	return buf;
}