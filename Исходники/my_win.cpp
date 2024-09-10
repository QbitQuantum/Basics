void PerfTimer::Dump(LogFile& logfile)
{
	std::wstring msg(L"---\n");
	const int BUFF_SIZE = 64;
	wchar_t buff[BUFF_SIZE];
	for (std::vector<std::pair<int, int64_t>>::iterator ti(_times.begin() + 1);
				ti != _times.end();
				++ti)
	{
		_itow_s(ti->first, buff, BUFF_SIZE, 10);
		msg += buff;
		msg += L' ';

		_i64tow_s(ti->second - _times.front().second, buff, BUFF_SIZE, 10);
		msg += buff;
		msg += L'\n';
	}

	logfile.Raw(msg);

	_times.clear();
}