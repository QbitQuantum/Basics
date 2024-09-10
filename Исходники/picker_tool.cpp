void PICKER_TOOL::setControls()
{
    KIGFX::VIEW_CONTROLS* controls = getViewControls();

    controls->ShowCursor( m_cursorVisible );
    controls->SetSnapping( m_cursorSnapping );
    controls->CaptureCursor( m_cursorCapture );
    controls->SetAutoPan( m_autoPanning );
}