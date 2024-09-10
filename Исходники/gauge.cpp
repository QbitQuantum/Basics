bool wxGauge::SetForegroundColour(
  const wxColour&                   rColour
)
{
    if (!wxControl::SetForegroundColour(rColour))
        return FALSE;

    LONG                            lColor = (LONG)rColour.GetPixel();

    ::WinSetPresParam( GetHwnd()
                      ,PP_FOREGROUNDCOLOR
                      ,sizeof(LONG)
                      ,(PVOID)&lColor
                     );

    return TRUE;
} // end of wxGauge::SetForegroundColour