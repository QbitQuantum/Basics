void CSymbolTypeComboBox::DrawSymbol(CDC&   dcContext,
                             LPPOINT lpPoints,
                             int npts,
                             bool filledSym)

{
    if (filledSym)
    {
        dcContext.SetPolyFillMode(WINDING);
        dcContext.Polygon(lpPoints, npts);
    }
    else
    {
        dcContext.MoveTo(lpPoints[0].x, lpPoints[0].y);
        for (int i = 1; i < npts; i++)
            dcContext.LineTo(lpPoints[i].x, lpPoints[i].y);
        dcContext.LineTo(lpPoints[0].x, lpPoints[0].y);
    }
}