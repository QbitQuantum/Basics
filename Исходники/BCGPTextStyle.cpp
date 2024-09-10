void TextStyleCreateFont (const CBCGPTextStyleRef& textStyle, CBCGPDrawContext& drawCtx, CFont& font)
{
    LOGFONT lf;
    ZeroMemory (&lf, sizeof (lf));

    CString strFontName = textStyle.GetFontName ();
    double dPointSize = textStyle.GetFontSize ();

    lstrcpyn (lf.lfFaceName, strFontName, LF_FACESIZE);
    lf.lfHeight = (long)(dPointSize * 10 * drawCtx.GetScale ());
    lf.lfWeight = textStyle.IsBold () ? FW_BOLD : FW_NORMAL;
    lf.lfItalic = textStyle.IsItalic ();
    font.CreatePointFontIndirect (&lf, drawCtx.GetDC ());
}