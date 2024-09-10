int
main(int argc, char **argv)
{
  struct timeval stv, etv;
  const char * const *engines;

  for (unsigned int i = START; i <= END; i *= 10) {
    gettimeofday(&stv, NULL);
    for (unsigned int j = 0; j < i; j++)
      i += (uintptr_t) test_return(NULL, NULL);
    gettimeofday(&etv, NULL);
    printf(RFMT, "return", i, TIME(stv, etv), 0);
  }

  engines = ql_engine_list();
  assert(engines);

  for (unsigned int i = 0; engines[i]; i++) {
    qlParameter param;
    qlState *state;

    for (unsigned int j = START; j <= END; j *= 10) {
      gettimeofday(&stv, NULL);
      for (unsigned int k = 0; k < j / YIELDS; k++) {
        state = ql_state_new(NULL, engines[i], test_yield, 0);
        while (ql_state_step(state, &param))
          continue;
      }
      gettimeofday(&etv, NULL);
      printf(FMT, engines[i], "yield", j, TIME(stv, etv), j / YIELDS * 2);
    }
  }

  return 0;
}