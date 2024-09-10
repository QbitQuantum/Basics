/**
 * \brief   Init of input history buffer
 *
 * \param   ihb            ... input history buffer
 * \param   lines          ... number of lines
 * \param   lenght         ... number of characters per line
 *          
 * This is the init-function of the input history buffer. It allocates the
 * history buffer.
 */
int
contxt_ihb_init(contxt_ihb_t *ihb, int lines, int length)
{  
  if (lines < 2)
    lines = 2;
  if (length < 2)
    length = 2;

  /* consider terminating '\0' */
  length++;
  
  ihb->lines  = lines;
  ihb->first  = 0;
  ihb->last   = 0;
  ihb->length = length;
 
  /* allocate history buffer */
  if (!(ihb->buffer = malloc(lines*length)))
    {
      LOGl("no mem for ihb->head");
      return -L4_ENOMEM;
    }

  /* empty whole history buffer */
  memset(ihb->buffer, 0, lines*length);
  
  return 0;
}