std::string cil::CILKeyboardState::ToAscii( CIL_KEY key )
{
	std::string out;
	int scan;
	USHORT buff[2];

	scan = MapVirtualKeyEx(key, 0, m_keyboardLayout);
	if ( ToAsciiEx(key, scan, m_keys, buff, 0, m_keyboardLayout) > 0)
	{
		out += (char)buff[0];
	};
	
	return out;
}