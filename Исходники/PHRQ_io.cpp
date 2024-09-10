/**
        Reads input stream until end of line, ";", or eof
        stores characters in line_save

        returns:
                EOF on empty line on end of file or
                OK otherwise
*/
PHRQ_io::LINE_TYPE PHRQ_io::
get_logical_line(void)
{
	int j;
	unsigned int pos;
	char c;

	m_line_save.erase(m_line_save.begin(), m_line_save.end());	// m_line_save.clear();
	while ((j = getc()) != EOF)
	{
		c = (char) j;
		if (c == '#')
		{
			// ignore all chars after # until newline
			do
			{
				c = (char) j;
				if (c == '\n')
				{
					break;
				}
				m_line_save += c;
			}
			while ((j = getc()) != EOF);
		}
		if (c == ';')
			break;
		if (c == '\n')
		{
			break;
		}
		if (c == '\\')
		{
			pos = (int) m_line_save.size();
			m_line_save += c;
			while ((j = getc()) != EOF)
			{
				c = (char) j;
				if (c == '\\')
				{
					pos = (int) m_line_save.size();
					m_line_save += c;
					continue;
				}
				if (c == '\n')
				{
					// remove '\\'
					m_line_save = m_line_save.substr(0,pos);
					break;
				}
				m_line_save += c;
				if (!::isspace(j))
					break;
			}
		}
		else
		{
			m_line_save += c;
		}
	}
	if (j == std::char_traits < char >::eof() && m_line_save.size() == 0)
	{
		return (LT_EOF);
	}
	return (LT_OK);
}