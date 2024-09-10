void RedirectStdio()
{
	std::string stdout_path = FileSystem::JoinPath(FileSystem::GetUserDir(), "stdout.txt");
	std::string stderr_path = FileSystem::JoinPath(FileSystem::GetUserDir(), "stderr.txt");
	std::wstring wstdout_path = transcode_utf8_to_utf16(stdout_path);
	std::wstring wstderr_path = transcode_utf8_to_utf16(stderr_path);

	FILE *f;

	f = _wfreopen(wstdout_path.c_str(), L"w", stdout);
	if (!f) {
		fprintf(stderr, "ERROR: Couldn't redirect stdout to '%s': %s\n", stdout_path.c_str(), strerror(errno));
	} else {
		setvbuf(f, 0, _IOLBF, BUFSIZ);
	}

	f = _wfreopen(wstderr_path.c_str(), L"w", stderr);
	if (!f) {
		fprintf(stderr, "ERROR: Couldn't redirect stderr to '%s': %s\n", stderr_path.c_str(), strerror(errno));
	} else {
		setvbuf(f, 0, _IOLBF, BUFSIZ);
	}
}