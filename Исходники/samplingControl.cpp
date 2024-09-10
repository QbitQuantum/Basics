void samplingControl::setSliceWidths(NumericVector inWidths)
{
    if (inWidths.length() != 11)
    {
        ::Rf_error("Slice widths must have length 11.\n"); 
    }
    int i;
    for (i = 0; i < inWidths.length(); i++)
    {
        sliceWidths[i] = inWidths[i];
    }
}