//////////
//
// Find the indicated class based on its name
//
//////
	SClassX* iHwndX_findClass_byName(cs8* lpClassName)
	{
		u32			lnI, lnLength;
		SClassX*	cls;


		// Make sure our environment is sane
		if (lpClassName)
		{
			// Iterate through each class until we find the correct one
			lnLength = strlen(lpClassName);
			for (lnI = 0, cls = (SClassX*)gsClasses->buffer; lnI < gsClasses->populatedLength; lnI += sizeof(SClassX), cls++)
			{
				// If it's valid, and the class maches, we're good
				if (cls->isValid && strlen(cls->wcx.lpszClassName) == lnLength && _memicmp(cls->wcx.lpszClassName, lpClassName, lnLength) == 0)
					return(cls);
			}
			// If we get here, the class was not found
		}

		// If we get here, invalid
		return(NULL);
	}