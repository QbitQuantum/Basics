//----------------------------------------------------------------------------------------
void nsFileSpecHelpers::NativeToUnix(nsSimpleCharString& ioPath)
// This just does string manipulation.  It doesn't check reality, or canonify, or
// anything.  The unix path is longer, so we can't do it in place.
//----------------------------------------------------------------------------------------
{
	if (ioPath.IsEmpty())
		return;
		
	// Convert the drive-letter separator, if present
	nsSimpleCharString temp("/");

	char* cp = (char*)ioPath + 1;
	if (strstr(cp, ":\\") == cp)
		*cp = '|';    // absolute path
    else
      if (cp[0] == '\\')	// unc path
        cp--;
        else
        temp[0] = '\0'; // relative path
	
	// Convert '\' to '/'
	for (; *cp; cp++)
    {
      if(IsDBCSLeadByte(*cp) && *(cp+1) != nsnull)
      {
         cp++;
         continue;
      }
      if (*cp == '\\')
        *cp = '/';
    }
	// Add the slash in front.
	temp += ioPath;
	ioPath = temp;
}