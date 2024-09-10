static void cdj_FF()
{
   fputs("\033*rbC\033E", prnstr);
   fputs("\033&l0H",prnstr);        //FORM FEED
   blanklines = 0;
}