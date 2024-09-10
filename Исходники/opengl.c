/***********************************************************************
 *		dibdrv_wglMakeCurrent
 */
static BOOL dibdrv_wglMakeCurrent( HDC hdc, struct wgl_context *context )
{
    HBITMAP bitmap;
    BITMAPOBJ *bmp;
    dib_info dib;
    GLenum type;
    BOOL ret = FALSE;

    if (!context)
    {
        pOSMesaMakeCurrent( NULL, NULL, GL_UNSIGNED_BYTE, 0, 0 );
        return TRUE;
    }

    if (GetPixelFormat( hdc ) != context->format)
        FIXME( "mismatched pixel formats %u/%u not supported yet\n",
               GetPixelFormat( hdc ), context->format );

    bitmap = GetCurrentObject( hdc, OBJ_BITMAP );
    bmp = GDI_GetObjPtr( bitmap, OBJ_BITMAP );
    if (!bmp) return FALSE;

    if (init_dib_info_from_bitmapobj( &dib, bmp ))
    {
        char *bits;
        int width = dib.rect.right - dib.rect.left;
        int height = dib.rect.bottom - dib.rect.top;

        if (dib.stride < 0)
            bits = (char *)dib.bits.ptr + (dib.rect.bottom - 1) * dib.stride;
        else
            bits = (char *)dib.bits.ptr + dib.rect.top * dib.stride;
        bits += dib.rect.left * dib.bit_count / 8;

        TRACE( "context %p bits %p size %ux%u\n", context, bits, width, height );

        if (pixel_formats[context->format - 1].mesa == OSMESA_RGB_565)
            type = GL_UNSIGNED_SHORT_5_6_5;
        else
            type = GL_UNSIGNED_BYTE;

        ret = pOSMesaMakeCurrent( context->context, bits, type, width, height );
        if (ret)
        {
            pOSMesaPixelStore( OSMESA_ROW_LENGTH, abs( dib.stride ) * 8 / dib.bit_count );
            pOSMesaPixelStore( OSMESA_Y_UP, 1 );  /* Windows seems to assume bottom-up */
        }
    }
    GDI_ReleaseObj( bitmap );
    return ret;
}