static void Docking_AdjustPosition(HWND hwnd,RECT *rcDisplay,RECT *rc)
{
	APPBARDATA abd;

	ZeroMemory(&abd,sizeof(abd));
	abd.cbSize=sizeof(abd);
	abd.hWnd=hwnd;
	abd.uEdge=docked==DOCKED_LEFT?ABE_LEFT:ABE_RIGHT;
	abd.rc=*rc;
	abd.rc.top=rcDisplay->top;
	abd.rc.bottom=rcDisplay->bottom;
	if(docked==DOCKED_LEFT) {
		abd.rc.right=rcDisplay->left+abd.rc.right-abd.rc.left;
		abd.rc.left=rcDisplay->left;
	}
	else {
		abd.rc.left=rcDisplay->right-(abd.rc.right-abd.rc.left);
		abd.rc.right=rcDisplay->right;

	}
	SHAppBarMessage(ABM_SETPOS,&abd);
	*rc=abd.rc;
    {
        //RECT r;
        //SetWindowRect(hwnd,&r);
        //OnMoving(hwnd,&r);
    }
}