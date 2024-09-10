static void  reducec(NUM_TYPE* l1,NUM_TYPE * l2)
{ NUM_TYPE    c, i1, i2;

   i1 = ABS(*l1); i2 = ABS(*l2);
   if (i2 > i1) { c = i1; i1 = i2; i2 = c; }
   while (i2 != 0) { c = i2; i2 = REST(i1,i2); i1 = c; }
   (*l1) = DIV(*l1,i1);
   (*l2) = DIV(*l2,i1);

}