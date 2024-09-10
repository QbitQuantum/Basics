//idExtName为扩展名ID
//pFilePath为带斜线目录名
//filePathLen为带斜线目录名长度
//pFileName文件名
//fileLen文件名长度
int CExtArray::SetIconIndex(int idExtName,PWCHAR pFilePath,int filePathLen,PWCHAR pFileName,int fileLen)
{
    assert(idExtName>=s_dwOmitExt && "已经初始化实时调用的不能再传递进来");

    SHFILEINFOW sfi;

    //现将filePath扩展为文件名
    int j=filePathLen;
    for(int i=0;i<fileLen;++i)
    {
        pFilePath[j++]=pFileName[i];
    }
    pFilePath[j]=L'\0';

    SHGetFileInfoW(pFilePath,  
        FILE_ATTRIBUTE_NORMAL,  
        &sfi,  
        sizeof(sfi),  
        SHGFI_SMALLICON
        | SHGFI_SYSICONINDEX 
        | SHGFI_USEFILEATTRIBUTES
        ) ;
    pFilePath[filePathLen]=L'\0';//还原filePath
    m_piIcon[idExtName]=sfi.iIcon;
    return sfi.iIcon;
}