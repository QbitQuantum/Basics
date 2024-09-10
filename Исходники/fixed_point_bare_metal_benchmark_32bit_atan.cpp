void app::benchmark::task_func()
{
  using std::atan;

  mcal::irq::disable_all();
  port_type::set_pin_high();

  y = atan(x);

  port_type::set_pin_low();
  mcal::irq::enable_all();

  // atan(4/10) = approx. 0.3805063771123649
  const bool value_is_ok =    (y > (numeric_type(38) / 100))
                           && (y < (numeric_type(39) / 100));

  if(value_is_ok)
  {
    // The benchmark is OK.
    // Perform one nop and leave.

    mcal::cpu::nop();
  }
  else
  {
    // The benchmark result is not OK!
    // Remain in a blocking loop and crash the system.

    for(;;) { mcal::cpu::nop(); }
  }
}