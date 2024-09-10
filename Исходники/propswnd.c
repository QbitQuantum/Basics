HWND PropGetHWNDCombobox(HWND parent)
{
    HWND rv = CreateWindow("combobox", "", WS_VISIBLE | WS_CHILD | WS_BORDER | CBS_SORT | CBS_DROPDOWN,
                                  CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                  parent, 0, hInstance, NULL);
    POINT pt;
    HWND h;
    pt.x = pt.y = 5;
    h = ChildWindowFromPoint(rv, pt);
    SubclassPropsEditWindow(h);
    return rv;
}