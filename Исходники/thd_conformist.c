static int_pair zpadax_pm( int nx_super , float xorg_super ,
                           int nx_input , float xorg_input , float dx )
{
   int_pair pm ; float ts , ti ;

   ts   = xorg_super + nx_super * dx ;
   ti   = xorg_input + nx_input * dx ;
   pm.i = (int)rintf((xorg_input-xorg_super)/dx) ;
   pm.j = (int)rintf((ts-ti)/dx) ;

   return pm ;
}