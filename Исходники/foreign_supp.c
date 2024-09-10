/*-------------------------------------------------------------------------*
 * PL_FOREIGN_RD_IO_ARG                                                    *
 *                                                                         *
 *-------------------------------------------------------------------------*/
PlFIOArg *
Pl_Foreign_Rd_IO_Arg(int arg_long, WamWord start_word, PlLong (*rd_fct) (),
		     int fio_arg_index)
{
  WamWord word, tag_mask;
  PlFIOArg *fa = fio_arg_array + fio_arg_index;

  DEREF(start_word, word, tag_mask);

  fa->is_var = fa->unify = (tag_mask == TAG_REF_MASK);

  if (rd_fct == NULL)
    fa->value.l = (PlLong) word;
  else if (!fa->is_var)
    {
      if (arg_long)
	{
	  fa->value.l = (*rd_fct) (word);
	  if (arg_long == 2)	/* strdup needed */
	    fa->value.s = Strdup(fa->value.s);
	}
      else
	fa->value.d = (*(double (*)()) rd_fct) (word);
    }

  return fa;
}