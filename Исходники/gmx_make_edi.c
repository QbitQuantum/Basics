int sscan_list(int *list[], const char *str, const char *listname)
{
    /*this routine scans a string of the form 1,3-6,9 and returns the
       selected numbers (in this case 1 3 4 5 6 9) in NULL-terminated array of integers.
       memory for this list will be allocated  in this routine -- sscan_list expects *list to
       be a NULL-Pointer

       listname is a string used in the errormessage*/


    int   i, istep;
    char  c;
    char *pos, *startpos, *step;
    int   n = strlen(str);

    /*enums to define the different lexical stati */
    enum {
        sBefore, sNumber, sMinus, sRange, sZero, sSmaller, sError, sSteppedRange
    };

    int   status     = sBefore; /*status of the deterministic automat to scan str   */
    int   number     = 0;
    int   end_number = 0;

    char *start = NULL; /*holds the string of the number behind a ','*/
    char *end   = NULL; /*holds the string of the number behind a '-' */

    int   nvecs = 0;    /* counts the number of vectors in the list*/

    step = NULL;
    snew(pos, n+4);
    startpos = pos;
    strcpy(pos, str);
    pos[n]   = ',';
    pos[n+1] = '1';
    pos[n+2] = '\0';

    *list = NULL;

    while ((c = *pos) != 0)
    {
        switch (status)
        {
            /* expect a number */
            case sBefore: if (isdigit(c))
                {
                    start  = pos;
                    status = sNumber;
                    break;
                }
                else
                {
                    status = sError;
                } break;

            /* have read a number, expect ',' or '-' */
            case sNumber: if (c == ',')
                {
                    /*store number*/
                    srenew(*list, nvecs+1);
                    (*list)[nvecs++] = number = strtol(start, NULL, 10);
                    status           = sBefore;
                    if (number == 0)
                    {
                        status = sZero;
                    }
                    break;
                }
                else if (c == '-')
                {
                    status = sMinus; break;
                }
                else if (isdigit(c))
                {
                    break;
                }
                else
                {
                    status = sError;
                } break;

            /* have read a '-' -> expect a number */
            case sMinus:
                if (isdigit(c))
                {
                    end    = pos;
                    status = sRange; break;
                }
                else
                {
                    status = sError;
                } break;

            case sSteppedRange:
                if (isdigit(c))
                {
                    if (step)
                    {
                        status = sError; break;
                    }
                    else
                    {
                        step = pos;
                    }
                    status = sRange;
                    break;
                }
                else
                {
                    status = sError;
                } break;

            /* have read the number after a minus, expect ',' or ':' */
            case sRange:
                if (c == ',')
                {
                    /*store numbers*/
                    end_number = strtol(end, NULL, 10);
                    number     = strtol(start, NULL, 10);
                    status     = sBefore;
                    if (number == 0)
                    {
                        status = sZero; break;
                    }
                    if (end_number <= number)
                    {
                        status = sSmaller; break;
                    }
                    srenew(*list, nvecs+end_number-number+1);
                    if (step)
                    {
                        istep = strtol(step, NULL, 10);
                        step  = NULL;
                    }
                    else
                    {
                        istep = 1;
                    }
                    for (i = number; i <= end_number; i += istep)
                    {
                        (*list)[nvecs++] = i;
                    }
                    break;
                }
                else if (c == ':')
                {
                    status = sSteppedRange;
                    break;
                }
                else if (isdigit(c))
                {
                    break;
                }
                else
                {
                    status = sError;
                } break;

            /* format error occured */
            case sError:
                gmx_fatal(FARGS, "Error in the list of eigenvectors for %s at pos %d with char %c", listname, pos-startpos, *(pos-1));
                break;
            /* logical error occured */
            case sZero:
                gmx_fatal(FARGS, "Error in the list of eigenvectors for %s at pos %d: eigenvector 0 is not valid", listname, pos-startpos);
                break;
            case sSmaller:
                gmx_fatal(FARGS, "Error in the list of eigenvectors for %s at pos %d: second index %d is not bigger than %d", listname, pos-startpos, end_number, number);
                break;
        }
        ++pos; /* read next character */
    }          /*scanner has finished */

    /* append zero to list of eigenvectors */
    srenew(*list, nvecs+1);
    (*list)[nvecs] = 0;
    sfree(startpos);
    return nvecs;
} /*sscan_list*/