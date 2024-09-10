// -------------------------------------------------------------------------------- //
void guSplashFrame::OnEraseBackground( wxEraseEvent &event )
{
    wxDC * dc = event.GetDC();
    if( dc )
    {
        dc->DrawBitmap( * m_Bitmap, 0, 0, false );
    }
}