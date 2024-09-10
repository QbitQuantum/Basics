float        LinInterpolateRampU16   ( unsigned short    * ramp,
                                       int                 ramp_size,
                                       float               pos )
{
  unsigned short val1, val2;
  float start, dist, result;
  
  if(!ramp)
    return 0.0;
  
  if(pos < 0)
    return ramp[0];
    
  if(pos > ramp_size-1)
    return ramp[ramp_size-1];
  
  dist = modff( pos, &start );
  val1 = ramp[(int)start];
  val2 = ramp[(int)start+1];
    
  result = val2 - val1;
  result *= dist;
  result += val1;
    
  return result;
}