static void repeat_1_cb(uv_timer_t* handle, int status) {
  int r;

  ASSERT(handle == &repeat_1);
  ASSERT(status == 0);

  ASSERT(uv_timer_get_repeat((uv_timer_t*)handle) == 50);

  LOGF("repeat_1_cb called after %ld ms\n",
      (long int)(uv_now(uv_default_loop()) - start_time));

  repeat_1_cb_called++;

  r = uv_timer_again(&repeat_2);
  ASSERT(r == 0);

  if (uv_now(uv_default_loop()) >= start_time + 500) {
    uv_close((uv_handle_t*)handle, close_cb);
    /* We're not calling uv_timer_again on repeat_2 any more, so after this */
    /* timer_2_cb is expected. */
    repeat_2_cb_allowed = 1;
    return;
  }
}