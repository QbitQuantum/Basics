bool ParseVector2				(std::wifstream& in, vec2& v)				
{
	std::wstring buff;
	in >> buff;
	if(!isdigit(buff[0]) && buff[0] != '-')	return false;
	v.x = (FLOAT)_wtof(buff.c_str());
	in >> buff;
	if(!isdigit(buff[0]) && buff[0] != '-')	return false;
	v.y = (FLOAT)_wtof(buff.c_str());

	return true;
}