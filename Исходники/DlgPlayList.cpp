/*
	Поток для загрузки музыки в плейлист
*/
DWORD WINAPI Thread(LPVOID lp)
{
	HDROP hDrop = (HDROP)lp;
	CHAR szFileName[MAX_PATH];
	TCHAR buff[MAX_PATH];
	DWORD dwCount = DragQueryFileA(hDrop, 0xFFFFFFFF, szFileName, MAX_PATH);		//Определение количества загружаемых песен
	for (INT i = 0; i < dwCount; i++)
	{
		DragQueryFileA(hDrop, i, szFileName, MAX_PATH);			//Определение пути к файлу
		INT len = strlen(szFileName);
		CHAR buffFormat[4];									//Формат песни
		INT j = 0;											//для прохода по буферу формата песни
		for (INT i = len - 4; i < len; i++)
		{
			buffFormat[j] = szFileName[i];
			j++;
		}
		if (me_strcmp(".mp3", buffFormat))
		{
			HSTREAM stream = BASS_StreamCreateFile(0, szFileName, 0, 0, 0);			//Создание потока 
			mbstowcs(buff, szFileName, MAX_PATH);							//преобразование CHAR to TCHAR
			DlgPlayList::_this->addSongToPlayList(stream, buff);			//Добавление песни в плейлист
		}
	}
	DragFinish(hDrop);
	return FALSE;
}