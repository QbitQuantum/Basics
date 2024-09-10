void ole_exit(int *pipe)
{
	App *pad;

	#ifdef DEBUG
	printf("OLGA: OLE_EXIT App %i\n",pipe[1]);
	#endif

	denotify(pipe[1],0,0);
	unLink(FALSE,FALSE,pipe);
	close_doc(FALSE,pipe);
	server_terminated(pipe[1],0);
	client_terminated(pipe[1]);

	_exit:
	pad = apps;

	while (pad)
	{
		if (pad->apID == pipe[1])
		{
			int i;
			
			for (i=0; i<=CMDMAX; i++) globalFree(pad->startCmd[i]);
			
			if ((!pad->Prev) && (!pad->Next)) apps = NULL;
			else
			{
				if (!pad->Prev) apps = pad->Next;
				else
					pad->Prev->Next = pad->Next;
				
				if (pad->Next) pad->Next->Prev = pad->Prev;
			}

			free(pad);
			appCount--;
			
			goto _exit;
		}

		pad = pad->Next;
	}
	
	if (!appCount)
	{
		if ((multitask) && (_app) && (apName))
		{
			char *p = getenv("OLGAMANAGER");
			
			if (p)
			{
				if (!stricmp(p,apName))
				{
					#ifdef DEBUG
					printf(DEBUG_DEACTIVATED);
					#endif
					
					appl_exit();
					exit(0);
				}
			}
		}
	}
}