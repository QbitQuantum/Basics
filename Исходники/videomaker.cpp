/*
 * Функция videomaker_fnc() реализует поток записи видео с камеры робота в файл.
 * @ptr - указатель на структуру System.
 * Начинает запись видео, если поле videomaker объекта ptr истина
 */
void* videomaker_fnc(void *ptr)
{
	System &syst = *((System *)ptr);
	VideoMaker clip;
	Object<Mat> *curObj = NULL;
	Queue<Mat> &queue = syst.queue;
	
	if(!syst.videomaker)
	{	
		return NULL;
	}
	else
	{
		LOG("[I]: VideoMaker started.");
	}
	
	if(!clip.init(syst))
	{
		LOG("[E]: Videomaker: Can't open output stream."); //chmod or codecs problem???
		exit(EXIT_FAILURE);
	}
	
	while(1)
    {
		curObj = queue.waitForNewObject(curObj);
		
		clip.write(*(curObj->obj));
		
		curObj->free();
	}
	clip.deinit();
	return NULL;
}