		Air::U32 Converter::ToHex( const AString& str )
		{
			U32 uiHex=0;
			sscanf_s(str.c_str(),"%x",&uiHex);
			return uiHex;
		}