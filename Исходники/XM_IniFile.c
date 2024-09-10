/**
	读入文件
	@param filename 被读入的文件名
*/
bool Open(char *filename) {
    int nSrcLen = strlen(filename);
    if ( MAX_PATH <= nSrcLen)
        strcpy_s(g_FileName, nSrcLen, filename);
    else
        return false;//输入过长

	Clear();//先清理了

    g_DataLen = GetFileLength(g_FileName);
    //有内容存在
    if( g_DataLen > 0 )	{
        g_pData = _MALLOC(char,g_DataLen + 1);//多个"\0"
        FILE *fp = fopen(g_FileName, "rb");
        fread(g_pData, g_DataLen, 1, fp);		//读数据
        fclose(fp);
		g_FileType= GetFileType();//判断文件类型是dos还是unix
    } else {