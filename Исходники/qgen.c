/*
 * FUNCTION qsub(char *qtag, int flags)
 *
 * based on the settings of flags, and the template file $QDIR/qtag.sql
 * make the following substitutions to turn a query template into EQT
 *
 *  String      Converted to            Based on
 *  ======      ============            ===========
 *  first line  database <db_name>;      -n from command line
 *  second line set explain on;         -x from command line
 *   :<number>  parameter <number>
 *  :k          set number
 *  :o          output to outpath/qnum.snum    
 *                                      -o from command line, SET_OUTPUT
 *  :s          stream number
 *  :b          BEGIN WORK;             -a from command line, START_TRAN
 *  :e          COMMIT WORK;            -a from command line, END_TRAN
 *  :q          query number
 *  :n<number>                          sets rowcount to be returned
 */
void
qsub(char *qtag, int flags)
{
static char *line = NULL,
    *qpath = NULL;
FILE *qfp;
char *cptr,
    *mark,
    *qroot = NULL;

    qnum = atoi(qtag);
    if (line == NULL)
        {
        line = malloc(BUFSIZ);
        qpath = malloc(BUFSIZ);
        MALLOC_CHECK(line);
        MALLOC_CHECK(qpath);
        }

    qroot = env_config(QDIR_TAG, QDIR_DFLT);
    sprintf(qpath, "%s%c%s.sql", 
		qroot, PATH_SEP, qtag);
    qfp = fopen(qpath, "r");
    OPEN_CHECK(qfp, qpath);

    rowcnt = rowcnt_dflt[qnum];
    varsub(qnum, 0, flags); /* set the variables */
    if (flags & DFLT_NUM)
        fprintf(ofp, SET_ROWCOUNT, rowcnt);
    while (fgets(line, BUFSIZ, qfp) != NULL)
        {
        if (!(flags & COMMENT))
            strip_comments(line);
        mark = line;
        while ((cptr = strchr(mark, VTAG)) != NULL)
            {
            *cptr = '\0';
             cptr++;
            fprintf(ofp,"%s", mark);
            switch(*cptr)
                {
                case 'b':
                case 'B':
                    if (!(flags & ANSI))
                        fprintf(ofp,"%s\n", START_TRAN);
                    cptr++;
                    break;
                case 'c':
                case 'C':
                    if (flags & DBASE)
                        fprintf(ofp, SET_DBASE, db_name);
                    cptr++;
                    break;
                case 'e':
                case 'E':
                    if (!(flags & ANSI))
                        fprintf(ofp,"%s\n", END_TRAN);
                    cptr++;
                    break;
                case 'n':
                case 'N':
                    if (!(flags & DFLT_NUM))
                        {
                        rowcnt=atoi(++cptr);
                        while (isdigit(*cptr) || *cptr == ' ') cptr++;
                        fprintf(ofp, SET_ROWCOUNT, rowcnt);
                        }
                    continue;
                case 'o':
                case 'O':
                    if (flags & OUTPUT)
                        fprintf(ofp,"%s '%s/%s.%d'", SET_OUTPUT, osuff, 
                            qtag, (snum < 0)?0:snum);
                    cptr++;
                    break;
                case 'q':
                case 'Q':
                    fprintf(ofp,"%s", qtag);
                    cptr++;
                    break;
                case 's':
                case 'S':
                    fprintf(ofp,"%d", (snum < 0)?0:snum);
                    cptr++;
                    break;
                case 'X':
                case 'x':
                    if (flags & EXPLAIN)
                        fprintf(ofp, "%s\n", GEN_QUERY_PLAN);
                    cptr++;
                    break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
                    varsub(qnum, atoi(cptr), flags & DFLT);
                    while (isdigit(*++cptr));
                    break;
                default:
		    fprintf(stderr, "-- unknown flag '%c%c' ignored\n", 
                        VTAG, *cptr);
		    cptr++;
		    break;
                }
            mark=cptr;
            }
        fprintf(ofp,"%s", mark);
        }
    fclose(qfp);
    fflush(stdout);
    return;
}