void
uim_throw_error(const char *msg)
{
  assert(msg || !msg);

  err_msg = msg;

  if (!guarded) {
    print_caught_error();
    exit(EX_SOFTWARE);
  }

#if UIM_USE_ERROR_GUARD
  /* To run print_caught_error() on roomed stack space, exit to the
   * guarded point first. */
  LONGJMP(uim_catch_block_env, guarded);
#endif
}