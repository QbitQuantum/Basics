time_t utils::time::from_string(const std::string &data)
{
	long long timestamp = _strtoi64(data.c_str(), NULL, 10);

	// If it is milli timestamp
	if (timestamp > 100000000000)
		timestamp /= 1000;

	// If conversion fails, use local time?
	//if (!timestamp)
	//	timestamp = ::time(NULL);

	return (time_t)timestamp;
}