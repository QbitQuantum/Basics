/*---------------------------------------------------------------------------*/
PROCESS_THREAD(border_router_process, ev, data)
{
  static struct etimer et;

  PROCESS_BEGIN();
  PUTSTRING("Border Router started\n");
  prefix_set = 0;

  leds_on(LEDS_GREEN);

  /* Request prefix until it has been received */
  while(!prefix_set) {
    leds_on(LEDS_RED);
    PUTSTRING("Prefix request.\n");
    etimer_set(&et, CLOCK_SECOND);
    request_prefix();
    leds_off(LEDS_RED);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }
  /* We have created a new DODAG when we reach here */
  PUTSTRING("On Channel ");
  PUTDEC(cc2530_rf_channel_get());
  PUTCHAR('\n');

  print_local_addresses();

  leds_off(LEDS_GREEN);

  PROCESS_EXIT();

  PROCESS_END();
}