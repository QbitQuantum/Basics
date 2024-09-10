BOOL initFS(char* OsFileName, int SizeInBlocks)
{
//	HANDLE hFile;

    fileSystemSizeInBlocks = SizeInBlocks;

    diskInBlocksSize = fileSystemSizeInBlocks * BLOCK_SIZE;

    createVirtualDisk(OsFileName, diskInBlocksSize);
    //openMapView(OsFileName, sizeInBlocks,hFile);
    CreateMyBitmap();
    CreateFolder();
    CreateOpenFiles();

    return 0;

}