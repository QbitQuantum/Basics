int main(int argc, char *argv[])
{ DAZZ_DB    _db, *db = &_db;
  FILE       *hdrs = NULL;
  char       *hdrs_name = NULL;

  int         nfiles;
  char      **flist = NULL;
  int        *findx = NULL;

  int            reps, *pts;
  int            input_pts;
  File_Iterator *iter = NULL;
  FILE          *input;

  int         TRIM, UPPER;
  int         DOSEQ, DOQVS, DOARR, QUIVA, ARROW, DAM;
  int         WIDTH;

  int         MMAX, MTOP;
  char      **MASK;

  //  Process arguments

  { int  i, j, k;
    int  flags[128];
    char *eptr;

    ARG_INIT("DBshow")

    WIDTH = 80;
    MTOP  = 0;
    MMAX  = 10;
    MASK  = (char **) Malloc(MMAX*sizeof(char *),"Allocating mask track array");
    if (MASK == NULL)
      exit (1);

    j = 1;
    for (i = 1; i < argc; i++)
      if (argv[i][0] == '-')
        switch (argv[i][1])
        { default:
            ARG_FLAGS("unqaUQA")
            break;
          case 'w':
            ARG_NON_NEGATIVE(WIDTH,"Line width")
            break;
          case 'm':
            if (MTOP >= MMAX)
              { MMAX = 1.2*MTOP + 10;
                MASK = (char **) Realloc(MASK,MMAX*sizeof(char *),"Reallocating mask track array");
                if (MASK == NULL)
                  exit (1);
              }
            MASK[MTOP++] = argv[i]+2;
            break;
        }
      else
        argv[j++] = argv[i];
    argc = j;

    DAM   = 0;
    TRIM  = 1-flags['u'];
    UPPER = 1+flags['U'];
    DOQVS = flags['q'];
    DOARR = flags['a'];
    DOSEQ = 1-flags['n'];
    QUIVA = flags['Q'];
    ARROW = flags['A'];
    if ((QUIVA || DOQVS) && (ARROW || DOARR))
      { fprintf(stderr,"%s: Cannot request both Quiver (-Q,-q) and Arrow (-A,a) information\n",
                       Prog_Name);
        exit (1);
      }

    if (QUIVA)
      { DOQVS = 1;
        DOSEQ = 0;
        MTOP  = 0;
      }
    if (ARROW)
      { DOARR = 1;
        DOSEQ = 0;
        MTOP  = 0;
      }

    if (argc <= 1)
      { fprintf(stderr,"Usage: %s %s\n",Prog_Name,Usage[0]);
        fprintf(stderr,"       %*s %s\n",(int) strlen(Prog_Name),"",Usage[1]);
        fprintf(stderr,"\n");
        fprintf(stderr,"      -u: Show the untrimmed database.\n");
        fprintf(stderr,"\n");
        fprintf(stderr,"      -q: Show also the .quiva streams.\n");
        fprintf(stderr,"      -a: Show also the .arrow pulse sequences.\n");
        fprintf(stderr,"      -n: Do not show the default read DNA sequences.\n");
        fprintf(stderr,"      -m: Show mask intervals and highlight in sequence.\n");
        fprintf(stderr,"\n");
        fprintf(stderr,"      -Q: Produce a .quiva file (ignore all other options but -uU).\n");
        fprintf(stderr,"      -A: Produce a .arrow file (ignore all other options but -uw).\n");
        fprintf(stderr,"\n");
        fprintf(stderr,"      -U: Use upper case for DNA (default is lower case).\n");
        fprintf(stderr,"      -w: Print -w bp per line (default is 80).\n");
        exit (1);
      }
  }