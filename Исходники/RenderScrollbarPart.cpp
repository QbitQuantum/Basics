static int calcScrollbarThicknessUsing(const Length& l, int containingLength)
{
    if (l.isIntrinsicOrAuto())
        return ScrollbarTheme::nativeTheme()->scrollbarThickness();
    return l.calcMinValue(containingLength);
}