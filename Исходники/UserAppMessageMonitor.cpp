void CounterView::Draw (BRect updateRect)
{
  BRect MovingRect (
    m_MovingDotPoint.x,
    m_MovingDotPoint.y,
    m_MovingDotPoint.x + m_MovingDotSize,
    m_MovingDotPoint.y + m_MovingDotSize);
  char TempString [40];

  if (m_BackingBitmap != NULL)
  {
    m_BackingBitmap->Lock ();
    m_BackingView.SetHighColor (60, 60, 255, 8);
    m_BackingView.FillRect (m_BndRect);
    m_BackingView.SetHighColor (255, 255, 0, 255);
    m_BackingView.MovePenTo (m_TextStartPoint);
    sprintf (TempString, "%d", m_CurrentCount);
    m_BackingView.DrawString (TempString);
    m_BackingView.FillRect (MovingRect);
    m_BackingView.Sync ();
    m_BackingBitmap->Unlock ();
    MovePenTo (0, 0);
    DrawBitmap (m_BackingBitmap);
  }
}