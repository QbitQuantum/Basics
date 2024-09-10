std::string Stopwatch::ToMilliSecondsString() const
{
	const long double msec = roundl(Seconds()*10000.0)/10.0;
	std::stringstream str;
	if(msec >= 10.0)
		str << roundl(Seconds()*1000.0) << "ms";
	else
		str << msec << "ms";
	return str.str();
}