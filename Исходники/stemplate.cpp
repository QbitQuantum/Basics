void WebAddress::Combine(WebAddress Base)
{
	//Strings are hard coded to reduce code size
	String_256 sSlashDotSlash="/./";
	String_256 sSlashDotDotSlash="/../";
	
	TCHAR cSlash='/';

	//Now start the parsing.

	//If the base Web Address is empty, this Web Address does not change
	if (Base.IsEmpty())
		goto ReturnNow;

	//If this Web Address is empty, then it inherits everything from the 
	//base Web Address
	if (IsEmpty())
	{
		Absolute = Base.Absolute;

		Scheme=Base.Scheme;
		NetLoc=Base.NetLoc;
		Path=Base.Path;
		Parameters=Base.Parameters;
		Query=Base.Query;
		Fragment=Base.Fragment;
		goto ReturnNow;
	}

	//If this Web Address is absolute, it does not change
	if (IsAbsolute())
		goto ReturnNow;

	//If none of the above apply, this Web Address inherits the scheme of
	//the Base address
	Scheme=Base.Scheme;

	//If this Web Address has a net location, we need do nothing more to it.
	if (!NetLoc.IsEmpty())
		goto ReturnNow;

	//Otherwise, this Web Address inherits the Net Location of the base address.
	NetLoc=Base.NetLoc;

	//If the path of this Web Address starts with a slash, it is non-relative
	//and we need only add it on to the Net Location
	if ((*(Path))==cSlash) goto ReturnNow;


	//This is where all the loops within loops start. Hang on to your curly brackets.

	//Does this Web Address have a path?
	if (!Path.IsEmpty())
	{
		//Yes. Then the full path is given by:
		//The Base URL path up to the rightmost slash + the URL of this Web Address
		
		//This string will hold the base URL path up to the rightmost slash
		String_256 sTempPath="";
		
		//First find the rightmost slash in Base.Path
		INT32 iFound=Base.Path.ReverseFind(cSlash);
		
		//Did we find a slash?
		if (iFound>=0)
		{
			//Yes. So copy everything up to that slash into sTempPath


			Base.Path.Split(&sTempPath, NULL, iFound, TRUE);
			
			sTempPath+=Path;

			Path=sTempPath;
		}//End IF there's a slash in Base.Path

		
		//We now need to check the path for ../ and ./
		//First let's search for /./
		iFound=Path.Sub(sSlashDotSlash);

		//If we've found a /./
		while (iFound>=0)
		{
			//Then remove the ./ part of it.
			Path.Remove(iFound+1, 2);

			//And look for the next /./ to remove
			iFound=Path.Sub(sSlashDotSlash);
		}

		//Now we want to remove all occurrences of /[path segment/../
		//So first let's do a search for /../
		
		iFound=Path.Sub(sSlashDotDotSlash);

		//If we've found a /./
		while (iFound>=0)
		{
			//Then go back until we find the start of the path segment before it
			INT32 iStartOfSection=iFound-1;

			while (iStartOfSection>=0 && Path[iStartOfSection]!=cSlash)
				iStartOfSection--;

			if (iStartOfSection>=0)
			{
				//Get iStartOfSection to represent the character after the slash,
				//rather than the slash
				iStartOfSection++;

				//So if we've found something, then set a pointer to the end of that
				//section
				INT32 iEndOfSection=iFound+3;

				Path.Remove(iStartOfSection, (iEndOfSection-iStartOfSection+1));
			}
			else
				//If we found an unparsable /../, then break now before we
				//get into trouble...
				break;

			//And find the next /../
			iFound=Path.Sub(sSlashDotDotSlash);
		}	
	}
	else
	{
		//No, this Web Address doesn't have a path.
		//So it inherits the path of the base URL.
		Path=Base.Path;

		//If this Web Address has some parameters, we need do nothin more to it
		if (!Parameters.IsEmpty())
			goto ReturnNow;

		//Otherwise this Web Address inherits the parameters of the base URL
		Parameters=Base.Parameters;

		//If this Web Address has a query, we need do nothin more to it
		if (!Query.IsEmpty())
			goto ReturnNow;

		//Otherwise this Web Address inherits the parameters of the base URL
		Query=Base.Query;

		//And that's it. (Fragments are never inherited).
		//So we can return.
		goto ReturnNow;

	}//End if (!Path.IsEmpty()) else...

ReturnNow:
	//Set the "Absolute" flag to whatever it's meant to be, and return
	SetFlags();
	return;
}