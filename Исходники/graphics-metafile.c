GpStatus
metafile_FillRectanglesI (GpGraphics *graphics, GpBrush *brush, GDIPCONST GpRect *rects, int count)
{
    /* every rectangle must fit into a INT16 or we must use the float version */
    if (!GpRectArrayFitInInt16 (rects, count)) {
        GpStatus status;
        GpRectF *rf = convert_rects (rects, count);
        if (!rf)
            return OutOfMemory;

        status = metafile_FillRectangles (graphics, brush, rf, count);
        GdipFree (rf);
        return status;
    }
    /* TODO */
    return Ok;
}