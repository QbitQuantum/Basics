void mDisk::readSector(char* data, long long startingSector, int nBytes, int& numberOfBytesRead)
{
	numberOfBytesRead = 0;
	int nBytesLeft = nBytes;
	//pointer to the starting position of data field
	char* pointer = data;
	int numberOfBytesToRead;

	while (nBytesLeft > 0)
	{
		if (startingSector > this->ending || startingSector < this->starting)
		{
			LARGE_INTEGER offset;
			offset.QuadPart = startingSector;
			offset.QuadPart *= 512;
			SetFilePointerEx(this->vol, offset, 0, FILE_BEGIN);

			DWORD nOfRead;
			ReadFile(this->vol, this->disk, (DWORD)MAXSECTOR*512, &nOfRead, 0);

			this->starting = startingSector;
			this->ending = this->starting + (nOfRead / 512 + int(nOfRead % 512 > 0)) - 1;
		}

		if (this->ending < startingSector)
			return;
		//point to the position of startingSector between this->starting and this->ending
		char* startingPointer = this->disk + (startingSector - this->starting) * 512;
		int numberOfBytesToCopy = min((this->ending - startingSector + 1) * 512, nBytesLeft);
		memcpy(pointer, startingPointer, numberOfBytesToCopy);
		
		numberOfBytesRead += numberOfBytesToCopy;
		nBytesLeft -= numberOfBytesToCopy;
		//shift the pointer to the next position of data field to copy
		pointer += numberOfBytesToCopy;
		//shift the starting sector to the next position in disk
		startingSector += numberOfBytesToCopy / 512 + int(numberOfBytesToCopy % 512 > 0);
	}
	
}