Control::Control(Control *newParent)
{
    wantedInputBits = 0;
    stateBits = 0;
    zOrder = 0;
    parent = NULL;
    hwndParent = NULL;
    layout = NULL;
    hCursor = NULL;
    cachedStyle = NULL;
    SetStyle(NULL);
    pos = Rect();
    if (newParent)
        SetParent(newParent);
}