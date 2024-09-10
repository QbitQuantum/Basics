void getch2_enable(void)
{
	DWORD retval;
    in = GetStdHandle(STD_INPUT_HANDLE);
   	if(!GetNumberOfConsoleInputEvents(in,&retval))
	{
		printf("getch2: %i can't get number of input events  [disabling console input]\n",GetLastError());
		getch2_status = 0;
	}
    else getch2_status=1;
}