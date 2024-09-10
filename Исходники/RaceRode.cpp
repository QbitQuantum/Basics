void RaceRoad::play(){
	//RaceRoad myroad(Player p());
	RaceRoad(/*new Player()*/);
	represent();
	short direction;
	char ispressed(1);

	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD NumInputs = 0;
    DWORD InputsRead = 0;
    bool running = true;
    INPUT_RECORD irInput;
    GetNumberOfConsoleInputEvents(hInput, &NumInputs);
    while(running){
		direction=0;
        ReadConsoleInput(hInput, &irInput, 1, &InputsRead);
        switch(irInput.Event.KeyEvent.wVirtualKeyCode){
            case VK_ESCAPE:
                running = false;
            break;
			case VK_LEFT:
			case VK_NUMPAD4:
				direction=-1;
				ispressed*=-1;
			break;
			case VK_RIGHT:
			case VK_NUMPAD6:
				direction=1;
				ispressed*=-1;
			break;
		}
		if(ispressed>0)moveCar(direction);
		if(isHit())cout<<"HALAL"<<endl;
		represent();
		Sleep(1000);
		
    }
}