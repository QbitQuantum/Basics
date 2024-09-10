__declspec(dllexport) void __cdecl VDDDispatch(void) 
{
	char			str[512];
	DWORD			count;
	DWORD			msgs;
	int				retval;
	int				node_num;
	BYTE*			p;
	vdd_status_t*	status;
	static  DWORD	writes;
	static  DWORD	bytes_written;
	static	DWORD	reads;
	static  DWORD	bytes_read;
	static  DWORD	inbuf_poll;
	static	DWORD	online_poll;
	static	DWORD	status_poll;
	static	DWORD	vdd_yields;
	static	DWORD	vdd_calls;
	VDD_IO_HANDLERS  IOHandlers = { NULL };
	static VDD_IO_PORTRANGE PortRange;

	retval=0;
	node_num=getBH();

	lprintf(LOG_DEBUG,"VDD_OP: (handle=%d) %d (arg=%X)", getAX(),getBL(),getCX());
	vdd_calls++;

	switch(getBL()) {

		case VDD_OPEN:

			sscanf("$Revision: 1.40 $", "%*s %s", revision);

			lprintf(LOG_INFO,"Synchronet Virtual Device Driver, rev %s %s %s"
				,revision, __DATE__, __TIME__);
#if 0
			sprintf(str,"sbbsexec%d.log",node_num);
			fp=fopen(str,"wb");
#endif

			sprintf(str,"\\\\.\\mailslot\\sbbsexec\\wr%d",node_num);
			rdslot=CreateMailslot(str
				,0 //LINEAR_RX_BUFLEN		/* Max message size (0=any) */
				,MAILSLOT_WAIT_FOREVER 	/* Read timeout */
				,NULL);
			if(rdslot==INVALID_HANDLE_VALUE) {
				lprintf(LOG_ERR,"!VDD_OPEN: Error %d opening %s"
					,GetLastError(),str);
				retval=1;
				break;
			}

			sprintf(str,"\\\\.\\mailslot\\sbbsexec\\rd%d",node_num);
			wrslot=CreateFile(str
				,GENERIC_WRITE
				,FILE_SHARE_READ
				,NULL
				,OPEN_EXISTING
				,FILE_ATTRIBUTE_NORMAL
				,(HANDLE) NULL);
			if(wrslot==INVALID_HANDLE_VALUE) {
				lprintf(LOG_ERR,"!VDD_OPEN: Error %d opening %s"
					,GetLastError(),str);
				retval=2;
				break;
			}

			if(RingBufInit(&rdbuf, RINGBUF_SIZE_IN)!=0) {
				retval=3;
				break;
			}

			sprintf(str,"sbbsexec_hungup%d",node_num);
			hungup_event=OpenEvent(
				EVENT_ALL_ACCESS,	/* access flag  */
				FALSE,				/* inherit flag  */
				str);				/* pointer to event-object name  */
			if(hungup_event==NULL) {
				lprintf(LOG_ERR,"!VDD_OPEN: Error %d opening %s"
					,GetLastError(),str);
				retval=4;
				break;
			}

			sprintf(str,"sbbsexec_hangup%d",node_num);
			hangup_event=OpenEvent(
				EVENT_ALL_ACCESS,	/* access flag  */
				FALSE,				/* inherit flag  */
				str);				/* pointer to event-object name  */
			if(hangup_event==NULL) {
				lprintf(LOG_WARNING,"!VDD_OPEN: Error %d opening %s"
					,GetLastError(),str);
			}

			status_poll=0;
			inbuf_poll=0;
			online_poll=0;
			yields=0;

			lprintf(LOG_INFO,"Yield interval: %f milliseconds", yield_interval);

			if(virtualize_uart) {
				lprintf(LOG_INFO,"Virtualizing UART (0x%x, IRQ %u)"
					,uart_io_base, uart_irq);

				IOHandlers.inb_handler = uart_rdport;
				IOHandlers.outb_handler = uart_wrport;
				PortRange.First=uart_io_base;
				PortRange.Last=uart_io_base + UART_IO_RANGE;

				VDDInstallIOHook((HANDLE)getAX(), 1, &PortRange, &IOHandlers);

				interrupt_event=CreateEvent(NULL,FALSE,FALSE,NULL);
				InitializeCriticalSection(&interrupt_mutex);

				_beginthread(interrupt_thread, 0, NULL);
			}

			lprintf(LOG_DEBUG,"VDD_OPEN: Opened successfully (wrslot=%p)", wrslot);

			_beginthread(input_thread, 0, NULL);

			retval=0;
			break;

		case VDD_CLOSE:
			lprintf(LOG_INFO,"VDD_CLOSE: rdbuf=%u "
				"status_poll=%u inbuf_poll=%u online_poll=%u yields=%u vdd_yields=%u vdd_calls=%u"
				,RingBufFull(&rdbuf),status_poll,inbuf_poll,online_poll
				,yields,vdd_yields,vdd_calls);
			lprintf(LOG_INFO,"           read=%u bytes (in %u calls)",bytes_read,reads);
			lprintf(LOG_INFO,"           wrote=%u bytes (in %u calls)",bytes_written,writes);

			if(virtualize_uart) {
				lprintf(LOG_INFO,"Uninstalling Virtualizaed UART IO Hook");
				VDDDeInstallIOHook((HANDLE)getAX(), 1, &PortRange);
			}

			CloseHandle(rdslot);
			CloseHandle(wrslot);
			if(hungup_event!=NULL)
				CloseHandle(hungup_event);
			if(hangup_event!=NULL)
				CloseHandle(hangup_event);

#if 0	/* This isn't strictly necessary... 
		   and possibly the cause of a NULL dereference in the input_thread */
			RingBufDispose(&rdbuf);
#endif
			status_poll=0;
			retval=0;

			break;

		case VDD_READ:
			count = getCX();
			if(count != 1)
				lprintf(LOG_DEBUG,"VDD_READ of %d",count);
			p = (BYTE*) GetVDMPointer((ULONG)((getES() << 16)|getDI())
				,count,FALSE); 
			retval=vdd_read(p, count);
			reads++;
			bytes_read+=retval;
			reset_yield();
			break;

		case VDD_PEEK:
			count = getCX();
			if(count != 1)
				lprintf(LOG_DEBUG,"VDD_PEEK of %d",count);

			p = (BYTE*) GetVDMPointer((ULONG)((getES() << 16)|getDI())
				,count,FALSE); 
			retval=RingBufPeek(&rdbuf,p,count);
			reset_yield();
			break;

		case VDD_WRITE:
			count = getCX();
			if(count != 1)
				lprintf(LOG_DEBUG,"VDD_WRITE of %d",count);
			p = (BYTE*) GetVDMPointer((ULONG)((getES() << 16)|getDI())
				,count,FALSE); 
			if(!WriteFile(wrslot,p,count,&retval,NULL)) {
				lprintf(LOG_ERR,"!VDD_WRITE: WriteFile Error %d (size=%d)"
					,GetLastError(),retval);
				retval=0;
			} else {
				writes++;
				bytes_written+=retval;
				reset_yield();
			}
			break;

		case VDD_STATUS:

			status_poll++;
			count = getCX();
			if(count != sizeof(vdd_status_t)) {
				lprintf(LOG_DEBUG,"!VDD_STATUS: wrong size (%d!=%d)",count,sizeof(vdd_status_t));
				retval=sizeof(vdd_status_t);
				break;
			}
			status = (vdd_status_t*) GetVDMPointer((ULONG)((getES() << 16)|getDI())
				,count,FALSE); 

			status->inbuf_size=RINGBUF_SIZE_IN;
			status->inbuf_full=RingBufFull(&rdbuf);
			msgs=0;

			/* OUTBUF FULL/SIZE */
			if(!GetMailslotInfo(
				wrslot,					/* mailslot handle  */
 				&status->outbuf_size,	/* address of maximum message size  */
				&status->outbuf_full,	/* address of size of next message  */
				&msgs,					/* address of number of messages  */
 				NULL					/* address of read time-out  */
				)) {
				lprintf(LOG_ERR,"!VDD_STATUS: GetMailSlotInfo(%p) failed, error %u (msgs=%u, inbuf_full=%u, inbuf_size=%u)"
					,wrslot
					,GetLastError(), msgs, status->inbuf_full, status->inbuf_size);
				status->outbuf_full=0;
				status->outbuf_size=DEFAULT_MAX_MSG_SIZE;
			} else
				lprintf(LOG_DEBUG,"VDD_STATUS: MailSlot maxmsgsize=%u, nextmsgsize=%u, msgs=%u"
					,status->outbuf_size
					,status->outbuf_full
					,msgs);
			if(status->outbuf_full==MAILSLOT_NO_MESSAGE)
				status->outbuf_full=0;
			status->outbuf_full*=msgs;
			
			/* ONLINE */
			if(WaitForSingleObject(hungup_event,0)==WAIT_OBJECT_0)
				status->online=0;
			else
				status->online=1;

			retval=0;	/* success */
			break;

		case VDD_INBUF_PURGE:
			RingBufReInit(&rdbuf);
			retval=0;
			break;

		case VDD_OUTBUF_PURGE:
			lprintf(LOG_WARNING,"!VDD_OUTBUF_PURGE: NOT IMPLEMENTED");
			retval=0;
			break;

		case VDD_INBUF_FULL:
			retval=RingBufFull(&rdbuf);
			inbuf_poll++;
			break;

		case VDD_INBUF_SIZE:
			retval=RINGBUF_SIZE_IN;
			break;

		case VDD_OUTBUF_FULL:
			if(!GetMailslotInfo(
				wrslot,		/* mailslot handle  */
 				NULL,		/* address of maximum message size  */
				&retval,	/* address of size of next message  */
				&msgs,		/* address of number of messages  */
 				NULL		/* address of read time-out  */
				))
				retval=0;
			if(retval==MAILSLOT_NO_MESSAGE)
				retval=0;
			retval*=msgs;
			break;

		case VDD_OUTBUF_SIZE:
			if(!GetMailslotInfo(
				wrslot,		/* mailslot handle  */
 				&retval,	/* address of maximum message size  */
				NULL,		/* address of size of next message  */
				NULL,		/* address of number of messages  */
 				NULL		/* address of read time-out  */
				)) 
				retval=DEFAULT_MAX_MSG_SIZE;
			break;

		case VDD_ONLINE:
			if(WaitForSingleObject(hungup_event,0)==WAIT_OBJECT_0)
				retval=0;
			else
				retval=1;
			online_poll++;
			break;

		case VDD_YIELD:			/* forced yield */
			vdd_yields++;
			yield();
			break;

		case VDD_MAYBE_YIELD:	/* yield if YieldInterval is enabled and expired */
			maybe_yield();
			break;

		case VDD_LOAD_INI_FILE:	/* Load and parse settings file */
			{
				FILE*	fp;
				char	cwd[MAX_PATH+1];

				/* Load exec/sbbsexec.ini first (setting default values) */
				count = getCX();
				p = (BYTE*)GetVDMPointer((ULONG)((getES() << 16)|getDI())
					,count,FALSE); 
				iniFileName(ini_fname, sizeof(ini_fname), p, INI_FILENAME);
				if((fp=fopen(ini_fname,"r"))!=NULL) {
					ini=iniReadFile(fp);
					fclose(fp);
					parse_ini(ROOT_SECTION);
				}

				/* Load cwd/sbbsexec.ini second (over-riding default values) */
				GetCurrentDirectory(sizeof(cwd),cwd);
				iniFileName(ini_fname, sizeof(ini_fname), cwd, INI_FILENAME);
				if((fp=fopen(ini_fname,"r"))!=NULL) {
					ini=iniReadFile(fp);
					fclose(fp);
					parse_ini(ROOT_SECTION);
				}
			}
			break;

		case VDD_LOAD_INI_SECTION:	/* Parse (program-specific) sub-section of settings file */
			count = getCX();
			p = (BYTE*)GetVDMPointer((ULONG)((getES() << 16)|getDI())
				,count,FALSE); 
			parse_ini(p);
			break;

		case VDD_DEBUG_OUTPUT:	/* Send string to debug output */
			count = getCX();
			p = (BYTE*)GetVDMPointer((ULONG)((getES() << 16)|getDI())
				,count,FALSE); 
			lputs(LOG_INFO, p);
			break;

		case VDD_HANGUP:
			hangup();
			break;

		default:
			lprintf(LOG_ERR,"!UNKNOWN VDD_OP: %d",getBL());
			break;
	}
	setAX((WORD)retval);
}