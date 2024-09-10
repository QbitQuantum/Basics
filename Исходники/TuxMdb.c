int Logger(LISTE *plcs)
{
	int res=0,Comm_err=0,Read_Something=0;
	if (TEST)
	{
		ListePlc(plcs);
		//return(0);
	}
	int now=time(NULL);
	res=BuildSockets(plcs);
	while (!Terminated)
	{
		ELEMENT *elt=GetFirst(plcs);
		while (elt!=NULL)  // PLCs
		{
			PLC *plc=elt->Data;
			/* Something to do ? */
			if (plc->Next_Time>time(NULL))
			{
				elt=GetNext(plcs,elt);			
				continue;
			}
			/* Test Socket */
			if (plc->socket<0)
			{
				if (BuildSocket(plc)<0)
				{
					Log(LOG_WARNING,"Socket unavailable for : %s\n",plc->PlcName);
					plc->Next_Time=now+WAIT_FOR_RECONNECT;
					elt=GetNext(plcs,elt);
					continue;
				} else Log(LOG_INFO,"Socket build for : %s\n",plc->PlcName);
			}
			now=time(NULL);
			Read_Something=0;
			Comm_err=1;
			//plc->Next_Time=now+0.95*MAX_SAMPLE/1000;
			plc->Next_Time=now+MAX_SAMPLE;
			Log(LOG_DEBUG,"Set plc->Next_Time in %d seconds (MAX_SAMPLE : %d)\n",plc->Next_Time-now,MAX_SAMPLE);
			/* Read Tags */
			ELEMENT *elt2=GetFirst(&(plc->Tags));
			while (elt2!=NULL)
			{
				TAG *tag=elt2->Data;
				if ((now-tag->Time_Value)>(1.5*tag->Time_Sample))
					Log(LOG_WARNING,"Time Sample exceed on tag : %s (%s)\n",tag->TagName,plc->PlcName);
				if ((now-tag->Time_Value)>=tag->Time_Sample)
				{
					//Log(LOG_DEBUG,"Reading tag : %s (%s) (%d - %d > %d)\n",tag->TagName,plc->PlcName,now,tag->Time_Value,tag->Time_Sample);
					Read_Something=1;
					res=ReadTag(plc,tag);
					if (res==0) Comm_err=0; // At least one tag is Ok
					if (mb_errno==EPIPE) CloseSocket(plc->socket,plcs);
				}
				if ((tag->Time_Value+tag->Time_Sample)<(plc->Next_Time))
				{
					plc->Next_Time=tag->Time_Value+tag->Time_Sample;
					Log(LOG_DEBUG,"plc->Next_Time in %d seconds*\n",plc->Next_Time-now);
				}
				elt2=GetNext(&(plc->Tags),elt2);
			}
			/* Read Packets */
			elt2=GetFirst(&(plc->Packets));
			while (elt2!=NULL)
			{
				PACKET *packet=elt2->Data;
				if ((now-packet->Time_Value)>(1.5*packet->Time_Sample))
					Log(LOG_WARNING,"Time Sample exceed on packet : %s (%s)\n",packet->BaseAddress,plc->PlcName);
				if ((now-packet->Time_Value)>=packet->Time_Sample)
				{
					Read_Something=1;
					res=ReadPacket(plc,packet);
					if (res>=0) Comm_err=0; // At least one tag is Ok
					if (mb_errno==EPIPE) CloseSocket(plc->socket,plcs);
				}
				if ((packet->Time_Value+packet->Time_Sample)<(plc->Next_Time))
				{
					plc->Next_Time=packet->Time_Value+packet->Time_Sample;
					Log(LOG_DEBUG,"plc->Next_Time in %d seconds\n",plc->Next_Time-now);
				}
				elt2=GetNext(&(plc->Packets),elt2);
			}
			/* Check Plc */
			if (Comm_err && Read_Something) // All Tags & packets are in error
			{
				Log(LOG_WARNING,"All tags in error for : %s suspending for %d seconds\n",plc->PlcName,WAIT_FOR_RECONNECT);
				plc->Next_Time=now+WAIT_FOR_RECONNECT;
			}
			if (plc->Next_Time>0.8*(time(NULL)+MODBUS_SOCK_TIMEOUT))
			{
				close(plc->socket);
				plc->socket=-1;
				Log(LOG_DEBUG,"Closing socket for plc : %s \n",plc->PlcName);
			}			
			elt=GetNext(plcs,elt);
		}
		sleep(1);
	}
	Log(LOG_NOTICE,"Killing Connections\n");
	KillAll(plcs);
	FreeAll(plcs);
	return(0);
}