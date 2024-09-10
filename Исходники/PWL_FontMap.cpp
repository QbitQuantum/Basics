CFX_ByteString CPWL_FontMap::EncodeFontAlias(const CFX_ByteString& sFontName)
{
	CFX_ByteString sRet = sFontName;
	sRet.Remove(' ');
	return sRet;
}