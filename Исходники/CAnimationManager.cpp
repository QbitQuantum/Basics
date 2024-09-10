BOOL cAnimationManager::MagProcess(RECT * dockingBarRect, cWindow* window, VECTOR2 * outWindowPos)
{
	BOOL rt = FALSE;
	if( abs( (int)(dockingBarRect->left - (LONG)(window->GetAbsX()) ) ) <= MAG_GAB )
	{
		outWindowPos->x = (float)dockingBarRect->left;
		rt = TRUE;
	}
	else if(abs((int)(dockingBarRect->left - (window->GetAbsX()+window->GetWidth()))) <= MAG_GAB)
	{
		outWindowPos->x = (float)dockingBarRect->left-window->GetWidth();
		rt = TRUE;
	}

	if(abs((int)(dockingBarRect->right - window->GetAbsX())) <= MAG_GAB)
	{
		outWindowPos->x = (float)dockingBarRect->right;
		rt = TRUE;
	}
	else if(abs((int)(dockingBarRect->right - (window->GetAbsX()+window->GetWidth()))) <= MAG_GAB)
	{
		outWindowPos->x = (float)(dockingBarRect->right - window->GetWidth());
		rt = TRUE;
	}

	if(abs((int)(dockingBarRect->top - window->GetAbsY())) <= MAG_GAB)
	{
		outWindowPos->y = (float)dockingBarRect->top;
		rt = TRUE;
	}
	else if(abs((int)(dockingBarRect->top - (window->GetAbsY()+window->GetHeight()))) <= MAG_GAB)
	{
		outWindowPos->y = (float)dockingBarRect->top-window->GetHeight();
		rt = TRUE;
	}
	
	if(abs((int)(dockingBarRect->bottom - window->GetAbsY())) <= MAG_GAB)
	{
		outWindowPos->y = (float)dockingBarRect->bottom;
		rt = TRUE;
	}
	else if(abs((int)(dockingBarRect->bottom - (window->GetAbsY()+window->GetHeight()))) <= MAG_GAB)
	{
		outWindowPos->y = (float)(dockingBarRect->bottom - window->GetHeight());
		rt = TRUE;
	}

//KES 031017 CAPTION이 밖으로 나가지 못하도록
	RECT rc = *((cDialog*)window)->GetCaptionRect();
	OffsetRect( &rc, (int)window->GetAbsX(), (int)window->GetAbsY() );

	if( rc.left < dockingBarRect->left )
	{
		outWindowPos->x = (float)dockingBarRect->left;
		rt = TRUE;
	}
	else if( rc.right > dockingBarRect->right )
	{
		outWindowPos->x = (float)(dockingBarRect->right - ( rc.right - rc.left ));
		rt = TRUE;
	}
	if( rc.top < dockingBarRect->top )
	{
		outWindowPos->y = (float)dockingBarRect->top;
		rt = TRUE;
	}
	else if( rc.bottom > dockingBarRect->bottom )
	{
		outWindowPos->y = (float)(dockingBarRect->bottom - ( rc.bottom - rc.top ));
		rt = TRUE;
	}

	return rt;
}