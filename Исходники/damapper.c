int main(int argc, char *argv[])
{ DAZZ_DB    _ablock, _bblock;
  DAZZ_DB    *ablock = &_ablock, *bblock = &_bblock;
  char       *afile,  *bfile;
  char       *aroot,  *broot, *apwd;
  void       *aindex, *bindex;
  int         alen,    blen;
  int         isdam, nblocks;   //  of reference (a-argument)
  int         mflag;
  char       *command;

  Align_Spec *settings;

  int    COVER, NOMAP;
  int    KMER_LEN;
  int    MAX_REPS;
  double AVE_ERROR;
  int    NTHREADS;
  int    MAP_ORDER;
  int    MMAX, MTOP, *MSTAT;
  char **MASK;

  { int    i, j, k;
    int    flags[128];
    char  *eptr;
    DIR   *dirp;

    ARG_INIT("damapper")

    KMER_LEN  = 20;
    MAX_REPS  = 0;
    AVE_ERROR = .85;
    SPACING   = 100;       //   Globally visible to map.c
    BEST_TIE  = 1.0;
    NTHREADS  = 4;
    SORT_PATH = "/tmp";

    MEM_PHYSICAL = getMemorySize();
    MEM_LIMIT    = MEM_PHYSICAL;
    if (MEM_PHYSICAL == 0)
      { fprintf(stderr,"\nWarning: Could not get physical memory size\n");
        fflush(stderr);
      }

    MTOP  = 0;
    MMAX  = 10;
    MASK  = (char **) Malloc(MMAX*sizeof(char *),"Allocating mask track array");
    MSTAT = (int *) Malloc(MMAX*sizeof(int),"Allocating mask status array");
    if (MASK == NULL || MSTAT == NULL)
      exit (1);

    j = 1;
    for (i = 1; i < argc; i++)
      if (argv[i][0] == '-')
        switch (argv[i][1])
        { default:
            ARG_FLAGS("vbpzCN")
            break;
          case 'e':
            ARG_REAL(AVE_ERROR)
            if (AVE_ERROR < .7 || AVE_ERROR >= 1.)
              { fprintf(stderr,"%s: Average correlation must be in [.7,1.) (%g)\n",
                               Prog_Name,AVE_ERROR);
                exit (1);
              }
            break;
          case 'k':
            ARG_POSITIVE(KMER_LEN,"K-mer length")
            if (KMER_LEN > 32)
              { fprintf(stderr,"%s: K-mer length must be 32 or less\n",Prog_Name);
                exit (1);
              }
            break;
          case 'm':
            if (MTOP >= MMAX)
              { MMAX  = 1.2*MTOP + 10;
                MASK  = (char **) Realloc(MASK,MMAX*sizeof(char *),"Reallocating mask track array");
                MSTAT = (int *) Realloc(MSTAT,MMAX*sizeof(int),"Reallocating mask status array");
                if (MASK == NULL || MSTAT == NULL)
                  exit (1);
              }
            MASK[MTOP++] = argv[i]+2;
            break;
          case 'n':
            ARG_REAL(BEST_TIE)
            if (BEST_TIE < .7 || BEST_TIE > 1.)
              { fprintf(stderr,"%s: Near optimal threshold must be in [.7,1.] (%g)\n",
                               Prog_Name,BEST_TIE);
                exit (1);
              }
            break;
          case 's':
            ARG_POSITIVE(SPACING,"Trace spacing")
            break;
          case 't':
            ARG_POSITIVE(MAX_REPS,"Tuple supression frequency")
            break;
          case 'M':
            { int limit;

              ARG_NON_NEGATIVE(limit,"Memory allocation (in Gb)")
              MEM_LIMIT = limit * 0x40000000ll;
              break;
            }
          case 'P':
            SORT_PATH = argv[i]+2;
            if ((dirp = opendir(SORT_PATH)) == NULL)
              { fprintf(stderr,"%s: -P option: cannot open directory %s\n",Prog_Name,SORT_PATH);
                exit (1);
              }
            closedir(dirp);
            break;
          case 'T':
            ARG_POSITIVE(NTHREADS,"Number of threads")
            break;
        }
      else
        argv[j++] = argv[i];
    argc = j;

    VERBOSE   = flags['v'];   //  Globally declared in map.h
    BIASED    = flags['b'];
    PROFILE   = flags['p'];
    COVER     = flags['C'];
    NOMAP     = flags['N'];
    MAP_ORDER = 1-flags['z'];

    if (argc <= 2)
      { fprintf(stderr,"Usage: %s %s\n",Prog_Name,Usage[0]);
        fprintf(stderr,"       %*s %s\n",(int) strlen(Prog_Name),"",Usage[1]);
        fprintf(stderr,"       %*s %s\n",(int) strlen(Prog_Name),"",Usage[2]);
        fprintf(stderr,"\n");
        fprintf(stderr,"      -k: k-mer size (must be <= 32).\n");
        fprintf(stderr,"      -t: Ignore k-mers that occur >= -t times in a block.\n");
        fprintf(stderr,"      -M: Use only -M GB of memory by ignoring most frequent k-mers.\n");
        fprintf(stderr,"\n");
        fprintf(stderr,"      -e: Look for alignments with -e percent similarity.\n");
        fprintf(stderr,"      -s: Use -s as the trace point spacing for encoding alignments.\n");
        fprintf(stderr,"      -n: Output all matches within this %% of the best\n");
        fprintf(stderr,"\n");
        fprintf(stderr,"      -T: Use -T threads.\n");
        fprintf(stderr,"      -P: Do sorts and merges in directory -P.\n");
        fprintf(stderr,"      -m: Soft mask the blocks with the specified mask.\n");
        fprintf(stderr,"      -b: For AT/GC biased data, compensate k-mer counts (deprecated).\n");
        fprintf(stderr,"\n");
        fprintf(stderr,"      -v: Verbose mode, output statistics as proceed.\n");
        fprintf(stderr,"      -z: sort .las by A,B-read pairs (overlap piles)\n");
        fprintf(stderr,"          off => sort .las by A-read,A-position pairs");
        fprintf(stderr," (default for mapping)\n");
        fprintf(stderr,"      -p: Output repeat profile track\n");
        fprintf(stderr,"      -C: Output reference vs reads .las.\n");
        fprintf(stderr,"      -N: Do not output reads vs reference .las.\n");
        exit (1);
      }

    if (COVER)
      if (NOMAP)
        mflag = FLAG_DOB;
      else
        mflag = FLAG_DOA | FLAG_DOB;
    else
      if (NOMAP)
        { fprintf(stderr,"%s: Cannot specify both C and N flags together\n",Prog_Name);
          exit (1);
        }
      else
        mflag = FLAG_DOA;

    if (NOMAP && PROFILE)
      { fprintf(stderr,"%s: Cannot specify both N and p flags together\n",Prog_Name);
        exit (1);
      }

    for (j = 0; j < MTOP; j++)
      MSTAT[j] = -2;
  }