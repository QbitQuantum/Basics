/*
  load a node from the file
  Params: fp - the input stream
          error - return for error
  Returns: node loaded.
  Notes: recursive. Expects the opening parenthesis to have been eaten
 */
NEWICKNODE *TreeOPE::loadnode(FILE *fp, int *error)
{
  NEWICKNODE *answer = NULL;
  int err;
  NEWICKNODE *child = 0;
  int ch;

  answer = (NEWICKNODE *) malloc(sizeof(NEWICKNODE));
  //printf("sizeof(NEWICKNODE) = %d\n", sizeof(NEWICKNODE));
  if(!answer)
  {
    err = -1;
    goto error_exit;
  }

  answer->Nchildren = 0;
  answer->label = 0;
  answer->child = 0;
  answer->hv1 = 0;
  answer->hv2 = 0;
  answer->bitstr = NULL;

  skipspace(fp);
  do
  {
    ch = fgetc(fp);
    if(ch == '(')
    {
      child = loadnode(fp, &err);
      if(!child)
        goto error_exit;

      if(addchild(answer, child ) == -1)
      {
        err = -1;
        goto error_exit;
      }
      child = 0;
    }
    else
    {
      ungetc(ch, fp);
      child = loadleaf(fp, &err);
      if(!child)
        goto error_exit;

      if(addchild(answer, child) == -1)
      {
        err = -1;
        goto error_exit;
      }
      child = 0;
    }
    skipspace(fp);
    ch = fgetc(fp);
  } while(ch == ',');

  if(ch == ')')
  {
    answer->label = readlabelandweight(fp, &answer->weight, &err);
    if(err)
      goto error_exit;
  }
  else
  {
    err = -2;
    goto error_exit;
  }

  if(error)
    *error = 0;
  return answer;

 error_exit:
  if(child)
    killnoder(child);
  killnoder(answer);
  if(error)
    *error = err;
  return 0;
}