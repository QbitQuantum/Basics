//***************************************************************************************
DRFile* DRFileManager::startWriting(const char* pcPfadName, const char* pcFilename, const char* pcTyp, unsigned long ulBlockLength)
{
	if(!m_bInitialized) return NULL;
	//Zero Pointer Check
	if(!pcPfadName) return NULL;
	if(!pcFilename) return NULL;
	if(!pcTyp) return NULL;

    DRFile* pTempFile = NULL;
    pTempFile = getFileByName(pcTyp, pcFilename);
    if(!pTempFile)
    {
        pTempFile = new DRFile(pcPfadName, "r+b");
        if(!pTempFile->isOpen() || !isFileOK(pTempFile))
        {
            LOG_WARNING("Neue Datei muss erstellt werden!");
            if(newFile(pcPfadName)) return NULL;

            pTempFile->open(pcPfadName, false, "r+b");
            if(!pTempFile->isOpen()) return NULL;
        }
        
        if(!isFileOK(pTempFile)) return NULL;
        pTempFile->setFilePointer(pTempFile->getSize()-8, SEEK_SET);

        unsigned short u16HeaderLength = 2*sizeof(long) + sizeof(int) + sizeof(short) + strlen(pcFilename);
        DHASH ID = DRMakeDoubleHash(pcTyp, pcFilename);

        //BlockHeader schreiben
        pTempFile->write(&u16HeaderLength, sizeof(unsigned short), 1);
        pTempFile->write(&ulBlockLength, sizeof(unsigned long), 1);
        pTempFile->write(&ID, sizeof(DHASH), 1);
        //pstrFilename->Save(pTempFile);
        int istrLength = strlen(pcFilename);
        pTempFile->write(&istrLength, sizeof(int), 1);
        pTempFile->write(pcFilename, sizeof(char), istrLength);

        unsigned long ulCurrentPointerPos = pTempFile->getFilePointer();

        //Hauptheader aktualisieren
        //Dateigröße
        pTempFile->setFilePointer(8, SEEK_SET);
        unsigned long ulDateiGesLength;
        pTempFile->read(&ulDateiGesLength, sizeof(unsigned long), 1);
        ulDateiGesLength += u16HeaderLength + ulBlockLength;
        pTempFile->setFilePointer(8, SEEK_SET);
        pTempFile->write(&ulDateiGesLength, sizeof(unsigned long), 1);

        //NumBlöcke
        pTempFile->setFilePointer(8 + sizeof(long) + sizeof(DRReal), SEEK_SET);
        unsigned long ulNumBloecke;
        pTempFile->read(&ulNumBloecke, sizeof(unsigned long), 1);
        ulNumBloecke++;
        pTempFile->setFilePointer(8 + sizeof(long) + sizeof(DRReal), SEEK_SET);
        pTempFile->write(&ulNumBloecke, sizeof(unsigned long), 1);

        pTempFile->setFilePointer(ulCurrentPointerPos, SEEK_SET);
    }
	//prüfe ob neue dateigröße der alten entspricht
	else
	{
		u32 filePointer = pTempFile->getFilePointer();
		int iStrLen = strlen(pcFilename);
		//filePointer -= iStrLen*sizeof(char) + sizeof(int) + sizeof(DHASH) + sizeof(u32);
		u32 blockLength = 0;
		pTempFile->setFilePointer(-(iStrLen*sizeof(char) + sizeof(int) + sizeof(DHASH) + sizeof(u32)), SEEK_CUR);
		u32 now = pTempFile->getFilePointer();
		pTempFile->read(&blockLength, sizeof(unsigned long), 1);
		pTempFile->setFilePointer(filePointer, SEEK_SET);
		if(ulBlockLength > blockLength)
		{
			closeFile(pTempFile);
			LOG_ERROR("neuer Dateieintrag ist zu gross!", NULL);
		}
	}

	return pTempFile;

}