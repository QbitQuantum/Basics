bool http_t::download( std::string& result,
                       const std::string& url )
{
  // hINet = InternetOpen( L"Firefox/3.0", INTERNET_OPEN_TYPE_PROXY, "proxy-server", NULL, 0 );

  result = "";
  HINTERNET hINet, hFile;
  hINet = InternetOpen( L"Firefox/3.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
  if ( hINet )
  {
    std::wstring wURL( url.length(), L' ' );
    std::copy( url.begin(), url.end(), wURL.begin() );

    std::wstring wHeaders = L"";
    wHeaders += L"Cookie: loginChecked=1\r\n";
	  wHeaders += L"Cookie: cookieLangId=en_US\r\n";

    hFile = InternetOpenUrl( hINet, wURL.c_str(), wHeaders.c_str(), 0, INTERNET_FLAG_RELOAD, 0 );
    if ( hFile )
    {
      char buffer[ 20000 ];
      DWORD amount;
      while ( InternetReadFile( hFile, buffer, sizeof( buffer )-2, &amount ) )
      {
        if ( amount > 0 )
        {
          buffer[ amount ] = '\0';
          result += buffer;
        }
        else break;
      }
      InternetCloseHandle( hFile );
    }
    InternetCloseHandle( hINet );
  }
  return result.size() > 0;
}