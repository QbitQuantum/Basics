char loadWaveData(WAVDATA* p_wav, char* fileName, char memLoad)  // WAVE加载, memLoad-是否加载至内存
{

	JFileSystem* fileSystem = JFileSystem::GetInstance();
	if (!fileSystem->OpenFile(fileName)) 
		return 0;
		
	memset(p_wav, 0, sizeof(WAVDATA));
	//SceUID fd = sceIoOpen(fileName, PSP_O_RDONLY, 0777);
	char head[256];
	memset(head, 0, 256);
	//sceIoRead(fd, head, 20);
	fileSystem->ReadFile(head, 20);
	char string[8];
	memset(string, 0, 8);
	memcpy(string, head, 4);
	if (0!=strcmp(string, "RIFF"))
	{
		//sceIoClose(fd);
		fileSystem->CloseFile();
		return 0;
	}
	memset(string, 0, 8);
	memcpy(string, head+8, 4);
	if (0!=strcmp(string, "WAVE"))
	{
		//sceIoClose(fd);
		fileSystem->CloseFile();
		return 0;
	}
	memset(string, 0, 8);
	memcpy(string, head+12, 3);
	if (0!=strcmp(string, "fmt"))
	{
		//sceIoClose(fd);
		fileSystem->CloseFile();
		return 0;
	}
	int fmtSize = 0;
	memcpy(&fmtSize, head+16, 4);
	//sceIoRead(fd, head+20, fmtSize);
	fileSystem->ReadFile(head+20,fmtSize );
	p_wav->headSize = 20+fmtSize;
	while (1)
	{
		//sceIoRead(fd, head+p_wav->headSize, 4);
		fileSystem->ReadFile(head+p_wav->headSize, 4);
		memset(string, 0, 8);
		memcpy(string, head+p_wav->headSize, 4);
		p_wav->headSize += 4;
		if (0!=strcmp(string, "data"))
		{
			//sceIoRead(fd, head+p_wav->headSize, 4);
			fileSystem->ReadFile(head+p_wav->headSize, 4);
			memcpy(&fmtSize, head+p_wav->headSize, 4);
			p_wav->headSize += 4;
			//sceIoRead(fd, head+p_wav->headSize, fmtSize);
			fileSystem->ReadFile(head+p_wav->headSize, fmtSize);
			p_wav->headSize += fmtSize;
		}
		else
		{
			//sceIoRead(fd, head+p_wav->headSize, 4);
			fileSystem->ReadFile(head+p_wav->headSize, 4);
			p_wav->headSize += 4;
			break;
		}
		if (p_wav->headSize>191)
		{
			//sceIoClose(fd);
			fileSystem->CloseFile();
			return 0;
		}
	}
	strcpy(p_wav->fullName, fileName);
	memcpy(&p_wav->fileSize, head+4, 4);
	memcpy(&p_wav->format, head+20, 2);
	memcpy(&p_wav->channelCount, head+22, 2);
	if (p_wav->channelCount!=1 && p_wav->channelCount!=2)
	{
		//sceIoClose(fd);
		fileSystem->CloseFile();
		return 0;
	}
	memcpy(&p_wav->samplePerSecond, head+24, 4);
	memcpy(&p_wav->bytePerSecond, head+28, 4);
	memcpy(&p_wav->bytePerSample, head+32, 2);
	p_wav->bytePerSample = p_wav->bytePerSample / p_wav->channelCount;
	if (p_wav->bytePerSample!=1 && p_wav->bytePerSample!=2)
	{
		//sceIoClose(fd);
		fileSystem->CloseFile();
		return 0;
	}
	p_wav->nSample = 44100 / p_wav->samplePerSecond;
	p_wav->sizeStep = 4096 / p_wav->nSample * p_wav->channelCount / 2 * p_wav->bytePerSample / 2;
	memcpy(&p_wav->soundSize, head+p_wav->headSize-4, 4);
	if (memLoad)
	{
		if (p_wav->soundSize>4096000)
		{
			//sceIoClose(fd);
			fileSystem->CloseFile();
			return 0;
		}
		p_wav->buffer = (char*)malloc(p_wav->soundSize);
		memset(p_wav->buffer, 0, p_wav->soundSize);
		//sceIoRead(fd, p_wav->buffer, p_wav->soundSize);
		fileSystem->ReadFile(p_wav->buffer, p_wav->soundSize);
		p_wav->bytePosition = 0;
		p_wav->fd = -1;
		//sceIoClose(fd);
		fileSystem->CloseFile();
	}
	else
	{
		p_wav->bytePosition = p_wav->headSize;
		//p_wav->fd = fd;	// no file mode...
		p_wav->fd = -1;
	}
	return 1;
}