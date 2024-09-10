/* ------------------------------------------------------------------------- *
 * Block waiting of specified timer
 * ------------------------------------------------------------------------- */
void WaitTim(TIM_Indx indx, uint32_t value)
{
  LoadTim(indx, value);

  while (GetTim(indx) != 0)
    __nop();
}