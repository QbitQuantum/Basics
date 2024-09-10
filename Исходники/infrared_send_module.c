static void pin10_sigal()
{
  nrf_gpio_cfg_output(10);
  nrf_gpio_pin_set(10);
  __nop();
  __nop();
  __nop();
  __nop();
  nrf_gpio_pin_clear(10);
}