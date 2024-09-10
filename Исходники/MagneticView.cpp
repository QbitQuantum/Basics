void CMagneticView::CaretOff(void)
{
  if (m_bCaret)
  {
    HideCaret();
    DestroyCaret();
    m_bCaret = false;
  }
}