GpStatus WINGDIPAPI GdipPathIterEnumerate(GpPathIterator* iterator, INT* resultCount,
    GpPointF *points, BYTE *types, INT count)
{
    TRACE("(%p, %p, %p, %p, %d)\n", iterator, resultCount, points, types, count);

    if((count < 0) || !resultCount)
        return InvalidParameter;

    if(count == 0){
        *resultCount = 0;
        return Ok;
    }

    return GdipPathIterCopyData(iterator, resultCount, points, types, 0, count-1);
}