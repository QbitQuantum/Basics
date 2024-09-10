int
AvgByCount(double ts,
	  double input_val,
	  void *state_set,
	  int tau,
	  double *out_ts,
	  double *out_val)
{
	int ierr;
	double curr_ts;
	double curr_val;
	double count;
	double acc;
	int size;
	int read;
	
	Rewind(state_set);
	
	size = SizeOf(state_set);
	
	acc = input_val;
	*out_ts = ts;
	count = 1.0;
	read = 0;
	while((ReadEntry(state_set,&curr_ts,&curr_val) != 0) &&
	      (count < tau))
	{
		read += 1;
		
		/*
		 * -1 because input_val counts
		 */
		if((size - read) < (tau-1))
		{
			acc += curr_val;
/*
printf("%f ",curr_val);
*/
			count += 1;
		}
	}
	
/*
printf("%f ",input_val);
printf(" | ");
*/

	*out_val = acc / count;
	
	Rewind(state_set);
	return(1);
}