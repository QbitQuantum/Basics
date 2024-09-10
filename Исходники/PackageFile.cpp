void PackageFile::Save(std::string savePath)
{
    OutputFileName = savePath;

    FileReader rdr;

    int headerSize = HEADER_SIZE; // Header Size
    int directorySize = 0; // Directory size
    int bufPos = 0; // Data section size

    auto it = filesList->GetContainer()->begin();

    while (it != filesList->GetContainer()->end())
    {
        FileListEntry* fileListing = *it;

        std::string fileName;

        if (fileListing->RelativeDirectoryParentRoot == "")
        {
            fileName = fileListing->File->FileName;
        }
        else
        {
            fileName = StringSubtract(fileListing->File->FilePath, fileListing->RelativeDirectoryParentRoot);
        }        

        rdr.OpenFile(fileListing->File->FilePath.c_str());

        if (contents != NULL)
            delete(contents);

        contents = rdr.GetFileContents();

        DirectoryEntry* newFileEntry = new DirectoryEntry();

        strcpy(newFileEntry->fileName, const_cast<char*>(fileName.c_str()));
        newFileEntry->fileLength = contents->fileSize;
        newFileEntry->filePosition = bufPos;

        newFileEntry->fileContents = new char[contents->fileSize];
        memcpy(newFileEntry->fileContents, contents->buffer, contents->fileSize);

        bufPos += contents->fileSize;

        directorySize += sizeof(newFileEntry->fileName) + sizeof(newFileEntry->fileLength) + sizeof(newFileEntry->filePosition);

        entries->Add(newFileEntry);

        rdr.Close();

        it++;
    }

    int fileSize = headerSize + bufPos + directorySize;

    Header *packHeader = new Header();
    strncpy(packHeader->sig, "PACK", 4);
    packHeader->dirOffset = headerSize;
    packHeader->dirLength = directorySize;

    WriteBytes(packHeader->sig, 4, memStream);
    WriteBytes((char*)&packHeader->dirOffset, 4, memStream);
    WriteBytes((char*)&packHeader->dirLength, 4, memStream);

    packageHeader = packHeader;

    auto it2 = entries->GetContainer()->begin();

    int currentDirectoryOffset = 0;
    int currentDataSize = 0;

    while (it2 != entries->GetContainer()->end())
    {
        DirectoryEntry* entry = *it2;

        WriteBytes(entry->fileName, sizeof(entry->fileName), memStream);
        int currPos = headerSize + directorySize + currentDataSize;

		char* filePosCopy = new char[4];
		memcpy(filePosCopy, (char*)&entry->filePosition, 4);
        WriteBytes(filePosCopy, sizeof(filePosCopy), memStream);

        char* fileLengthCopy = new char[4];
        memcpy(fileLengthCopy, (char*)&entry->fileLength, 4);
        WriteBytes(fileLengthCopy, sizeof(fileLengthCopy), memStream);

        currentDataSize += entry->fileLength;
        it2++;
    }

    auto it3 = entries->GetContainer()->begin();

    while (it3 != entries->GetContainer()->end())
    {
        DirectoryEntry* entry = *it3;

        WriteBytes(entry->fileContents, entry->fileLength, memStream);

        it3++;
    }

    int streamSize = memStream->tellg();
    
    memStream->seekg(0); // Reset the cursor

    auto test = ((std::stringstream*)memStream)->str();

    std::fstream packageStream = std::fstream(OutputFileName, std::ios::out | std::ios::binary);

    packageStream << memStream->rdbuf();
    
    packageStream.close();
}