/*****************************************************************************

    functionname: atan_approx
    description:  Calculates atan , val >=0
    returns:      approx of atan(val), error is less then 0.5 %
    input:
    output:

*****************************************************************************/
static float atan_approx(float val)
{
  COUNT_sub_start("atan_approx");

  ADD(1); BRANCH(1);
  if(val < (float)1.0)
  {
    DIV(1); MULT(2); ADD(1); /* counting post-operations */
    COUNT_sub_end();
    return(val/((float)1.0f+(float)0.280872f*val*val));
  }
  else
  {
    DIV(1); MULT(1); ADD(2); /* counting post-operations */
    COUNT_sub_end();
    return((float)1.57079633f-val/((float)0.280872f +val*val));
  }

}