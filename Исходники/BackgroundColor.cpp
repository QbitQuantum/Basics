void BackgroundColor::SetColor(COLORREF col)
{
   static const INT P_COLOR_DESKTOP[] = {COLOR_DESKTOP};

   if (col == m_CurrentColor)
      return;

   if (SetSysColors(1, P_COLOR_DESKTOP, &col))
      m_CurrentColor = col;
}