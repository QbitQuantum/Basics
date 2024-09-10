int lineCount(CString fileName)
{
	CStdioFile openfile(fileName,CFile::modeRead);				//构造CStdioFile对象
	CString str;
	int count=0;
	while(openfile.ReadString(str))							//读一行数据
	{

			count++;
	}
	return count;
}