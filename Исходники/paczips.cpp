//================================================================================
//ファイルデータを取得します。ただしoutDataはメモリが確保されてなくてはなりません
//================================================================================
HRESULT CompressData::GetFileData(char *fileName,char *outData)
{	
	FileInfo *fi;
	if(GetFileInfo(fileName,&fi) == E_FAIL)
	{
		assert(!"ファイルがないですよ");
		return E_FAIL;
	}
	

	FILE *fp = fopen(m_fileName,"rb");
	fseek(fp,fi->startAdress,SEEK_SET);
	Decompress(fp,outData,fi->size);

	fclose(fp);
	
	return S_OK;
}