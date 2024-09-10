void ProcKernelModuleLoaded(PUNICODE_STRING FullImageName, HANDLE  ProcessId, PIMAGE_INFO  ImageInfo)
{
	char buf[256], *s, *sbuf;
	ANSI_STRING AS;
	ULONG l;
	modctl_t *ctl;
	int reloaded = 0;
	
	if (ImageInfo->SystemModeImage) {
		l = RtlUnicodeStringToAnsiSize(FullImageName);
		if (l == 0)
			return;

		RtlInitAnsiString(&AS, NULL);
		RtlUnicodeStringToAnsiString(&AS, FullImageName, TRUE);
		if (AS.MaximumLength >= AS.Length + 1) {
 			AS.Buffer[AS.Length] = '\0';
 		} else {
 			RtlFreeAnsiString(&AS);
 			return;
 		}
 	
		s = strrchr(AS.Buffer, '\\');
		if (s == NULL) {
			RtlFreeAnsiString(&AS);
			return;
		}
		
		s++;
		ctl = modules;
		do {
			if (strcmp(ctl->mod_modname, s) == 0 && ctl->size == ImageInfo->ImageSize) {
				ctl->imgbase = (uintptr_t) ImageInfo->ImageBase;
				ctl->loadcnt++;
				reloaded = 1;
				dprintf("dtrace.sys: module %s reloaded\n", s);
				break;
			}
				
		} while ((ctl = ctl->mod_next) != modules);
		
		if (reloaded == 0) {
			ctl = ExAllocatePoolWithTag(NonPagedPool, sizeof(modctl_t), 'Tag1');
			
			if (ctl == NULL) {
				return;
			}
			sbuf = ExAllocatePoolWithTag(NonPagedPool, strlen(s)+1, 'Tag1');
			RtlFreeAnsiString(&AS);
			
			if (sbuf == NULL) {
				ExFreePoolWithTag(ctl, 'Tag1');
				return;
			}
			strcpy(sbuf, s);
			ctl->imgbase = (uintptr_t) ImageInfo->ImageBase;
			ctl->size = ImageInfo->ImageSize;
			ctl->mod_modname = sbuf;
			ctl->loadcnt = 0;
			ctl->nenabled = 0;
			ctl->fbt_nentries = 0;
			dprintf("dtrace.sys: module %s loaded\n", s);
			
			ctl->mod_next = modules->mod_next;
			modules->mod_next = ctl;
		}	
		dtrace_module_loaded(ctl);
	}
}