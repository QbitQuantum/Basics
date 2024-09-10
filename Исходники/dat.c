dat_t *
dat_fread (FILE *stream, int *count)
{
  /* reads a dat file, into an array pointed to by dat_ary.
     The number of elements in the array (0 may indicate an 
     error) is placed in count, returns dat_ary, the array
     which the user should free() when no longer needed. 
  */

  char str[STRLEN];				/* for reading the line */
  char *s;					/* temporary pointer */
  dat_t *dat_ary;				/* array to hold data */
  int dat_size = 0;			/* holds needed malloc'd size */
  fpos_t iFilePosition;             /* stores initial file position */

  /* Read the file until end of file */

  *count = 0;

  /* Do two reads, 1st time through just count how many there are */

  /* 1st get file position, so can reset after 1st time through,
     we could just seek to the beginning, but there is guarentee
     the stream is at the beginning.
  */
  if (fgetpos(stream, &iFilePosition)) return NULL;

  /* Do 1st pass on the file data, getting just the count */
  while (fgets (str, STRLEN, stream) != NULL) {

    /* Ignore the line if 1st character is a # */
    if (*str == '#') continue;

    /* Ignore blank lines */
    if ( (*str == '\0') || ((*str == '\n') && (*(str+1) == '\0')) ) continue;

    /* Increment counter */
    dat_size++;

  } /* while */

  /* Reset file position */
  if (fsetpos(stream, &iFilePosition)) return NULL;

  /* Allocate necessary space (should be all space that is needed) */
  if ( (dat_size == 0) || ((dat_ary = (dat_t *)malloc(sizeof(dat_t) * dat_size)) == NULL) )
    return NULL;

  /* Actually read in the data */
  while (fgets (str, STRLEN, stream) != NULL) {

    /* Ignore the line if 1st character is a # */
    if (*str == '#') continue;

    /* Ignore blank lines */
    if ( (*str == '\0') || ((*str == '\n') && (*(str+1) == '\0')) ) continue;

    /* Break up the string into tokens */

    s = strtok (str, " :");

    if (s == NULL)
      {
	strncpy (dat_ary[*count].name, "", 1);
      }

    else
      {
	strncpy (dat_ary[*count].name, s, DAT_NAME_LEN);
      }

    s = strtok (NULL, " :");

    if (s == NULL)
      {
	dat_ary[*count].rank = '?';
      }

    else
      {
	dat_ary[*count].rank = s[0];
      }
    
    /* Check on the length of the array */

    *count += 1;

    if (*count > dat_size) {
        printf("INTERNAL ERROR: 2nd processing of data file yielded extra entries!\n");
        exit(1);
    }
  } /* while */

  /* Return */

  return (dat_ary);
}