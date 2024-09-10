mxListView::mxListView (mxWindow *parent, int x, int y, int w, int h, int id)
: mxWidget (parent, x, y, w, h)
{
	if (!parent)
		return;

	d_this = new mxListView_i;

	DWORD dwStyle = LVS_NOSORTHEADER | LVS_REPORT | LVS_SHOWSELALWAYS | WS_VISIBLE | WS_CHILD;
	HWND hwndParent = (HWND) ((mxWidget *) parent)->getHandle ();

	d_this->d_hwnd = CreateWindowEx (WS_EX_CLIENTEDGE, WC_LISTVIEW, "", dwStyle,
				x, y, w, h, hwndParent,
				(HMENU) id, (HINSTANCE) GetModuleHandle (NULL), NULL);
	
	SendMessage (d_this->d_hwnd, WM_SETFONT, (WPARAM) (HFONT) GetStockObject (ANSI_VAR_FONT), MAKELPARAM (TRUE, 0));
	SetWindowLong (d_this->d_hwnd, GWL_USERDATA, (LONG) this);

	setHandle ((void *) d_this->d_hwnd);
	setType (MX_LISTVIEW);
	setParent (parent);
	setId (id);
}