CExtentVisualWindow::~CExtentVisualWindow()
{
    if (IsWindow(_hwnd))
        DestroyWindow(_hwnd);
}