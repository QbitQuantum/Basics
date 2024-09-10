bool
XFace::CreateXpm(char ***xpm)
{
#ifndef HAVE_COMPFACE_H
   return false;
#else
   int
      l,c,q;
   char
      *ptr, *buf, *token;
   int
      line = 0;
   String
      tmp;

   *xpm = (char **) malloc(sizeof(char *)*52);

   buf = strutil_strdup(data);
   ptr = buf;

   (*xpm)[line++] = strutil_strdup(" 48 48 2 1");
   (*xpm)[line++] = strutil_strdup("# c #000000");
   (*xpm)[line++] = strutil_strdup(". c #ffffff");
   for(l = 0; l < 48; l++)
   {
      tmp = wxEmptyString;
      for(c = 0; c < 3; c++)
      {
         token = strutil_strsep(&ptr,",\n\r");
         if(strlen(token) == 0)
            token = strutil_strsep(&ptr, ",\n\r");  // skip end of line
         if(token)
         {
            token += 2;  // skip  0x
            for(q = 0; q < 4; q++)
            {
               switch(token[q])
               {
                  case '0':
                     tmp += _T("...."); break;
                  case '1':
                     tmp += _T("...#"); break;
                  case '2':
                     tmp += _T("..#."); break;
                  case '3':
                     tmp += _T("..##"); break;
                  case '4':
                     tmp += _T(".#.."); break;
                  case '5':
                     tmp += _T(".#.#"); break;
                  case '6':
                     tmp += _T(".##."); break;
                  case '7':
                     tmp += _T(".###"); break;
                  case '8':
                     tmp += _T("#..."); break;
                  case '9':
                     tmp += _T("#..#"); break;
                  case 'a': case 'A':
                     tmp += _T("#.#."); break;
                  case 'b': case 'B':
                     tmp += _T("#.##"); break;
                  case 'c': case 'C':
                     tmp += _T("##.."); break;
                  case 'd': case 'D':
                     tmp += _T("##.#"); break;
                  case 'e': case 'E':
                     tmp += _T("###."); break;
                  case 'f': case 'F':
                     tmp += _T("####"); break;
                  default:
                     break;
               }
            }

         }
      }
      (*xpm)[line++] = strutil_strdup(tmp.ToAscii());
   }
   delete [] buf;
   (*xpm)[line++] = NULL;
   return true;
#endif
}