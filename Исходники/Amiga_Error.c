__saveds void ErrorProcess(void)
{
	char constring[200];
	BPTR file=NULL;
	ULONG sig;
	ULONG lock;
	ErrorSig=AllocSignal(ErrorSig);
	hassent=1;
	errorprocessalive=1;
	ErrorTask=FindTask(NULL);

	sprintf(constring,"CON:%d/%d/%d/%d/%s/SCREEN%s",20,20,500,300,"radium.nfo",screenname);

	for(;;){
		sig=Wait(1L<<ErrorSig|SIGBREAKF_CTRL_C);
		if(sig&1L<<ErrorSig){
			if(file==NULL){
				file=Open(constring,0x3ee);
			}
			if(file!=NULL && errorwindow==NULL){
				if(mainscreen!=NULL){
					struct Window *tempwindow;
					lock=LockIBase(0);
						tempwindow=mainscreen->FirstWindow;
						for(;;){
							if(tempwindow==NULL) break;
							if(!strcmp(tempwindow->Title,"radium.nfo")){
								errorwindow=tempwindow;
								break;
							}
							tempwindow=tempwindow->NextWindow;
						}
					UnlockIBase(lock);
 				}
			}

			if(file==NULL){
				fprintf(stderr,errorstring);
			}else{
				FPuts(file,errorstring);
			}
			hassent=1;

			if(errorwindow!=NULL){
				WindowToFront(errorwindow);
			}
		}
		if(sig&SIGBREAKF_CTRL_C) break;
	}

	if(file!=NULL){
		Close(file);
	}
	FreeSignal(ErrorSig);
}