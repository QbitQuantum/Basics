/********************Start*************************/
void I2CStart (void)
{
 DIO_H ;
 CLK_H ;
  #ifdef tm1651_delay_EN
__nop() ;
  tm1651_delay();
  #endif
 DIO_H ;

 DIO_L ;
  #ifdef tm1651_delay_EN
 __nop() ;
  #endif
 CLK_L ;
}