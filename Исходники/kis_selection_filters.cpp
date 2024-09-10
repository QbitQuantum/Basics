void KisInvertSelectionFilter::process(KisPixelSelectionSP pixelSelection, const QRect& rect)
{
    Q_UNUSED(rect);
    pixelSelection->invert();
}