bool ParsePathAndCaptureID(char *p, char *buf, int bufSize, char **pPath, char **pCaptureID)
{
	if (!p || *p == '\0')
	{
		// prompt for path and capture id
		std::cout<<"Enter the path: ";
		//std::getline(std::cin, line);
		gets_s(buf, bufSize);
		*pPath = buf;

		size_t len = strlen(buf);
		buf[len] = '\0';
		std::cout<<"Enter the capture id: ";
		//std::getline(std::cin, line);
		gets_s(buf+len+1, bufSize-len-1);
		*pCaptureID = buf+len+1;
	} else {
		// some characters on the line - split at comma
		*pPath = p;
		*pCaptureID = p;
		while(**pCaptureID != '\0')
		{
			if (**pCaptureID == ',' )
			{
				**pCaptureID = '\0';
				(*pCaptureID)++;
				break;
			} else {
				(*pCaptureID)++;
			}
		}
	}

	return true;
}