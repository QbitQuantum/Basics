/****************************************************************************
   function: periods_elapsed()

 parameters:     bdate - beginning date
	     curr_date - ending date
	      inc_days - the period size in days

    returns: The number of periods elapsed between two dates as an integer.

    purpose: This function will calculate the number of periods between
	     any to dates.
****************************************************************************/
long periods_elapsed(char *b_date, char *e_date, long inc_days)
  {
  ldiv_t q_r;

  q_r = ldiv(days_elapsed(b_date, e_date), inc_days);
  return(q_r.quot);
  }