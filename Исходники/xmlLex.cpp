void xml::lex::getXMLDecl(xml::token *tok)
{
	static const char* s_version = "version";
	static const char* s_encoding = "encoding";
	static const char* s_standalone = "standalone";
	static const char* s_endXMLDecl = "?>";

xmlDecl:;

	switch (m_sstate)
	{
		case _xml_decl_version :
			if (handleWhitespace() == false)
			{
				throw GException("XML Parser", 20, m_line, m_byte);
			}
			if (handleReserved(s_version) == false)
			{
				throw GException("XML Parser", 13, m_line, m_byte);
			}
			getEqual();
			getQuote();
			tok->m_type = xml::_version;
			if (getVersion(tok) == false)
			{
				throw GException("XML Parser", 13, m_line, m_byte);
			}
			getQuote();
			m_sstate = xml::_xml_decl_encoding;
			break;
		case _xml_decl_encoding :
			handleWhitespace();
			if (handleReserved(s_encoding) != false)
			{
				getEqual();
				getQuote();
				tok->m_type = xml::_encoding;
				if (getEncoding(tok) == false)
				{
					throw GException("XML Parser", 14, m_line, m_byte);
				}
				getQuote();
			}
			else
			{
				m_sstate = xml::_xml_decl_standalone;
				goto xmlDecl;
			}
			m_sstate = xml::_xml_decl_standalone;
			break;
		case _xml_decl_standalone :
			handleWhitespace();
			if (handleReserved(s_standalone) != false)
			{
				getEqual();
				getQuote();
				tok->m_type = xml::_standalone;
				if (getStandalone(tok) == false)
				{
					throw GException("XML Parser", 15, m_line, m_byte);
				}
				getQuote();
			}
			handleWhitespace();
			if (handleReserved(s_endXMLDecl) == false)
			{
				throw GException("XML Parser", 3, m_line, m_byte);
			}
			m_state = xml::_misc;
	}
}