void DDScreen::RestoreDisplay()
{
    if ( DDrawWindow::GetDisplay().IsWindowed() )
    {
        Useless::Rect cr = Window::GetClientRect();
        OpenWindowed( _w, _h );
        MoveWindow( Window::GetHandle(), cr.GetX1(), cr.GetY1(), cr.GetW(), cr.GetH(), true );
    }
}