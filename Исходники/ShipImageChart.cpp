bool OutputImage (CG16bitImage &Image, const CString &sFilespec)
	{
	if (!sFilespec.IsBlank())
		{
		if (Image.SaveAsWindowsBMP(sFilespec) != NOERROR)
			{
			printf("Unable to save to '%s'\n", sFilespec.GetASCIIZPointer());
			return false;
			}

		printf("%s\n", sFilespec.GetASCIIZPointer());
		}

	//	Otherwise, clipboard

	else
		{
		if (Image.CopyToClipboard() != NOERROR)
			{
			printf("Unable to copy to clipboard.\n");
			return false;
			}

		printf("Image copied to clipboard.\n");
		}

	//	Done

	return true;
	}