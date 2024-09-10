BOOL WRectangle::IntersectRect( LPCRECT lpRect1, LPCRECT lpRect2 )
{
	int x1 = max(lpRect1->left, lpRect2->left);
	int x2 = min(lpRect1->right, lpRect2->right); 
	int y1 = max(lpRect1->top, lpRect2->top);
	int y2 = min(lpRect1->bottom, lpRect2->bottom); 
	
	if (x2 >= x1 && y2 >= y1)
	{ 
		SetRect(x1,x2,y1,y2);
	}

	SetRectEmpty();
	return false;
}