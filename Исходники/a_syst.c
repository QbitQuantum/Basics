static int msc_system (const char *s)

        {
        char *par[10];
        int   i = 0;
        char *p = (char *)b_cm__;

        (void)strcpy(p,s);

        while (*p==' ') p++;                    /* skip leading blanks */
        while (*p!='\0')
           {
           par[i++] = p;
           while (*p!=' ' && *p!='\0') p++;     /* search next blank */
           if (*p==' ')
              {
              *p = '\0';                        /* store null char */
              p++;
              while (*p==' ') p++;              /* skip leading blanks */
              }
           }
        par [i] = NULL ;

        return  spawnvp (P_WAIT, par[0],par ) ;
        }