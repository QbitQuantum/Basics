/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Transfer_Packet
--
-- DATE: November 25, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Ruoqi Jia
--
-- PROGRAMMER: Ruoqi Jia
--
-- INTERFACE:  Transfer_Packet(LPVOID packet)
--					-LPVOID packet : the packet to be sent
--
-- RETURNS: 0 upon successful thread finish
--
-- NOTES:
--		Represents the sending state of the wireless protocol design.  This thread is called whenever a user chooses a
--  file to send and presses the Send button.  We confirm the line to make sure the line is available.  If confirm line
--  times out, we bring the protocol back to the Wait state to wait for an ENQ, and re-initialize the read thread.  If
--  confirm line succeeds, we send our packet using SendPacket.  When SendPacket succeeds or times out, we do a check
--  on the priority states of the sender and receiver.  If we don't have priority and the sender has priority, we enter
--  the wait state again to wait for an ENQ, otherwise we will just go directly to the read idle state.  Finally, we
--  reinitialize the read thread and return from this write thread.
----------------------------------------------------------------------------------------------------------------------*/
DWORD WINAPI Transfer_Packet(LPVOID packet)
{
	ResetEvent(Ev_Read_Thread_Finish);
	SetCommMask(hComm, RETURN_COMM_EVENT);
	WaitForSingleObject(hWrite_Lock, 2000);
	char* s = (char*)packet;
	OutputDebugString("Starting confirm line loop\n");
	if (!ConfirmLine()) 
	{
		OutputDebugString("exceeded confirm line max tries\n");

		//WAIT STATE: wait for an enq, for a specified amount of time. If we get one, set
		//the receivedENQinWait boolean flag to skip directly to acknowledging line in read thread
		receivedENQinWait = WaitForEnq();
		ReleaseMutex(hWrite_Lock);
		Initialize_Read();
		SetEvent(Ev_Send_Thread_Finish);
		delete[]s;
		return 0;
	}
	OutputDebugString("Sending packet\n");
	SendPacket(s);

	//Check Priorities
	//only when we want priority and sender doesn't want priority, we go directly to read idle. every other priority combo,
	//we go to wait state
	if ((!weHavePriority && senderHasPriority) || (weHavePriority && senderHasPriority) || (!weHavePriority && !senderHasPriority))
	{
		//WAIT STATE: wait for an enq, for a specified amount of time. If we get one, set
		//the receivedENQinWait boolean flag to skip directly to acknowledging line in read thread
		OutputDebugString("Going to wait state\n");
		receivedENQinWait = WaitForEnq();
	}else 
		SetEvent(Ev_Send_Thread_Finish);
	//going back to wait/idle state
	ReleaseMutex(hWrite_Lock);
	Initialize_Read();
	delete[]s;
	return 0;
}