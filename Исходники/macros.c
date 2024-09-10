Bool stop_macro_definition(PCL5Context *pcl5_ctxt, MacroInfo *macro_info)
{
  PCL5MacroStorage *macro ;
  uint8 ch ;
  int32 byte ;
  Bool found_1 = FALSE ;
  FILELIST *filter;

  UNUSED_PARAM(MacroInfo *, macro_info) ;

  HQASSERT(pcl5_ctxt != NULL, "pcl5_ctxt is NULL") ;
  HQASSERT(macro_info != NULL, "macro_info is NULL") ;

  /* If we are not recording a macro, ignore this command and move
     on. */
  if (! pcl5_recording_a_macro)
    return TRUE ;

  HQASSERT(macro_being_defined != NULL, "macro_being_defined is NULL") ;

#ifdef ASSERT_BUILD
  if (is_string_macro(macro_info, FALSE)) {
    uint8 *string ;
    int32 length ;
    string = macro_info->macro_string_id.buf ;
    length = macro_info->macro_string_id.length ;

    HQASSERT((macro_being_defined->detail.string_id.length == length &&
              HqMemCmp(macro_being_defined->detail.string_id.buf,
                       macro_being_defined->detail.string_id.length,
                       string, length) == 0),
             "macro_being_defined is invalid") ;
  }
  else {
    pcl5_resource_numeric_id macro_numeric_id = macro_info->macro_numeric_id ;
    HQASSERT(macro_being_defined->detail.numeric_id == macro_numeric_id,
             "macro_being_defined is invalid") ;
  }
#endif

  /* We would have recorded this command as part of the macro, so remove it.
   * ESC & f 1 X, ESC & f -1.5 X, or similar.
   *
   * N.B. It may be that we don't really need to remove this at all, and
   *      would manage to ignore it OK while running the macro, though
   *      it is perhaps neater to get rid of it.
   */
  macro = macro_being_defined->detail.private_data ;
  HQASSERT(macro != NULL, "macro is NULL") ;

  while (macro->total_bytes > 0) {
    /* N.B. It is not necessarily safe to look at the byte at write_pos,
     *      but should be OK to look at the one before.
     */
    ch = *(macro->write_pos - 1) ;

    if (ch == '1')
      found_1 = TRUE ;
    else if (found_1 && is_group_char(ch) && ch != 'f') {
      /* The parameter or group character is not 'f', so we must have a
       * combined escape sequence, such as ESC & f 1 s 1 X, which we need
       * to leave as ESC & f 1 s
       */
      break ;
    }

    pop_macro_byte(pcl5_ctxt) ;

    if (ch == ESCAPE)
      break ;
  }

  filter = pcl5_ctxt->flptr ;
  pcl5_ctxt->flptr = theIUnderFile(pcl5_ctxt->flptr) ;
  byte = 0 ;

  /* This is a real hack. We know that the buffer size on the macro
     recording filter is 1 byte in length and we always read one byte
     ahead (within filters) so that an UnGetc() can be done
     efficiently. Hence we need to always do an UnGetc() on the
     underlying file as the macro recording filter has consumed one
     byte too many (from its underlying file). Note that byte is not
     actually used by UnGetc() so we don't care what it is. We just
     set it to zero. */
  UnGetc(byte, pcl5_ctxt->flptr) ;

  /* This is where any finalisation on storing the macro should go. */

  pcl5_recording_a_macro = FALSE ;
  macro_being_defined = NULL ;

  SetIClosingFlag( filter ) ;
  (*theIMyDisposeFile(filter))(filter) ;
  ClearIClosingFlag( filter ) ;
  SetIEofFlag( filter ) ;

  return TRUE ;
}