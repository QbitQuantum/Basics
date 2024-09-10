void
JB2Dict::JB2Codec::code_record(
  int &rectype, const GP<JB2Image> &gjim, JB2Shape *xjshp, JB2Blit *jblt)
{
  GP<GBitmap> bm;
  GP<GBitmap> cbm;
  int shapeno = -1;
  int match;

  // Code record type
  code_record_type(rectype);
  
  // Pre-coding actions
  switch(rectype)
    {
    case NEW_MARK:
    case NEW_MARK_LIBRARY_ONLY:
    case NEW_MARK_IMAGE_ONLY:
    case MATCHED_REFINE:
    case MATCHED_REFINE_LIBRARY_ONLY:
    case MATCHED_REFINE_IMAGE_ONLY:
    case NON_MARK_DATA:
      {
        if(!xjshp)
        {
           G_THROW( ERR_MSG("JB2Image.bad_number") );
        }
        JB2Shape &jshp=*xjshp;
        if (!encoding) 
        {
          jshp.bits = GBitmap::create();
          jshp.parent = -1;
          if (rectype == NON_MARK_DATA)
            jshp.parent = -2;
        }
        bm = jshp.bits;
        break;
      }
    }
  // Coding actions
  switch (rectype)
    {
    case START_OF_DATA:
      {
        if(!gjim)
        {
           G_THROW( ERR_MSG("JB2Image.bad_number") );
        }
        JB2Image &jim=*gjim;
        code_image_size (jim);
        code_eventual_lossless_refinement ();
        if (! encoding)
          init_library(jim);
        break;
      }
    case NEW_MARK:
      {
        code_absolute_mark_size (*bm, 4);
        code_bitmap_directly (*bm);
        code_relative_location (jblt, bm->rows(), bm->columns() );
        break;
      }
    case NEW_MARK_LIBRARY_ONLY:
      {
        code_absolute_mark_size (*bm, 4);
        code_bitmap_directly (*bm);
        break;
      }
    case NEW_MARK_IMAGE_ONLY:
      {
        code_absolute_mark_size (*bm, 3);
        code_bitmap_directly (*bm);
        code_relative_location (jblt, bm->rows(), bm->columns() );
        break;
      }
    case MATCHED_REFINE:
      {
        if(!xjshp || !gjim)
        {
           G_THROW( ERR_MSG("JB2Image.bad_number") );
        }
        JB2Shape &jshp=*xjshp;
        JB2Image &jim=*gjim;
        match = code_match_index (jshp.parent, jim);
        cbm = jim.get_shape(jshp.parent).bits;
        LibRect &l = libinfo[match];
        code_relative_mark_size (*bm, l.right-l.left+1, l.top-l.bottom+1, 4); 
        code_bitmap_by_cross_coding (*bm, cbm, match);
        code_relative_location (jblt, bm->rows(), bm->columns() );
        break;
      }
    case MATCHED_REFINE_LIBRARY_ONLY:
      {
        if(!xjshp||!gjim)
        {
           G_THROW( ERR_MSG("JB2Image.bad_number") );
        }
        JB2Image &jim=*gjim;
        JB2Shape &jshp=*xjshp;
        match = code_match_index (jshp.parent, jim);
        cbm = jim.get_shape(jshp.parent).bits;
        LibRect &l = libinfo[match];
        code_relative_mark_size (*bm, l.right-l.left+1, l.top-l.bottom+1, 4);
        break;
      }
    case MATCHED_REFINE_IMAGE_ONLY:
      {
        if(!xjshp||!gjim)
        {
           G_THROW( ERR_MSG("JB2Image.bad_number") );
        }
        JB2Image &jim=*gjim;
        JB2Shape &jshp=*xjshp;
        match = code_match_index (jshp.parent, jim);
        cbm = jim.get_shape(jshp.parent).bits;
        LibRect &l = libinfo[match];
        code_relative_mark_size (*bm, l.right-l.left+1, l.top-l.bottom+1, 4);
        code_bitmap_by_cross_coding (*bm, cbm, match);
        code_relative_location (jblt, bm->rows(), bm->columns() );
        break;
      }
    case MATCHED_COPY:
      {
        int temp;
        if (encoding) temp = jblt->shapeno;
        if(!gjim)
        {
           G_THROW( ERR_MSG("JB2Image.bad_number") );
        }
        JB2Image &jim=*gjim;
        match = code_match_index (temp, jim);
        if (!encoding) jblt->shapeno = temp;
        bm = jim.get_shape(jblt->shapeno).bits;
        LibRect &l = libinfo[match];
        jblt->left += l.left;
        jblt->bottom += l.bottom;
        if (jim.reproduce_old_bug)
          code_relative_location (jblt, bm->rows(), bm->columns() );
        else
          code_relative_location (jblt, l.top-l.bottom+1, l.right-l.left+1 );
        jblt->left -= l.left;
        jblt->bottom -= l.bottom; 
        break;
      }
    case NON_MARK_DATA:
      {
        code_absolute_mark_size (*bm, 3);
        code_bitmap_directly (*bm);
        code_absolute_location (jblt, bm->rows(), bm->columns() );
        break;
      }
    case PRESERVED_COMMENT:
      {
        if(!gjim)
        {
           G_THROW( ERR_MSG("JB2Image.bad_number") );
        }
        JB2Image &jim=*gjim;
        code_comment(jim.comment);
        break;
      }
    case REQUIRED_DICT_OR_RESET:
      {
        if(!gjim)
        {
           G_THROW( ERR_MSG("JB2Image.bad_number") );
        }
        JB2Image &jim=*gjim;
        if (! gotstartrecordp)
	  // Indicates need for a shape dictionary
	  code_inherited_shape_count(jim);
	else
	  // Reset all numerical contexts to zero
	  reset_numcoder();
        break;
      }
    case END_OF_DATA:
      {
        break;
      }
    default:
      {
        G_THROW( ERR_MSG("JB2Image.unknown_type") );
      }
    }
  
  // Post-coding action
  if (!encoding)
    {
      // add shape to image
      switch(rectype)
        {
        case NEW_MARK:
        case NEW_MARK_LIBRARY_ONLY:
        case NEW_MARK_IMAGE_ONLY:
        case MATCHED_REFINE:
        case MATCHED_REFINE_LIBRARY_ONLY:
        case MATCHED_REFINE_IMAGE_ONLY:
        case NON_MARK_DATA:
          {
            if(!xjshp||!gjim)
            {
              G_THROW( ERR_MSG("JB2Image.bad_number") );
            }
            JB2Shape &jshp=*xjshp;
            shapeno = gjim->add_shape(jshp);
            shape2lib.touch(shapeno);
            shape2lib[shapeno] = -1;
            break;
          }
        }
      // add shape to library
      switch(rectype)
        {
        case NEW_MARK:
        case NEW_MARK_LIBRARY_ONLY:
        case MATCHED_REFINE:
        case MATCHED_REFINE_LIBRARY_ONLY:
          if(!xjshp)
          {
            G_THROW( ERR_MSG("JB2Image.bad_number") );
          }
          add_library(shapeno, *xjshp);
          break;
        }
      // make sure everything is compacted
      // decompaction will occur automatically on cross-coding bitmaps
      if (bm)
        bm->compress();
      // add blit to image
      switch (rectype)
        {
        case NEW_MARK:
        case NEW_MARK_IMAGE_ONLY:
        case MATCHED_REFINE:
        case MATCHED_REFINE_IMAGE_ONLY:
        case NON_MARK_DATA:
          jblt->shapeno = shapeno;
        case MATCHED_COPY:
          if(!gjim)
          {
            G_THROW( ERR_MSG("JB2Image.bad_number") );
          }
          gjim->add_blit(* jblt);
          break;
        }
    }
}