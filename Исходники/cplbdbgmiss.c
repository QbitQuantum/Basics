void _cplb_miss_without_replacement(void)
{
  interrupt_info iinfo[1];
  get_interrupt_info(ik_exception, iinfo);
  _ex_report_event(iinfo);
  _Exit();
  /* NOTREACHED */
}