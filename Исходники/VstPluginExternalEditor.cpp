//==============================================================================
void VstPluginExternalEditor::resized ()
{
    offsetX = window->getBorderThickness().getLeft ();
    offsetY = window->getTitleBarHeight()
              + window->getMenuBarHeight()
              + window->getBorderThickness().getTop ();
    
    if (handle)
    {
#if defined(LINUX)
        if (isWindowVisible (handle))
            XMoveWindow (display, handle, offsetX, offsetY);
#elif defined(_WIN32)
		HWND hwnd;
		hwnd = GetWindow((HWND) window->getWindowHandle(), GW_CHILD);

    	MoveWindow (hwnd, offsetX, offsetY, editorWidth, editorHeight, true);
#endif
    }

	repaint ();
}