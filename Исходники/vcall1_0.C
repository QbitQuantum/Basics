int
main (void)
{
  A* p;
  int i;
  int s = 0;

  p = getB();
  for (i = 0; i < 100; i++)
   {
      s += p->AA();
   }

  for (i = 0; i < 100; i++)
   {
      if (i%10 == 0)
        p = getB();
      else
        p = getC();

      s += p->AA();
   }
   printf ("result = %d\n",s);
}