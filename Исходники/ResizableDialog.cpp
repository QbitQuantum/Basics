BOOL CResizableDialog::IsDwmCompositionEnabled(void)
{
    HIGHCONTRAST hc = { sizeof(HIGHCONTRAST) };
    SystemParametersInfo(SPI_GETHIGHCONTRAST, sizeof(HIGHCONTRAST), &hc, FALSE);
    BOOL bEnabled = FALSE;
    return (((hc.dwFlags & HCF_HIGHCONTRASTON) == 0) && SUCCEEDED(DwmIsCompositionEnabled(&bEnabled)) && bEnabled);
}