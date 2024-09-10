bool wxTextMeasureBase::GetPartialTextExtents(const wxString& text,
                                              wxArrayInt& widths,
                                              double scaleX)
{
    widths.Empty();
    if ( text.empty() )
        return true;

    MeasuringGuard guard(*this);

    widths.Add(0, text.length());

    return DoGetPartialTextExtents(text, widths, scaleX);
}