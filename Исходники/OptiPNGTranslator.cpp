status_t
OptiPNGTranslator::DerivedTranslate(BPositionIO *source,
	const translator_info *info, BMessage *ioExtension,
	uint32 outType, BPositionIO *target, int32 baseType)
{
	if(baseType == 1 && outType == OPTIPNG_PNG_FORMAT) {
		// create temp file
		int tempFileFD;
		BPath tempDir;
		BString tempFilePath;
		if(find_directory(B_SYSTEM_TEMP_DIRECTORY, &tempDir) != B_OK )
			return B_ERROR;
		
		tempFilePath.Append(tempDir.Path())
			.Append("/OptiPNGTranslator.XXXXXX");
		
		tempFileFD = mkstemp(tempFilePath.LockBuffer(0));
		tempFilePath.UnlockBuffer();
		
		if(tempFileFD == -1)
			return B_ERROR;
		close(tempFileFD);
		
		BFile tempFile = BFile(tempFilePath, O_WRONLY);
		
		// write PNG to file
		off_t sourceSize;
		source->GetSize(&sourceSize);
		unsigned char sourceChars[sourceSize];
		
		BTranslatorRoster *roster = BTranslatorRoster::Default();
		roster->Translate(source, NULL, NULL, &tempFile, (uint32)B_PNG_FORMAT);
		
		// optimize file
		BString optipng;
		if(system("optipng &> /dev/null") == 0) {
			optipng = "optipng";
		} else if(system("optipng-x86 &> /dev/null") == 0) {
			optipng = "optipng-x86";
		} else {
			return B_ERROR;
		}
		
		// optipng -clobber -out (file) (file)
		BString command;
		command = optipng;
		if(!fSettings->SetGetBool(OPTIPNG_SETTING_BIT_DEPTH_REDUCTION))
			command += " -nb"; // no bit-depth reduction
		if(!fSettings->SetGetBool(OPTIPNG_SETTING_COLOR_TYPE_REDUCTION))
			command += " -nc";
		if(!fSettings->SetGetBool(OPTIPNG_SETTING_PALETTE_REDUCTION))
			command += " -np";
		
		command.Append(" -o")
			.Append((char)(fSettings->
				SetGetInt32(OPTIPNG_SETTING_OPTIMIZATION_LEVEL)+'0'),1);
		// rest of command
		command.Append(" -clobber -out ")
			.Append(tempFilePath)
			.Append(" ")
			.Append(tempFilePath)
		;
		
		if(system(command) != 0) {
			return B_ERROR;
		}
		
		// read the file
		tempFile = BFile(tempFilePath, O_RDONLY);
		
		off_t fileSize;
		tempFile.GetSize(&fileSize);
		unsigned char *buffer;
		
		buffer = new unsigned char[fileSize];
		if(buffer == NULL)
			return B_ERROR;
		tempFile.ReadAt(0, buffer, fileSize);
		target->Write(buffer, fileSize);
		delete [] buffer;
		
		// delete the file
		BEntry entry = BEntry(tempFilePath);
		entry.Remove();
		
		return B_OK;
	}
	return B_NO_TRANSLATOR;
}