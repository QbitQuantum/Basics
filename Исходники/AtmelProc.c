void InitAtmelControlProc()
{
	//bind to this process' message queue
	Bind(ATMELMQNUM);

	//wait for synchronization message from keyboardProc to begin
	char dummyBlock[1];
	int syncSrc = KBMQNUM;
	Recv(&syncSrc, ATMELMQNUM, dummyBlock, 1);

	//local variables for message passing
	int src = -1;
	char recvBuffer[RECV_BUFFER_SIZE];
	char sendHallSensorBuffer[SEND_HS_BUFFER_SIZE];

	//initialize cursor position for hall sensor display output
	//UpdateCursorPos(&(GetRunning()->cursorPosState), 23, 2);
	int currentCursorRow = HS_CURSOR_UPPER_LIMIT;
	UpdateCursorPos(&(GetRunning()->cursorPosState), currentCursorRow, 2);


	bool initialized = false; //set to true once track hardware has been initialized

	while(true) //the main loop of the Atmel Communication Process
	{
		src = -1; //-1 means "accept messages from any source"

		//clean the receive buffer
		int j;
		for(j = 0; j < 6; j++)
		{
			recvBuffer[j] = 0;
		}

		//blocking recieve waiting for messages
		Recv(&src, ATMELMQNUM, recvBuffer, -1);//because the src is unknown, size is determined by the sender

		switch(src) //two sources are supported: HS Process and Loco process.
		{
			case HSMQNUM:
			{
				switch(recvBuffer[0])
				{
					case 0:	//reset sensors and set switches
					{
						//init HS queues of atmel 1
						SendPacket *out_packet = InitHallSensorQueueInit();
						RecvPacket *in_packet = (RecvPacket*)Allocate(sizeof(RecvPacket));
						SendAndReceivePacket(out_packet, in_packet, 1);

						//init HS queues of atmel 3
						SendPacket *out_packet2 = InitHallSensorQueueInit();
						RecvPacket *in_packet2 = (RecvPacket*)Allocate(sizeof(RecvPacket));
						SendAndReceivePacket(out_packet2, in_packet2, 3);

						if(GetRecvSuccess(in_packet) && GetRecvSuccess(in_packet2))
						{
							//reset all HS (atmel 1 only)
							SendPacket *out_packet3 = InitHallSensorAllReset();
							RecvPacket *in_packet3 = (RecvPacket*)Allocate(sizeof(RecvPacket));

							SendAndReceivePacket(out_packet3, in_packet3, 1);

							Deallocate((uint32_t)out_packet);
							Deallocate((uint32_t)in_packet);
							Deallocate((uint32_t)out_packet2);
							Deallocate((uint32_t)in_packet2);
							Deallocate((uint32_t)out_packet3);
							Deallocate((uint32_t)in_packet3);

							initialized = true;

							//send back to HS to acknowledge that HS queues were initialized
							Send(ATMELMQNUM, HSMQNUM, recvBuffer, sizeof(char));
						}
						else
						{
							char *failure = "FATAL ERROR initalizing HS queues\n\r\0";
							WriteString(failure);
						}
						break;
					}
					default://1 or 3
					{
						if(initialized) //do not act on other messages if we haven't initialized the queues yet
						{
							//query which hall sensor was triggered
							SendPacket *out_packet = InitHallSensorInput();
							RecvPacket *in_packet = (RecvPacket*)Allocate(sizeof(RecvPacket));

							SendAndReceivePacket(out_packet, in_packet, (int)recvBuffer[0]);

							//examine the rx'd packet to determine the hall sensor number
							int sensorNum = -1;
							bool successfulSPI = GetHallSensorNum(in_packet, &sensorNum);

							Deallocate((uint32_t)out_packet);
							Deallocate((uint32_t)in_packet);

							//send which hall sensor triggered to LocoProc
							if(successfulSPI)
							{
								//output the HS number to the console
								char testHSNum[4];
								testHSNum[0] = sensorNum/10 + 0x30;
								testHSNum[1] = sensorNum%10 + 0x30;
								testHSNum[2] = ' ';
								testHSNum[3] = '\0';

								UpdateCursorPos(&(GetRunning()->cursorPosState), currentCursorRow, 2);
								OutputCursorPositionSequence(&(GetRunning()->cursorPosState));
								WriteStringChar('+');
								WriteString(testHSNum);

								//make sure the stream of hall sensor printouts stays on the screen.
								currentCursorRow = (currentCursorRow == HS_CURSOR_LOWER_LIMIT)? HS_CURSOR_UPPER_LIMIT: currentCursorRow +1;

								//send reset acknowledgement to Atmel 1 for hall sensor triggering
								SendPacket *out_packet2 = InitHallSensorSingleReset(sensorNum);
								RecvPacket *in_packet2 = (RecvPacket*)Allocate(sizeof(RecvPacket));

								SendAndReceivePacket(out_packet2, in_packet2, 1);

								if(GetRecvSuccess(in_packet2))
								{
									Deallocate((uint32_t)out_packet2);
									Deallocate((uint32_t)in_packet2);
								}
								else
								{
									char *failure = "FATAL ERROR when acknowledging Hall Sensor event\n\r\0";
									WriteString(failure);
								}

								if(lastSensorTriggered != sensorNum) //Some hall sensors will double-trigger intermittently as a train passes, so ignore successive duplicates
								{
									sendHallSensorBuffer[0] = (char)sensorNum;
									//tell the LocoProc which hall sensor was just hit
									Send(ATMELMQNUM, LOCOMQNUM, sendHallSensorBuffer, SEND_HS_BUFFER_SIZE);
								}

								lastSensorTriggered = sensorNum;
							}
							else
							{
								char *failure = "FATAL ERROR when getting hall sensor number\n\r\0";
								WriteString(failure);
							}
						}
						break;
					}
				}
				break;
			}
			case LOCOMQNUM:
			{
				switch(recvBuffer[0])
				{
					case SPI_SEGMENT_SPEED_DIR://set segment speed and dir
					{
						SendPacket *out_packet = InitDirAndMagFor1Section(recvBuffer[1], recvBuffer[2], recvBuffer[3]);
						RecvPacket *in_packet = (RecvPacket*)Allocate(sizeof(RecvPacket));
						SendAndReceivePacket(out_packet, in_packet, 1);

						if(GetRecvSuccess(in_packet))
						{
							Deallocate((uint32_t)out_packet);
							Deallocate((uint32_t)in_packet);
						}
						else
						{
							char *failure = "FATAL ERROR when setting single segment speed\n\r\0";
							WriteString(failure);
						}

						break;
					}
					case SPI_SWITCH://set switch as thrown or straight
					{
						SendPacket *out_packet = InitSwitchControl(recvBuffer[1], recvBuffer[2]);
						RecvPacket *in_packet = (RecvPacket*)Allocate(sizeof(RecvPacket));
						SendAndReceivePacket(out_packet, in_packet, 2);

						if(GetRecvSuccess(in_packet))
						{
							Deallocate((uint32_t)out_packet);
							Deallocate((uint32_t)in_packet);
						}
						else
						{
							char *failure = "FATAL ERROR when using switch command\n\r\0";
							WriteString(failure);
						}
						break;
					}
					case SPI_ALL_SEGMENTS_SPEED_DIR: //and init the switches
					{
						SendPacket *out_packet = InitDirAndMagForAllSections(0, 1);//1 means CCW
						RecvPacket *in_packet = (RecvPacket*)Allocate(sizeof(RecvPacket));
						SendAndReceivePacket(out_packet, in_packet, 1);

						if(GetRecvSuccess(in_packet))
						{
							//straighten all switches
							int i;
							SendPacket *out_packet2 = InitSwitchControl(-1, 1);//1 means straight
							RecvPacket *in_packet2 = (RecvPacket*)Allocate(sizeof(RecvPacket));

							for(i = 1; i <= 9; i++)
							{
								out_packet2->arg1 = i;
								SendAndReceivePacket(out_packet2, in_packet2, 2);
							}

							Deallocate((uint32_t)out_packet);
							Deallocate((uint32_t)in_packet);
							Deallocate((uint32_t)out_packet2);
							Deallocate((uint32_t)in_packet2);

							//acknowledge to loco proc that track is initialized
							Send(ATMELMQNUM, LOCOMQNUM, recvBuffer, sizeof(char));
						}
						else
						{
							char *failure = "FATAL ERROR when setting all segments speed\n\r\0";
							WriteString(failure);
						}
						break;
					}
				}
				break;
			}
		}
	}
}