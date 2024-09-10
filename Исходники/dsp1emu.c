float Atan(float x)
{
   if ((x >= 1) || (x <= 1))
      return (x / (1 + 0.28 * x * x));
   else
      return (PI / 2 - Atan(1 / x));
}