  static FT_Error
  ftc_sbit_node_load( FTC_SBitNode    snode,
                      FTC_Manager     manager,
                      FTC_SBitFamily  sfam,
                      FT_UInt         gindex,
                      FT_ULong       *asize )
  {
    FT_Error       error;
    FTC_GlyphNode  gnode = FTC_GLYPH_NODE( snode );
    FT_Memory      memory;
    FT_Face        face;
    FT_Size        size;
    FTC_SBit       sbit;


    if ( gindex <  (FT_UInt)gnode->item_start                     ||
         gindex >= (FT_UInt)gnode->item_start + gnode->item_count )
    {
      FT_ERROR(( "ftc_sbit_node_load: invalid glyph index" ));
      return FTC_Err_Invalid_Argument;
    }

    memory = manager->library->memory;

    sbit = snode->sbits + ( gindex - gnode->item_start );

    error = FTC_Manager_Lookup_Size( manager, &sfam->type.font,
                                     &face, &size );
    if ( !error )
    {
      /* by default, indicates a `missing' glyph */
      sbit->buffer = 0;

      error = FT_Load_Glyph( face, gindex, sfam->type.flags | FT_LOAD_RENDER );
      if ( !error )
      {
        FT_Int        temp;
        FT_GlyphSlot  slot   = face->glyph;
        FT_Bitmap*    bitmap = &slot->bitmap;
        FT_Int        xadvance, yadvance;


        /* check that our values fit into 8-bit containers!       */
        /* If this is not the case, our bitmap is too large       */
        /* and we will leave it as `missing' with sbit.buffer = 0 */

#define CHECK_CHAR( d )  ( temp = (FT_Char)d, temp == d )
#define CHECK_BYTE( d )  ( temp = (FT_Byte)d, temp == d )

        /* XXX: FIXME: add support for vertical layouts maybe */

        /* horizontal advance in pixels */
        xadvance = ( slot->metrics.horiAdvance + 32 ) >> 6;
        yadvance = ( slot->metrics.vertAdvance + 32 ) >> 6;

        if ( CHECK_BYTE( bitmap->rows  )     &&
             CHECK_BYTE( bitmap->width )     &&
             CHECK_CHAR( bitmap->pitch )     &&
             CHECK_CHAR( slot->bitmap_left ) &&
             CHECK_CHAR( slot->bitmap_top  ) &&
             CHECK_CHAR( xadvance )          &&
             CHECK_CHAR( yadvance )          )
        {
          sbit->width     = (FT_Byte)bitmap->width;
          sbit->height    = (FT_Byte)bitmap->rows;
          sbit->pitch     = (FT_Char)bitmap->pitch;
          sbit->left      = (FT_Char)slot->bitmap_left;
          sbit->top       = (FT_Char)slot->bitmap_top;
          sbit->xadvance  = (FT_Char)xadvance;
          sbit->yadvance  = (FT_Char)yadvance;
          sbit->format    = (FT_Byte)bitmap->pixel_mode;
          sbit->max_grays = (FT_Byte)(bitmap->num_grays - 1);

#if 0 /* this doesn't work well with embedded bitmaps */

          /* grab the bitmap when possible - this is a hack! */
          if ( slot->internal->flags & FT_GLYPH_OWN_BITMAP )
          {
            slot->internal->flags &= ~FT_GLYPH_OWN_BITMAP;
            sbit->buffer           = bitmap->buffer;
          }
          else
#endif
          {
            /* copy the bitmap into a new buffer -- ignore error */
            error = ftc_sbit_copy_bitmap( sbit, bitmap, memory );
          }

          /* now, compute size */
          if ( asize )
            *asize = ABS( sbit->pitch ) * sbit->height;

        }  /* glyph dimensions ok */

      } /* glyph loading successful */