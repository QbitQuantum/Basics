/* Merge *non-intersected* ranges R1 and R2 and returns the result.
   The function maintains the order of ranges and tries to minimize
   size of the result range list.  Ranges R1 and R2 may not be used
   after the call.  */
lra_live_range_t
lra_merge_live_ranges (lra_live_range_t r1, lra_live_range_t r2)
{
  lra_live_range_t first, last;

  if (r1 == NULL)
    return r2;
  if (r2 == NULL)
    return r1;
  for (first = last = NULL; r1 != NULL && r2 != NULL;)
    {
      if (r1->start < r2->start)
	std::swap (r1, r2);

      if (r1->start == r2->finish + 1)
	{
	  /* Joint ranges: merge r1 and r2 into r1.  */
	  r1->start = r2->start;
	  lra_live_range_t temp = r2;
	  r2 = r2->next;
	  lra_live_range_pool.remove (temp);
	}
      else
	{
	  gcc_assert (r2->finish + 1 < r1->start);
	  /* Add r1 to the result.  */
	  if (first == NULL)
	    first = last = r1;
	  else
	    {
	      last->next = r1;
	      last = r1;
	    }
	  r1 = r1->next;
	}
    }
  if (r1 != NULL)
    {
      if (first == NULL)
	first = r1;
      else
	last->next = r1;
    }
  else
    {
      lra_assert (r2 != NULL);
      if (first == NULL)
	first = r2;
      else
	last->next = r2;
    }
  return first;
}