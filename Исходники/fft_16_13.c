/* conversion function to 1.NUMBER_OF_BITS format */
int convert(float value)
{
  float man, t_val, frac, m, exponent = NUMBER_OF_BITS;
  int rnd_val;
  unsigned long int_val;
  unsigned long pm_val;

  m = exp2f(exponent+1)  - 1;

  t_val = value * m ;
  frac = modff(t_val,&man);
  if (frac < 0.0f) 
    {
      rnd_val = (-1);
      if (frac > -0.5f) rnd_val = 0;
    }
  else
    {
      rnd_val = 1;
      if (frac < 0.5f) rnd_val = 0;
    }
  int_val = man + rnd_val;
  
  pm_val = int_val ; 
  return ((int) (pm_val)) ; 
  
}