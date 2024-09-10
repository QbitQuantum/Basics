void CContainers::writeMemBuffers(int preprocFlag, int PPMDlib_order, int comprLevel, Encoder* PAQ_encoder, unsigned char* zlibBuffer,COutFileStream* outStream)
{
	std::map<std::string,CMemoryBuffer*>::iterator it;

	int fileLen=0;
	int len=0;
	int lenCompr=0;
	int allocated=0;

#ifdef USE_LZMA_LIBRARY
	if (IF_OPTION(OPTION_LZMA))
	{
		Byte **Data;
		size_t* Size;
		int count;
		
		count=(int)memmap.size();
		Size=new size_t[count];
		Data=(unsigned char**) malloc(sizeof(unsigned char*)*count);
		if (Data==NULL)
			OUT_OF_MEMORY();
	
		int i=0;
		for (it=memmap.begin(); it!=memmap.end(); it++)
		{
			CMemoryBuffer* b=it->second;
			fileLen=b->Size();
			
			if (fileLen>0)
			{
				Size[i]=fileLen;
				Data[i]=b->TargetBuf;
				i++;
				
				PUTC((int)it->first.size());
				for (int i=0; i<(int)it->first.size(); i++)
					PUTC(it->first[i]);
				
				PUTC(fileLen>>24);
				PUTC(fileLen>>16);
				PUTC(fileLen>>8);
				PUTC(fileLen);	
			}
		}
		
		PUTC(0);
		
		count=i;
		int last=LZMAlib_GetOutputFilePos(outStream);
		LZMAlib_EncodeSolidMemToFile(Data,Size,count,outStream);
		printStatus(0,LZMAlib_GetOutputFilePos(outStream)-last,true);
	}