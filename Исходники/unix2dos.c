/* converts stream ipInF to DOS format text and write to stream ipOutF
 * RetVal: 0  if success
 *         -1  otherwise
 */
int ConvertUnixToDos(FILE* ipInF, FILE* ipOutF, CFlag *ipFlag)
{
    int RetVal = 0;
    int TempChar;
    int PreviousChar = 0;

    ipFlag->status = 0;

    /* LF    -> CR-LF */
    /* CR-LF -> CR-LF, in case the input file is a DOS text file */
    /* \x0a = Newline/Line Feed (LF) */
    /* \x0d = Carriage Return (CR) */

    switch (ipFlag->ConvMode)
    {
      case 0: /* ascii */
        while ((TempChar = getc(ipInF)) != EOF) {  /* get character */
          if ((ipFlag->Force == 0) &&
              (TempChar < 32) &&
              (TempChar != '\x0a') &&  /* Not an LF */
              (TempChar != '\x0d') &&  /* Not a CR */
              (TempChar != '\x09')) {  /* Not a TAB */
            RetVal = -1;
            ipFlag->status |= BINARY_FILE ;
            break;
          }
          if (TempChar == '\x0a')
	  {
            putc('\x0d', ipOutF); /* got LF, put CR */
	  } else {
             if (TempChar == '\x0d') /* got CR */
	     {
               if ((TempChar = getc(ipInF)) == EOF) /* get next char */
                 TempChar = '\x0d';  /* Read error, or end of file. */
	       else
	       {
                 putc('\x0d', ipOutF); /* put CR */
                 PreviousChar = '\x0d';
	       }
	     }
	  }
          if (putc(U2DAsciiTable[TempChar], ipOutF) == EOF)
          {
              RetVal = -1;
              if (!ipFlag->Quiet)
                fprintf(stderr, _("unix2dos: can not write to output file\n"));
              break;
          } else {
            AddDOSNewLine( ipInF, ipOutF, ipFlag, TempChar, PreviousChar);
          }
          PreviousChar = TempChar;
        }
        break;
      case 1: /* 7bit */
        while ((TempChar = getc(ipInF)) != EOF) {
          if ((ipFlag->Force == 0) &&
              (TempChar < 32) &&
              (TempChar != '\x0a') &&  /* Not an LF */
              (TempChar != '\x0d') &&  /* Not a CR */
              (TempChar != '\x09')) {  /* Not a TAB */
            RetVal = -1;
            ipFlag->status |= BINARY_FILE ;
            break;
          }
          if (TempChar == '\x0a')
	  {
            putc('\x0d', ipOutF); /* got LF, put CR */
	  } else {
             if (TempChar == '\x0d') /* got CR */
	     {
               if ((TempChar = getc(ipInF)) == EOF) /* get next char */
                 TempChar = '\x0d';  /* Read error, or end of file. */
	       else
	       {
                 putc('\x0d', ipOutF); /* put CR */
                 PreviousChar = '\x0d';
	       }
	     }
	  }
          if (putc(U2D7BitTable[TempChar], ipOutF) == EOF)
          {
              RetVal = -1;
              if (!ipFlag->Quiet)
                fprintf(stderr, _("unix2dos: can not write to output file\n"));
              break;
          } else {
            AddDOSNewLine( ipInF, ipOutF, ipFlag, TempChar, PreviousChar);
          }
          PreviousChar = TempChar;
        }
        break;
      case 2: /* iso */
        while ((TempChar = getc(ipInF)) != EOF) {
          if ((ipFlag->Force == 0) &&
              (TempChar < 32) &&
              (TempChar != '\x0a') &&  /* Not an LF */
              (TempChar != '\x0d') &&  /* Not a CR */
              (TempChar != '\x09')) {  /* Not a TAB */
            RetVal = -1;
            ipFlag->status |= BINARY_FILE ;
            break;
          }
          if (TempChar == '\x0a')
	  {
            putc('\x0d', ipOutF); /* got LF, put CR */
	  } else {
             if (TempChar == '\x0d') /* got CR */
	     {
               if ((TempChar = getc(ipInF)) == EOF) /* get next char */
                 TempChar = '\x0d';  /* Read error, or end of file. */
	       else
	       {
                 putc('\x0d', ipOutF); /* put CR */
                 PreviousChar = '\x0d';
	       }
	     }
	  }
          if (putc(U2DIsoTable[TempChar], ipOutF) == EOF)
          {
              RetVal = -1;
              if (!ipFlag->Quiet)
                fprintf(stderr, _("unix2dos: can not write to output file\n"));
              break;
          } else {
            AddDOSNewLine( ipInF, ipOutF, ipFlag, TempChar, PreviousChar);
          }
          PreviousChar = TempChar;
        }
        break;
      case 3: /* Mac */
        while ((TempChar = getc(ipInF)) != EOF) {
          if ((ipFlag->Force == 0) &&
              (TempChar < 32) &&
              (TempChar != '\x0a') &&  /* Not an LF */
              (TempChar != '\x0d') &&  /* Not a CR */
              (TempChar != '\x09')) {  /* Not a TAB */
            RetVal = -1;
            ipFlag->status |= BINARY_FILE ;
            break;
          }
          if ((TempChar != '\x0a')) /* Not an LF */
            {
              if(putc(U2DAsciiTable[TempChar], ipOutF) == EOF){
                RetVal = -1;
                if (!ipFlag->Quiet)
                  fprintf(stderr, _("unix2dos: can not write to output file\n"));
                break;
              }
              PreviousChar = TempChar;
            }
          else{
            /* TempChar is an LF */
            /* Don't touch this delimiter if it's a CR,LF pair. */
            if ( PreviousChar == '\x0d' ) {
              if (putc('\x0a', ipOutF) == EOF)  /* CR,LF pair. Put LF */
                {
                  RetVal = -1;
                  if (!ipFlag->Quiet)
                    fprintf(stderr, _("unix2dos: can not write to output file\n"));
                  break;
                }
              PreviousChar = TempChar;
              continue;
            }
            PreviousChar = TempChar;
            if (putc('\x0d', ipOutF) == EOF) /* Unix line end (LF). Put CR */
              {
                RetVal = -1;
                if (!ipFlag->Quiet)
                  fprintf(stderr, _("unix2dos: can not write to output file\n"));
                break;
              }
            if (ipFlag->NewLine) {  /* add additional CR? */
              putc('\x0d', ipOutF);
            }
          }
        }
        break;
      default: /* unknown convmode */
      ;
#ifdef DEBUG
      fprintf(stderr, _("unix2dos: program error, invalid conversion mode %d\n"),ipFlag->ConvMode);
      exit(1);
#endif
    }
    return RetVal;
}