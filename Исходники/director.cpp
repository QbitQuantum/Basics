void CDirector::Loop()
{
	// TODO: 여기에 코드를 입력합니다.
	MSG msg;

	// 기본 메시지 루프입니다.
	while (1)
	{
		if(PeekMessage(&msg,0,0,0,PM_NOREMOVE))
		{
			if(!GetMessage(&msg,0,0,0))
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else if(m_isActive)
		{
			Update();
			Render();
		}
		else
		{
			WaitMessage();
		}
	}

}