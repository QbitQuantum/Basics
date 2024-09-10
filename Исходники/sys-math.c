/**
 * lw6sys_math_angle_360
 *
 * @sys_context: global system context
 * @x: x coordinate
 * @y: y coordinate
 *
 * This is a wrapper over the standard @atan function which will
 * handle internally the special x == 0 case and the various positive/negative
 * values of @x and @y.
 *
 * Return value: the angle, in degrees
 */
float
lw6sys_math_angle_360 (lw6sys_context_t * sys_context, int x, int y)
{
  float ret = 0.0f;

  if (x == 0)
    {
      ret = (y == 0) ? 0.0f : (y > 0) ? 90.0f : 270.0f;
    }
  else
    {
      if (x > 0)
	{
	  if (y >= 0)
	    {
	      ret = lw6sys_math_rad2deg (atanf (((float) y) / ((float) x)));
	    }
	  else
	    {
	      ret = 360.0f - lw6sys_math_rad2deg (atanf (((float) -y) / ((float) x)));
	    }
	}
      else
	{
	  if (y >= 0)
	    {
	      ret = 180.0f - lw6sys_math_rad2deg (atanf (((float) y) / ((float) -x)));
	    }
	  else
	    {
	      ret = 180.0f + lw6sys_math_rad2deg (atanf (((float) -y) / ((float) -x)));
	    }
	}
    }

  return ret;
}