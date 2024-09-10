LRESULT TouchEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (global.status)
	{
	case global.GS_PLAYING:
	{
		if (global.isGamePaused)
			return 0;

		UINT cInputs = LOWORD(wParam);
		PTOUCHINPUT pInputs = (PTOUCHINPUT)malloc(sizeof(TOUCHINPUT) * cInputs);
		if (pInputs)
		{
			POINT cliCoord = { 0 };
			ClientToScreen(hWnd, &cliCoord);
			if (GetTouchInputInfo((HTOUCHINPUT)lParam, cInputs, pInputs, sizeof(TOUCHINPUT)))
			{
				for (UINT i = 0; i < cInputs; i++)
				{
					int track;
					double ix = double(pInputs[i].x / 100 - cliCoord.x) / WNDWIDTH;
					double iy = double(pInputs[i].y / 100 - cliCoord.y) / WNDHEIGHT;
					if (ix < 0. || ix > 1.)
						continue;
					if (iy <= 0.26)
						track = 0;
					else if (iy <= 0.5)
						track = 1;
					else if (iy <= 0.76)
						track = 2;
					else
						track = 3;
					if (global.heroes[i].jpCount == 0 || (pInputs[i].dwFlags & TOUCHEVENTF_DOWN))
						DoJump(track);
				}
				CloseTouchInputHandle((HTOUCHINPUT)lParam);
			}
			free(pInputs);
		}
		return 0;
		break;
	}

	default:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}