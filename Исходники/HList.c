         frcDisc = TRUE; break;

      case 'e':

         gen = GetChkedLong(gst,LONG_MAX,s); break;

      case 'h':

         srcHdr = TRUE; break;

      case 'i':

         nItems = GetChkedInt(1,100,s); break;

      case 'n':

         numS = GetChkedInt(1,SMAX-1,s); break;

      case 'o':

         obsFmt = TRUE; break;

      case 'p':

         replay = TRUE; break;

      case 'r':

         rawOut = TRUE; break;

      case 's':

         gst = GetChkedLong(0,LONG_MAX,s); break;

      case 't':

         tgtHdr = TRUE; break;

      case 'z':

         prData = FALSE; break;

      case 'F':

         if (NextArg() != STRINGARG)