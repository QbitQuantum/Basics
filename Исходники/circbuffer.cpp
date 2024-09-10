int tCircularBuffer::insertData(char *data, int count)
{
  long i = 0;
  long pos = 0;
  tBufReader *P;

  WaitForSingleObject(hSemafor,1000);
  ResetEvent(hSemafor);
  while (count>0)
  {
	i=(bufferEnd+count<bufferSize ? count : bufferSize-bufferEnd);
	CopyMemory((void*)&buffer[bufferEnd], (void*)&data[pos], i);   nowInBuffer=nowInBuffer+i;
	P=FirstReader;
	while (P!=NULL)
	{
	  P->nowInBuffer=P->nowInBuffer+i;
	  if (P->in_event_id!=0)  PulseEvent(P->in_event_id);
	  P=P->nextreader;
	}
	pos=pos+i;
	count=count-i;
	bufferEnd=bufferEnd+i;
	if (bufferEnd>=bufferSize) bufferEnd=0;
  }
  SetEvent(hSemafor);
  if (in_event_id!=0)  PulseEvent(in_event_id);
  return 0;
}