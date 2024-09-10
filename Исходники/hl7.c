struct hl7_part_t *
hl7split (struct hl7_part_t *hl7_part, char *separators)
{

  struct hl7_part_t *head,	/* begining of the data list */
   *current;			/* tail of the data list */

  int begin = 0,		/* start of the current string */
    scan = 0;			/* current position in string */

  /* if list of separators is empty, we have reached a leaf, return null */
  if (separators[0] == '\000'){
    return (struct hl7_part_t *) 0;
  }

  /* setup structure for current level of operations */
  if (!(current = head
               = (struct hl7_part_t *) malloc (sizeof (struct hl7_part_t))))
      exit (1);

  /* initialize the structure to some sane values */
  current->data = (char *) 0;
  current->next = (struct hl7_part_t *) 0;
  current->lower = (struct hl7_part_t *) 0;


  /* start looking thru the string for current seperator */
  for (; hl7_part->data[scan]; scan++)
    {
      /* when we find the current seperator */
      if (hl7_part->data[scan] == separators[0]) {
	  /* replace the seperator with a NULL */
	  hl7_part->data[scan] = '\000';

	  /* copy string that we found to current data element */
	  current->data = strset (&hl7_part->data[begin]);

	  /* split the string into substrings */
	  /* this is a little tricky */
	  /* send the seperator string starting with its _second_ element */
	  current->lower = hl7split (current, &separators[1]);

	  /* setup for the next string that we find */
	  if (!(current->next
                  =(struct hl7_part_t *)malloc(sizeof(struct hl7_part_t))))
	      exit (1);

	  /* move the current pointer to the node that we just created */
	  current = current->next;

	  /* initialize the data to some sane values */
	  current->data = (char *) 0;
	  current->next = (struct hl7_part_t *) 0;
	  current->lower = (struct hl7_part_t *) 0;

	  /* set the begining of the string to follow the found string */
	  begin = scan + 1;
	}
    }

  /* We reached the end of the string without finding (another) seperator.
     But there is still a string that we need to take care of. */

  /* put a copy of the string in the current data element */
  current->data = strset (&hl7_part->data[begin]);

  /* split the data element into substrings */
  /* this is a little tricky */
  /* I send the seperator string starting with its _second_ element */
  current->lower = hl7split (current, &separators[1]);

  /* get rid of string from parent, we stored it safely at this level */
  free (hl7_part->data);

  /* set the parent data element to the null pointer so that it won't be
     pointing to the place where the string used to be. */
  hl7_part->data = (char *) 0;

  /* return the list of substrings found to the parent. */
  return head;

} /* end split */