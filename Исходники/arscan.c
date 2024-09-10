static int
VMS_get_member_info (struct dsc$descriptor_s *module, unsigned long *rfa)
{
  int status, i;
  long int fnval;

  time_t val;

  static struct dsc$descriptor_s bufdesc =
    { 0, DSC$K_DTYPE_T, DSC$K_CLASS_S, NULL };

  struct mhddef *mhd;
  char filename[128];

  bufdesc.dsc$a_pointer = filename;
  bufdesc.dsc$w_length = sizeof (filename);

  status = lbr$set_module (&VMS_lib_idx, rfa, &bufdesc,
			   &bufdesc.dsc$w_length, 0);
  if (! (status & 1))
    {
      error (NILF, _("lbr$set_module failed to extract module info, status = %d"),
	     status);

      lbr$close (&VMS_lib_idx);

      return 0;
    }

  mhd = (struct mhddef *) filename;

#ifdef __DECC
  /* John Fowler <*****@*****.**> writes this is needed in his environment,
   * but that decc$fix_time() isn't documented to work this way.  Let me
   * know if this causes problems in other VMS environments.
   */
  val = decc$fix_time (&mhd->mhd$l_datim) + timezone - daylight*3600;
#endif

  for (i = 0; i < module->dsc$w_length; i++)
    filename[i] = _tolower ((unsigned char)module->dsc$a_pointer[i]);

  filename[i] = '\0';

  VMS_member_date = (time_t) -1;

  fnval =
    (*VMS_function) (-1, filename, 0, 0, 0, 0, val, 0, 0, 0,
		     VMS_saved_memname);

  if (fnval)
    {
      VMS_member_date = fnval;
      return 0;
    }
  else
    return 1;
}