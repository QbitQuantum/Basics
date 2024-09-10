TBool CExampleCookieManager::CheckPathMatch(CCookie& aCookie, const TUriC8& aUri) const
	{
	THTTPHdrVal attributeVal;
	aCookie.Attribute(CCookie::EPath, attributeVal);
	TPtrC8 cookiePath = RemoveQuotes(attributeVal.StrF().DesC());

	const TDesC8& uriPath = aUri.Extract(EUriPath);
	if(uriPath.Length() == 0)
		{
		// if the uri has no path then it matches against no cookie path
		// or a cookie path of just a /
		const TInt pathLength = cookiePath.Length();
		if(pathLength == 0 || pathLength == 1)
			return ETrue;
		}
	else if(uriPath.FindF(cookiePath) == 0)
		{
		TChar separator('/');
		// Check that the character after the matched bit is a / otherwise
		// /path would match against /path2
		const TInt uriLength = uriPath.Length();
		const TInt cookieLength = cookiePath.Length();

		if(uriLength == cookieLength)
			return ETrue;
		else if(uriLength > cookieLength)
			{
			if(cookiePath[cookieLength - 1] == TUint(separator))
				return ETrue;
			else if(uriPath[cookieLength] == TUint(separator))
				return ETrue;
			}
		}

	return EFalse;
	}