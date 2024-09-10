void Fl_Osc_Dial::OSC_value(int v)
{
    value(v + value() - floorf(value()) +
          (minimum() == 64 ? 0 : minimum()));
}