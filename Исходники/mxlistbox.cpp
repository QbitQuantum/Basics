mxListBox::mxListBox (mxWindow *parent, int x, int y, int w, int h, int id, int style)
    : mxWidget (parent, x, y, w, h)
{
    if (!parent)
        return;

    DWORD dwStyle = WS_VISIBLE | WS_CHILD | LBS_NOTIFY | WS_VSCROLL | WS_HSCROLL;
    HWND hwndParent = (HWND) ((mxWidget *) parent)->getHandle ();

    if (style == MultiSelection)
        dwStyle |= LBS_MULTIPLESEL | LBS_EXTENDEDSEL;

    void *handle = (void *) CreateWindowEx (WS_EX_CLIENTEDGE, "LISTBOX", "", WS_VISIBLE | WS_CHILD | LBS_NOTIFY | WS_VSCROLL,
                                            x, y, w, h, hwndParent,
                                            (HMENU) id, (HINSTANCE) GetModuleHandle (NULL), NULL);

    SendMessage ((HWND) handle, WM_SETFONT, (WPARAM) (HFONT) GetStockObject (ANSI_VAR_FONT), MAKELPARAM (TRUE, 0));
    SetWindowLong ((HWND) handle, GWL_USERDATA, (LONG) this);

    setHandle (handle);
    setType (MX_LISTBOX);
    setParent (parent);
    setId (id);
}