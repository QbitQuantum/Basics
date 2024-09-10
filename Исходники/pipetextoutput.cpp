int PipeTextOutput::SendFrame(TextFrame& frame)
{
	//Bloqueamos
	pthread_mutex_lock(&mutex);

	//Get string
	DWORD len = frame.GetWLength();

	//Si no cabe
	if(fifoBuffer.length()+len>1024)
		//Limpiamos
		fifoBuffer.clear();

	//Metemos en la fifo
	fifoBuffer.push(frame.GetWChar(),len);

	//Desbloqueamos
	pthread_mutex_unlock(&mutex);

	return len;
}