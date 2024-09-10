FxBool txConvert( Gu3dfInfo *info, GrTextureFormat_t srcFormat,
                  int srcWidth, int srcHeight,
                  const void *srcImage, FxU32 flags,
                  const void *palNcc )
{
  TxMip srcMip;
  TxMip trueColorMip;
  TxMip outputMip;
  TxMip tmpMip;

  /*
   * Make a txMip out of the passed data.
   */
  memset( &srcMip, 0, sizeof( srcMip ) );
  srcMip.format         = srcFormat;
  srcMip.width          = srcWidth;
  srcMip.height         = srcHeight;
  srcMip.depth          = 1;

  if( palNcc )
    {
      switch( srcFormat )
        {
        case GR_TEXFMT_YIQ_422:
        case GR_TEXFMT_AYIQ_8422:
         txNccToPal( srcMip.pal, palNcc);
          break;
        case GR_TEXFMT_P_8:
          memcpy( srcMip.pal, palNcc, sizeof( FxU32 ) * 256 );
          break;
        }
    }
  srcMip.data[0]        = ( void * )srcImage;

  /*
   * Set up a txMip to put a true color version of the texture in.
   */
  memset( &trueColorMip, 0, sizeof( trueColorMip ) );
  trueColorMip.format         = GR_TEXFMT_ARGB_8888;
  trueColorMip.width          = srcWidth;
  trueColorMip.height         = srcHeight;
  /*
   * Set the depth to the mipmapped depth to allocate the image.
   */
#ifdef GLIDE3
  trueColorMip.depth          = info->header.large_lod - info->header.small_lod + 1;
#else
  trueColorMip.depth          = info->header.small_lod - info->header.large_lod + 1;
#endif
  if( !txMipAlloc( &trueColorMip ) )
    return FXFALSE;

  /*
   * Set to one level only since we only want to dequant the first 
   * level.
   */
  trueColorMip.depth          = 1;

  /*
   * Convert from the input format to truecolor.
   */
  txMipDequantize( &trueColorMip, &srcMip );

  /*
   * We realy have more than one level, so. . . 
   */
#ifdef GLIDE3
  trueColorMip.depth          = info->header.large_lod - info->header.small_lod + 1;
#else
  trueColorMip.depth          = info->header.small_lod - info->header.large_lod + 1;
#endif

  /*
   * WARNING!  I do not free srcMip.data[0] since it is passed in by the users.
   */

  /*
   * Resample the true color version of the input image to 
   * the passed in size. . . . this should be a valid
   * size for the hardware to handle.
   */
  tmpMip = trueColorMip;
  tmpMip.width = info->header.width;
  tmpMip.height = info->header.height;
  txMipAlloc( &tmpMip );

  if( ( flags & TX_CLAMP_MASK ) == TX_CLAMP_DISABLE )
    {
      txMipResample( &tmpMip, &trueColorMip );
    }
  else
    {
      txMipClamp( &tmpMip, &trueColorMip );
#if 0
      txMipView( &tmpMip, "blah", FXTRUE, 0 );
#endif
    }
    
  
#if 0
  if( _heapchk() != _HEAPOK )
    txPanic( "_heapchk failed" );
#endif
  txFree( trueColorMip.data[0] );

  trueColorMip = tmpMip;

  /*
   * Generate mipmap levels.
   */
#ifdef GLIDE3
  trueColorMip.depth          = info->header.large_lod - info->header.small_lod + 1;
#else
  trueColorMip.depth          = info->header.small_lod - info->header.large_lod + 1;
#endif
  txMipMipmap( &trueColorMip );

#if 0
  txMipView( &trueColorMip, "blah", FXTRUE, 0 );
#endif

  /*
   * Convert from true color to the output color format.
   */
  memset( &outputMip, 0, sizeof( outputMip ) );
  outputMip.format         = info->header.format;
  outputMip.width          = info->header.width;
  outputMip.height         = info->header.height;
  outputMip.depth          = trueColorMip.depth;
  outputMip.data[0]        = info->data;
#if 0
  txMipAlloc( &outputMip );
#else
  txMipSetMipPointers( &outputMip );
#endif
  
  if( ( flags & TX_TARGET_PALNCC_MASK ) == TX_TARGET_PALNCC_SOURCE )
    {
      txMipTrueToFixedPal( &outputMip, &trueColorMip, palNcc, 
                           flags & TX_FIXED_PAL_QUANT_MASK );
    }
  else
    {
      txMipQuantize( &outputMip, &trueColorMip, outputMip.format, 
                     flags & TX_DITHER_MASK, flags & TX_COMPRESSION_MASK );
    }

  info->data = outputMip.data[0];

  if( ( info->header.format == GR_TEXFMT_YIQ_422 ) ||
      ( info->header.format == GR_TEXFMT_AYIQ_8422 ) )
    {
      txPalToNcc( &info->table.nccTable, outputMip.pal );
    }
  
  if( info->header.format == GR_TEXFMT_P_8 || info->header.format == GR_TEXFMT_AP_88 )
    {
      memcpy( info->table.palette.data, outputMip.pal, sizeof( FxU32 ) * 256 );
    }

  txFree( trueColorMip.data[0] );

  return FXTRUE;
}