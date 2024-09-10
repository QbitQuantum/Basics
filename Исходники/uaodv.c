  uip_ipaddr_copy(&rreq_addr, host);
  command = COMMAND_SEND_RREQ;
  process_post(&uaodv_process, PROCESS_EVENT_MSG, NULL);
  timer_set(&next_time, CLOCK_SECOND/8); /* Max 10/s per RFC3561. */
  return NULL;
}

PROCESS_THREAD(uaodv_process, ev, data)
{
  PROCESS_EXITHANDLER(goto exit);

  PROCESS_BEGIN();

  printf("uaodv_process starting %lu\n", (unsigned long) my_hseqno);

  bcastconn = udp_broadcast_new(HTONS(UAODV_UDPPORT), NULL);
  unicastconn = udp_broadcast_new(HTONS(UAODV_UDPPORT), NULL);
  
  while(1) {
    PROCESS_WAIT_EVENT();

    if(ev == tcpip_event) {
      if(uip_newdata()) {
	handle_incoming_packet();
	continue;
      }
      if(uip_poll()) {
	if(command == COMMAND_SEND_RREQ) {
	  if(uaodv_rt_lookup(&rreq_addr) == NULL)
	    send_rreq(&rreq_addr);
	} else if (command == COMMAND_SEND_RERR) {