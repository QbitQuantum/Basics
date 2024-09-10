CPLErr JPEG2000RasterBand::IReadBlock( int nBlockXOff, int nBlockYOff,
                                      void * pImage )
{
    int             i, j;

    // Decode image from the stream, if not yet
    if ( !poGDS->DecodeImage() )
    {
        return CE_Failure;
    }

    // Now we can calculate the pixel offset of the top left by multiplying
    // block offset with the block size.

    /* In case the dimensions of the image are not multiple of the block dimensions */
    /* take care of not requesting more pixels than available for the blocks at the */
    /* right or bottom of the image */
    int nWidthToRead = MIN(nBlockXSize, poGDS->nRasterXSize - nBlockXOff * nBlockXSize);
    int nHeightToRead = MIN(nBlockYSize, poGDS->nRasterYSize - nBlockYOff * nBlockYSize);

    jas_image_readcmpt( poGDS->psImage, nBand - 1,
                        nBlockXOff * nBlockXSize, nBlockYOff * nBlockYSize,
                        nWidthToRead, nHeightToRead, psMatrix );

    int nWordSize = GDALGetDataTypeSize(eDataType) / 8;
    int nLineSize = nBlockXSize * nWordSize;
    GByte* ptr = (GByte*)pImage;

    /* Pad incomplete blocks at the right or bottom of the image */
    if (nWidthToRead != nBlockXSize || nHeightToRead != nBlockYSize)
        memset(pImage, 0, nLineSize * nBlockYSize);

    for( i = 0; i < nHeightToRead; i++, ptr += nLineSize )
    {
        for( j = 0; j < nWidthToRead; j++ )
        {
            // XXX: We need casting because matrix element always
            // has 32 bit depth in JasPer
            // FIXME: what about float values?
            switch( eDataType )
            {
                case GDT_Int16:
                {
                    ((GInt16*)ptr)[j] = (GInt16)jas_matrix_get(psMatrix, i, j);
                }
                break;
                case GDT_Int32:
                {
                    ((GInt32*)ptr)[j] = (GInt32)jas_matrix_get(psMatrix, i, j);
                }
                break;
                case GDT_UInt16:
                {
                    ((GUInt16*)ptr)[j] = (GUInt16)jas_matrix_get(psMatrix, i, j);
                }
                break;
                case GDT_UInt32:
                {
                    ((GUInt32*)ptr)[j] = (GUInt32)jas_matrix_get(psMatrix, i, j);
                }
                break;
                case GDT_Byte:
                default:
                {
                    ((GByte*)ptr)[j] = (GByte)jas_matrix_get(psMatrix, i, j);
                }
                break;
            }
        }
    }

    return CE_None;
}