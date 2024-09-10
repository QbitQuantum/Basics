long HandleServerMsg(void)
{
	unsigned long PubScreenModes;
	BlankMsg *CurMsg;
	
	while(CurMsg = (BlankMsg *)GetMsg(ServerPort))
	{
		long Type = CurMsg->bm_Type;
		long Flags = CurMsg->bm_Flags;

		if(Flags & BF_REPLY)
		{
			if(!(Flags & BF_INTERNAL))
				FreeVec(CurMsg);
		}
		else
		{
			CurMsg->bm_Flags |= BF_REPLY;
			ReplyMsg((struct Message *)CurMsg);
		}
		
		switch(Type)
		{
		case BM_DOBLANK:
			if(Flags & BF_REPLY)
			{
				if(!CheckIO((struct IORequest *)TimeOutIO))
				{
					AbortIO((struct IORequest *)TimeOutIO);
					WaitIO((struct IORequest *)TimeOutIO);
					SetSignal(0L, SIG_TIMER);
				}
				if(ServerScr)
				{
					UnblankMousePointer(Wnd);
					CloseScreen(ServerScr);
					ServerScr = 0L;
				}
				if(!PingTask)
					PingTask = CreateTask("GarshnePing", -5, PingFunc, 4096);
				Blanking = TRUE;
			}
			break;
		case BM_DOTESTBLANK:
			if(Flags & BF_REPLY)
			{
				if(!PingTask)
					PingTask = CreateTask("GarshnePing", -5, PingFunc, 4096);
				Blanking = TRUE;
			}
			break;
		case BM_INITMSG:
			if(BlankAfterInit)
			{
				BlankAfterInit = FALSE;
				MessageModule("GarshneClient", BM_DOBLANK);
			}
			break;
		case BM_FAILED:
			if(PingTask)
			{
				Signal(PingTask, SIGBREAKF_CTRL_C);
				PingTask = 0L;
			}
			InternalBlank();
			break;
		case BM_SENDBLANK:
			if((Flags & BF_REPLY)|| BlankingDisabled)
				break;
			if(ServerScr &&(UsagePercent() > 40))
				break;
			PubScreenModes = SetPubScreenModes(0L);
			if(Stricmp(Prefs->bp_Blanker, "Random"))
			{
				if(!Blanking || ServerScr)
					MessageModule("GarshneClient", BM_DOBLANK);
			}
			else
			{
				if(!Blanking || Prefs->bp_Flags & BF_REPLACE)
				{
					MessageModule("GarshneClient", BM_DELAYEDQUIT);
					BlankAfterInit = TRUE;
					LoadModule(Prefs->bp_Dir, Prefs->bp_Blanker);
				}
				else if(ServerScr)
					MessageModule("GarshneClient", BM_DOBLANK);
			}
			SetPubScreenModes(PubScreenModes);
			break;
		case BM_SENDTEST:
			if((Flags & BF_REPLY)|| BlankingDisabled)
				break;
			PubScreenModes = SetPubScreenModes(0L);
			MessageModule("GarshneClient", BM_DOTESTBLANK);
			SetPubScreenModes(PubScreenModes);
			break;
		case BM_SENDUNBLANK:
			if(Flags & BF_REPLY)
				break;
			if(ServerScr)
			{
				UnblankMousePointer(Wnd);
				CloseScreen(ServerScr);
				ServerScr = 0L;
			}
			Blanking = FALSE;
			MessageModule("GarshneClient", BM_UNBLANK);
			if(PingTask)
			{
				Signal(PingTask, SIGBREAKF_CTRL_C);
				PingTask = 0L;
			}
			break;
		default:
			break;
		}
	}

	return OK;
}