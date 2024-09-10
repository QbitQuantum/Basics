static void
print (void)
{
  FILE * file = fopen (tmp, "w");
  int i, j, lit, count;
  Exp * e, ** sorted;

  if (!file)
    die ("can not write to '%s'", tmp);

  count = 0;
  
  for (i = 1; i < nexps; i++)
    {
      e = exps + i;

      if (!e->ref)
	continue;

      if (!e->idx)
	continue;

      count++;
    }

  sorted = malloc (count * sizeof * sorted);

  j = 0;
  for (i = 1; i < nexps; i++)
    {
      e = exps + i;

      if (!e->ref)
	continue;

      if (!e->idx)
	continue;

      sorted[j++] = e;
    }

  assert (j == count);

  if (!nosort)
  qsort (sorted, count, sizeof *sorted, cmp_by_idx);

  for (i = 0; i < count; i++)
    {
      e = sorted[i];

      if (!e->ref)
	continue;

      if (!e->idx)
	continue;

      if (e->cut)
	{
	  fprintf (file, "%d var %d\n", e->idx, e->width);
	}
      else
	{
	  fprintf (file, "%d %s %d", e->idx, e->op, e->width);

	  if (isarrayop (e->op))
	    fprintf (file, " %d", e->addrwidth);

	  for (j = 0; j < e->childs; j++)
	    {
	      lit = e->child[j];
	      fprintf (file, " %d", ischild (e, j) ? deidx (lit) : lit);
	    }

	  if (e->name)
	    fprintf (file, " %s", e->name);

	  fputc ('\n', file);
	}
    }

  fclose (file);

  free (sorted);
}