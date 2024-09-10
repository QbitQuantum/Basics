int savefile()
{
	boost::shared_lock<boost::shared_mutex> lock(g_mutex, boost::defer_lock);

	lock.lock();
	std::vector<std::string> vhash_inf(hasinf_list.size());
	std::copy(hasinf_list.begin(), hasinf_list.end(), vhash_inf.begin());
	hasinf_list.clear();
	lock.unlock();

	if (vhash_inf.size() <= 0)
	{
		return 0;
	}
	
	char buf[64] = {0};
	_i64toa(time(0), buf, 10);

	std::string fileName = strTmpPath + buf + std::string(".t");
	std::string fileName2 = strDataPath + buf + std::string(".t");

	FILE *f = fopen(fileName.c_str(), "w+");
	if (f == NULL)
	{
		return -1;
	}
	
	for (int i = 0; i < vhash_inf.size(); i++)
	{
		fprintf(f, "%s|", vhash_inf[i].c_str());
	}

	fclose(f);

	MoveFileA(fileName.c_str(), fileName2.c_str());

	return 0;
}