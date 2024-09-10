int check_result(double src, double ref, double test, eps_t* thres)
{
  double diff;
  double error;

  diff=fabs(ref-test);
  if(ref==0)
    error=diff;
  else
    error=diff/fabs(ref);

  if (_isnan(error) || _isinf(error))
    return 1; //warning

  if(error>=thres->warn && error<thres->fail) {
    return 1; //warning
  }else if (error >= thres->fail) {
    printf("error=%12.5E src=%12.5E ref=%12.5E\t test=%12.5E\n", error, src, ref, test);
	return 2; //error
  }else{
    return 0; //pass
  }
}