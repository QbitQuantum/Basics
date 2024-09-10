void hpx_finalize(void) {
  // clean up after _hpx_143
  if (_hpx_143 != HPX_NULL) {
    hpx_gas_free(_hpx_143, HPX_NULL);
  }

#if defined(HAVE_APEX)
  // this will add the stats to the APEX data set
  libhpx_save_apex_stats();
#endif
  _stop(here);

#if defined(ENABLE_PROFILING)
  libhpx_stats_print();
#endif
  _cleanup(here);
}