HRESULT SkFontMgr_DirectWrite::getDefaultFontFamily(IDWriteFontFamily** fontFamily) const {
    NONCLIENTMETRICSW metrics;
    metrics.cbSize = sizeof(metrics);
    if (0 == SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0)) {
        return E_UNEXPECTED;
    }
    HRM(this->getByFamilyName(metrics.lfMessageFont.lfFaceName, fontFamily),
        "Could not create DWrite font family from LOGFONT.");
    return S_OK;
}