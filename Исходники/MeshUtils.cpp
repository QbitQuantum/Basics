void CopyVertex(PolygonGroup *srcGroup, uint32 srcPos, PolygonGroup *dstGroup, uint32 dstPos)
{
    int32 srcFormat = srcGroup->GetFormat();
    int32 dstFormat = dstGroup->GetFormat();
    int32 copyFormat = srcFormat&dstFormat;    //most common format;   

    uint8 *srcData = srcGroup->meshData+srcPos*GetVertexSize(srcFormat);
    uint8 *dstData = dstGroup->meshData+dstPos*GetVertexSize(dstFormat);
        
    for (uint32 mask = EVF_LOWER_BIT; mask <= EVF_HIGHER_BIT; mask = mask << 1)
    {
        int32 vertexAttribSize = GetVertexSize(mask);
        if (mask&copyFormat)
            Memcpy(dstData, srcData, vertexAttribSize);

        if (mask&srcFormat)
            srcData+=vertexAttribSize;
        
        if (mask&dstFormat)
            dstData+=vertexAttribSize;

         copyFormat&=~mask;
    }    
    
    /*unsupported stream*/
    DVASSERT((copyFormat == 0)&&"Unsupported attribute stream in copy");
    
}