CSFAPI int CSFile_load(CSFile** outcsf, const char* filename, CSFileMemoryPTR mem)
{
  FILE* file;
  if (fopen_s(&file,filename,"rb")){
    *outcsf = 0;
    return CADSCENEFILE_ERROR_NOFILE;
  }

  CSFile header;
  size_t sizeshould = 0;
  if (!fread_s(&header,sizeof(header),sizeof(header),1,file) ||
      !(sizeshould=CSFile_getRawSize(&header)))
  {
    fclose(file);
    *outcsf = 0;
    return CADSCENEFILE_ERROR_VERSION;
  }
  
  // load the full file to memory
  xfseek(file, 0, SEEK_END);
  size_t size = (size_t)xftell(file);
  xfseek(file, 0, SEEK_SET);

  if (sizeshould != size){
    fclose(file);
    *outcsf = 0;
    return CADSCENEFILE_ERROR_VERSION;
  }
  
  char* data  = (char*)mem->alloc(size);
  fread_s(data,size,size,1,file);
  fclose(file);

  return CSFile_loadRaw(outcsf,size,data);
}