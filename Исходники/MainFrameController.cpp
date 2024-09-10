CRect MainFrameController::_GetScreenRect(void) const
{
 CDC* pDC = mp_view->GetDC();
 int x_resolution = pDC->GetDeviceCaps(HORZRES);
 int y_resolution = pDC->GetDeviceCaps(VERTRES);
 return CRect(0, 0, x_resolution, y_resolution);
}