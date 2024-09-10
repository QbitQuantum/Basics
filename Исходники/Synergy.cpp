int _tmain(int argc, TCHAR* argv[])
{
//	POINT p;
//	DWORD px,py; 
//	DWORD temp; //이상 마우스 관련 변수

	HANDLE tHandle[2];//이상 쓰레드 관련변수
	DWORD threadId[2];
	DWORD counter=0, tmp=0;

	_tprintf(_T("%d\n"), GetSystemMetrics(SM_CYVIRTUALSCREEN));
	_tprintf(_T("%d\n"),GetSystemMetrics(SM_CYSCREEN));
	// GetSystemMetrics(SM_CXSCREEN) 함수는 현재 주모니터의 너비를 리턴한다
	// GetSystemMetrics(SM_CYSCREEN) 함수는 현재 주모니터의 높이를 리턴한다
	// GetSystemMetrics(SM_CYVIRTUALSCREEN) 서브모니터의 높이를 리턴한다
	// GetSystemMetrics(SM_CXVIRTUALSCREEN) 두너모니터의 너비의 합을 리턴한다
	// GetSystemMetrics(SM_CMONITORS) 연결된 모니터 정보를 가져온다. 듀얼지원안되면0 모니터하나면1 다중이면2

	//쓰레드 생성
	tHandle[0] = CreateThread( NULL, 0, ThreadProc, NULL, 0, &threadId[0]);
	tHandle[1] = CreateThread( NULL, 0, ThreadProc1, NULL, 0, &threadId[1]); 
	
	//쓰레드 검사
	if(tHandle[0] == NULL || tHandle[1] == NULL){
		_tprintf(_T("thread creation fault!") );
		return -1;
	}

	//2개의 쓰레드가 signaled 상태 될때까지 기다림
	WaitForMultipleObjects(2, tHandle, TRUE, INFINITE);


	//쓰레드의 반환을 받음
	GetExitCodeThread(tHandle[0], &tmp);
	counter += tmp;
	GetExitCodeThread(tHandle[1], &tmp);
	counter += tmp;
	
	_tprintf(_T("total count : %d"), counter);
	/*
	while(1){ 

		
		GetCursorPos(&p);	//마우스 위치값얻어오기
		//printf("%d, %d \n", p.x, p.y); //마우스위치출력
		px=p.x;
		py=p.y;

		temp = MouseClickTest();
		if(1==temp)
			_tprintf(_T("click!\n"));
		else if(2==temp)
			_tprintf(_T("right click!\n"));
		else if(3==temp)
			break;
		else if(4==temp)
			_tprintf(_T("wheel click!\n"));


		if(px==(GetSystemMetrics(SM_CXVIRTUALSCREEN)-1))
			SetCursorPos(1,py); //마우스 위치를 이동시키기
		
		if(px==0)
			SetCursorPos(GetSystemMetrics(SM_CXVIRTUALSCREEN)-2,py); //마우스 위치를 이동시키기

		//마우스 위쪽 -> 아래쪽, 아래쪽 -> 위쪽
		if(GetSystemMetrics(SM_CXVIRTUALSCREEN)-GetSystemMetrics(SM_CXSCREEN) > px){
			if(py==(GetSystemMetrics(SM_CYSCREEN)-1))
				SetCursorPos(px,1); //마우스 위치를 이동시키기
			if(py==0)
				SetCursorPos(px,GetSystemMetrics(SM_CYSCREEN)-2); //마우스 위치를 이동시키기
		}else{
			if(py==(GetSystemMetrics(SM_CYVIRTUALSCREEN)-1))
				SetCursorPos(px,1); //마우스 위치를 이동시키기
			if(py==0)
				SetCursorPos(px,GetSystemMetrics(SM_CYVIRTUALSCREEN)-2); //마우스 위치를 이동시키기
		}
		

	}*/

	CloseHandle(tHandle[0]);
	CloseHandle(tHandle[1]);

	return 0;
}