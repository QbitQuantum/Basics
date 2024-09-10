/*---------------------------------------------------------------------------
**        Name : WriteAWord
**      Author : Barry Tang
**        Date : 2009/12/11
** Description : Write a char into file
**       Input : ch, the char
**      Output :
**---------------------------------------------------------------------------*/
VOID CUnicodeFile::WriteAWord(TCHAR ch)
{
	//The file can not for writing
	if (m_fileOperateFlag == FOR_READ)
	{
		return;
	}

	fputwc(ch, m_pFile);
}