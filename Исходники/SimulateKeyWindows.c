int main(void)
{
	POINT pt;
	int i;
	int delaytime;
	int keynum;
	printf("input the delay time(ms):");
	scanf("%d",&delaytime);
	while(1) {
		switch (KEYDOWN(VK_ESCAPE)) {
		case 0:
			keybd_event(VK_NUMLOCK , 0, 0, 0);
			Sleep(delaytime / 2);
			keybd_event(VK_NUMLOCK, 0, KEYEVENTF_KEYUP, 0);
			Sleep(delaytime / 2);
			break;
		case 1:
			while (!KEYDOWN(VK_RETURN )) {
				Sleep(10);
			}
			break;
		}
	}
	return 0;
}