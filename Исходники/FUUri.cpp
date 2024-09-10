FUUri::FUUri(const fstring& uri, bool escape)
	:	scheme(FUUri::NONE),
		port(0),
		path(FC(""))
{
	if (uri.empty()) return;

	fstring _uri;

	if (escape)
	{
		_uri = Escape(uri);
	}
	else
	{
		_uri = uri;
	}

	// Replace all '\\' characters by '/' so the path is only using them
	_uri.replace(FC('\\'), FC('/'));

	// Find the scheme from its ':' delimiter
	size_t schemeDelimiterIndex = _uri.find(FC(':'));
	size_t hostIndex = 0;

	if (schemeDelimiterIndex != fstring::npos && schemeDelimiterIndex > 1)
	{
		fstring _scheme = _uri.substr(0, schemeDelimiterIndex);

		if (IsEquivalent(_scheme, FC("FILE")) || IsEquivalent(_scheme, FC("file")))
		{
			scheme = FUUri::FILE;
		}
		else if (IsEquivalent(_scheme, FC("FTP")) || IsEquivalent(_scheme, FC("ftp")))
		{
			scheme = FUUri::FTP;
		}
		else if (IsEquivalent(_scheme, FC("HTTP")) || IsEquivalent(_scheme, FC("http")))
		{
			scheme = FUUri::HTTP;
		}
		else if (IsEquivalent(_scheme, FC("HTTPS")) || IsEquivalent(_scheme, FC("https")))
		{
			scheme = FUUri::HTTPS;
		}
		else
		{
#ifdef WIN32
			// Scheme not supported (could be a NFS path)
			FUFail(return);
#endif // WIN32
		}

		schemeDelimiter = _uri.substr(schemeDelimiterIndex, 3);
		hostIndex = schemeDelimiterIndex + 3;
	}