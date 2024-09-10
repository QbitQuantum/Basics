/**
 * This routine gets characters from the filter's underlying file, and
 * decodes them according to the runlength scheme. It returns the number
 * of bytes placed into the filter's buffer through the ret_bytes arguments.
 * This number is negative if the EOD is found.
 * It returns FALSE if anything goes wrong. The caller is responsible for
 * setting the IOERROR condition.
 *
 * \param[in,out]  filter       Input and output streams for the filter
 * \param[out]     ret_bytes    Number of bytes placed in output buffer
 *                              (negative if EOD found)
 * \return                      Success status
 */
static Bool runlengthDecodeBuffer(FILELIST *filter, int32 *ret_bytes)
{
  int32    count, length;
  FILELIST *uflptr;
  uint8    *ptr;

  HQASSERT(filter, "NULL /RunLengthDecode filter");

  uflptr = filter->underlying_file;
  ptr = filter->buffer;

  HQASSERT(uflptr, "NULL /RunLengthDecode input buffer");
  HQASSERT(ptr, "NULL /RunLengthDecode output buffer");

  count = 0;
  for (;;)
  {
    register int32 ch = Getc(uflptr);

    if ( ch == EOF || ch == EOD )
    {
      /* found the EOD marker, or EOF on underlying file */
      count = -count;
      break;
    }
    if ( ch < 128 ) /* ch + 1 bytes to follow */
    {
      length = ch + 1;
      if ( ( count + length ) <= filter->buffersize )
      {
        count += length;
        /* If buffer is full enough avoid Getc() loop overhead */
        if ( length < uflptr->count )
        {
          HqMemCpy(ptr, uflptr->ptr, length);
          uflptr->count -= length;
          uflptr->ptr   += length;
          ptr += length;
        }
        else
        {
          while ( length-- )
          {
            if ( (ch = Getc(uflptr)) == EOF )
              return error_handler(IOERROR);
            *ptr++ = (uint8)ch;
          }
        }
      }
      else /* current run will not fit in */
      {
        UnGetc(ch, uflptr);
        break;
      }
    }
    else /* ch > 128, replicate single byte */
    {
      length = 257 - ch;
      if ( ( count + length ) <= filter->buffersize )
      {
        if (( ch = Getc( uflptr )) == EOF )
          return error_handler(IOERROR);
        count += length;
        HqMemSet8(ptr, (uint8)ch, length);
        ptr += length;
      }
      else /* current replciation will not fit into buffer */
      {
        UnGetc(ch , uflptr);
        break;
      }
    }
  }
  *ret_bytes = count;
  return TRUE;
}