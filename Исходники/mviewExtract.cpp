int _tmain(int argc, _TCHAR* argv[])
{
  char *path = NULL, *pathDir = NULL;
  FILE *fpMview = NULL;
  FILE *fpDst = NULL;

  DWORD flag, sizeData, sizeDataDecompressed;

  if(argc<2)goto err;
  fpMview = _wfopen(argv[1], L"rb");
  if(fpMview==NULL)goto err;

  path = (char *)malloc(4096);
  if(path==NULL)goto err;
  pathDir = (char *)malloc(4096);
  if(pathDir==NULL)goto err;

  buf = (BYTE *)malloc(bufSize);
  if(buf==NULL)goto err;

  while(1)
  {
    flag=0;
    sizeData=0;
    sizeDataDecompressed=0;

    int numPath = freadNullStr(fpMview, path, 4096);
    if(numPath==0)goto err;

    SanitizePath(path);

    freadNullStr(fpMview, NULL, 0);
    if(fread(&flag, 1, 4, fpMview)!=4)goto err;
    if(fread(&sizeData, 1, 4, fpMview)!=4)goto err;
    if(fread(&sizeDataDecompressed, 1, 4, fpMview)!=4)goto err;
    
    if(flag & 0x1)printf("\"%s\"  flag=%u (compressed!), size=%u, decompressedSize=%u\n", path, flag, sizeData, sizeDataDecompressed);
    else          printf("\"%s\"  flag=%u, size=%u\n", path, flag, sizeData);

    if(PathCombineA(path, "out\\", path)==NULL)goto err;
    strcpy_s(pathDir, 4096, path);

    PathRemoveFileSpecA(pathDir);
    PathAddBackslashA(pathDir);
    BOOL bRet = MakeSureDirectoryPathExists(pathDir);

    fpDst = fopen(path, "wb");
    if(fpDst==NULL)goto err;

    if(!FILEtoFILE(fpDst, fpMview, sizeData))goto err;

    fclose(fpDst);
  }
  
  if(buf)free(buf);
  if(path)free(path);
  if(pathDir)free(pathDir);
  if(fpMview)fclose(fpMview);
  if(fpDst)fclose(fpDst);
	return 0;

err:
  if(buf)free(buf);
  if(path)free(path);
  if(pathDir)free(pathDir);
  if(fpMview)fclose(fpMview);
  if(fpDst)fclose(fpDst);
  return 0;
}