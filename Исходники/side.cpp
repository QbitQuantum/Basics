void side::makeLine(const _finddata_t &finfo, string &str) const
{
	str.clear();
	str += char(179);

	/*name*/
	if (strlen(finfo.name) > 19)
		str += string(finfo.name, 19);
	else
		str += finfo.name + string(19 - strlen(finfo.name), ' ');
	str += char(179);

	/*size*/

	string size;
	if (finfo.size >= 1000 * 1000 * 1000)  // > 1 gb
		size = std::to_string(finfo.size / (1024 * 1024 * 1024)) + ',' + std::to_string(finfo.size % (1024 * 1024 * 1024) / 1024 / 1024 *100 / 1024) + 'G';
	else if (finfo.size >= 1000 * 1000)  // > 1 mb < 1 gb
		size = std::to_string(finfo.size / (1024 * 1024)) + ',' + std::to_string(finfo.size % (1024 * 1024) * 100 / (1024 * 1024)) + 'M';
	else if (finfo.size >= 1000)  // > 1 kb < 1 mb
		size = std::to_string(finfo.size / 1024) + ',' + std::to_string(finfo.size % 1024 * 100 / 1024) + 'K';
	else // < 1 kb
		size = std::to_string(finfo.size) + 'B';

	if (size.size() > 7)
		throw string("lenght of str:size > 7 : ") + size;

	if (size.size() < 7)
		size.insert(0, 7 - size.size(), ' ');

	str += size + char(179);

	/*date*/
	tm t;
	localtime_s(&t, &finfo.time_write);
	if (t.tm_mday < 10)
		str += '0';
	str += std::to_string(t.tm_mday) + '.';
	if (t.tm_mon < 9)
		str += '0';
	str += std::to_string(t.tm_mon + 1) + '.' + std::to_string(t.tm_year + 1900);
	str += char(179);


}