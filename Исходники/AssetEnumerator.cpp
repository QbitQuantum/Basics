const char* AssetEnumerator::GetSubdirectoryName(int index)
	{
	if (directory_)
		{
		const char* dirname=directory_->GetSubdirectory(index);
		int size=StrLen(directory_->GetPath())+StrLen(dirname)+2;
		if (!nameBuffer_ || nameBufferSize_<size)
			{
			if (nameBuffer_)
				{
				delete nameBuffer_;
				}
			nameBufferSize_=size;
			nameBuffer_=new char[nameBufferSize_];
			}
		SNPrintF(nameBuffer_,nameBufferSize_,"%s/%s",directory_->GetPath(), dirname);
		return nameBuffer_;
		}


	if (archiveDirectory_)
		{
		return archiveDirectory_->GetSubdirectory(index).GetString();
		}

	return 0;
	}