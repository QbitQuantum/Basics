GpStatus WINGDIPAPI GdipResetImageAttributes(GpImageAttributes *imageAttr,
    ColorAdjustType type)
{
    TRACE("(%p,%u)\n", imageAttr, type);

    if(!imageAttr || type >= ColorAdjustTypeCount)
        return InvalidParameter;

    memset(&imageAttr->colormatrices[type], 0, sizeof(imageAttr->colormatrices[type]));
    GdipSetImageAttributesColorKeys(imageAttr, type, FALSE, 0, 0);
    GdipSetImageAttributesRemapTable(imageAttr, type, FALSE, 0, NULL);
    GdipSetImageAttributesGamma(imageAttr, type, FALSE, 0.0);

    return Ok;
}