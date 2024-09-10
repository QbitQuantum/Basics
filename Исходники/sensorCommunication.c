void sensorcommunication_sendIntMsg(int left, int right)
{
	SENSORCOMMUNICATION_MESSAGE theMessage;
	//send message sequence byte
	theMessage.type = sensorcommunicationData.sensorIntTxMsgSeq;
	theMessage.msg = STARTBYTE;
	if(xQueueSend(sensorcommunicationData.sensorIntQueue, (void*)&(theMessage), 0) == pdTRUE)
	{
		sensorcommunicationData.sensorIntTxMsgSeq++;
	}
	//send from rover byte
	theMessage.type = sensorcommunicationData.sensorIntTxMsgSeq;
	theMessage.msg = sensorcommunicationData.sensorTxMsgSeq;	
	if(xQueueSend(sensorcommunicationData.sensorIntQueue, (void*)&(theMessage), 0) == pdTRUE)
	{
		sensorcommunicationData.sensorIntTxMsgSeq++;
	}
	//send left 1 of 4
	if(left > 9999)
		left = 9999;
	if(right > 9999)
		right = 9999;
	int leftxmit[4];
	int rightxmit[4];
	leftxmit[3] = left % 10;
	left /= 10;
	leftxmit[2] = left % 10;
	left /= 10;
	leftxmit[1] = left % 10;
	left /= 10;
	leftxmit[0] = left % 10;
	rightxmit[3] = right%10;
	right /= 10;
	rightxmit[2] = right%10;
	right /= 10;
	rightxmit[1] = right%10;
	right /= 10;
	rightxmit[0] = right%10;
	theMessage.type = sensorcommunicationData.sensorIntTxMsgSeq;
	theMessage.msg = IntToChar(leftxmit[0]);	
	if(xQueueSend(sensorcommunicationData.sensorIntQueue, (void*)&(theMessage), 0) == pdTRUE)
	{
		sensorcommunicationData.sensorIntTxMsgSeq++;
	}
	//send left 2 of 4
	theMessage.type = sensorcommunicationData.sensorIntTxMsgSeq;
	theMessage.msg = IntToChar(leftxmit[1]);
	if(xQueueSend(sensorcommunicationData.sensorIntQueue, (void*)&(theMessage), 0) == pdTRUE)
	{
		sensorcommunicationData.sensorIntTxMsgSeq++;
	}
	//send left 3 of 4
	theMessage.type = sensorcommunicationData.sensorIntTxMsgSeq;
	theMessage.msg = IntToChar(leftxmit[2]);	
	if(xQueueSend(sensorcommunicationData.sensorIntQueue, (void*)&(theMessage), 0) == pdTRUE)
	{
		sensorcommunicationData.sensorIntTxMsgSeq++;
	}
	//send 4 of 4
	theMessage.type = sensorcommunicationData.sensorIntTxMsgSeq;
	theMessage.msg = IntToChar(leftxmit[3]);	
	if(xQueueSend(sensorcommunicationData.sensorIntQueue, (void*)&(theMessage), 0) == pdTRUE)
	{
		sensorcommunicationData.sensorIntTxMsgSeq++;
	}
	//send right 1 of 4
	theMessage.type = sensorcommunicationData.sensorIntTxMsgSeq;
	theMessage.msg = IntToChar(rightxmit[0]);	
	if(xQueueSend(sensorcommunicationData.sensorIntQueue, (void*)&(theMessage), 0) == pdTRUE)
	{
		sensorcommunicationData.sensorIntTxMsgSeq++;
	}
	//send right 2 of 4
	theMessage.type = sensorcommunicationData.sensorIntTxMsgSeq;
	theMessage.msg = IntToChar(rightxmit[1]);	
	if(xQueueSend(sensorcommunicationData.sensorIntQueue, (void*)&(theMessage), 0) == pdTRUE)
	{
		sensorcommunicationData.sensorIntTxMsgSeq++;
	}
	//send right 3 of 4
	theMessage.type = sensorcommunicationData.sensorIntTxMsgSeq;
	theMessage.msg = IntToChar(rightxmit[2]);		
	if(xQueueSend(sensorcommunicationData.sensorIntQueue, (void*)&(theMessage), 0) == pdTRUE)
	{
		sensorcommunicationData.sensorIntTxMsgSeq++;
	}
	//send right 4 of 4
	theMessage.type = sensorcommunicationData.sensorIntTxMsgSeq;
	theMessage.msg = IntToChar(rightxmit[3]);		
	if(xQueueSend(sensorcommunicationData.sensorIntQueue, (void*)&(theMessage), 0) == pdTRUE)
	{
		sensorcommunicationData.sensorIntTxMsgSeq++;
	}
	sensorcommunicationData.sensorTxMsgSeq++;
	int temp = (int)sensorcommunicationData.sensorTxMsgSeq;
	if(sensorcommunicationData.sensorTxMsgSeq == 0x7F)
		sensorcommunicationData.sensorTxMsgSeq = 0x00;
	PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_3_TRANSMIT);	//ENABLE TX INTERRUPT
}