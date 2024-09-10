PROCESS_THREAD(ieee_process, ev, data)
{
  static void (*ieee_mlmehandler)(MAC_MlmeDcfmInd_s*);
  static void (*ieee_mcpshandler)(MAC_McpsDcfmInd_s*);

  PROCESS_BEGIN();
  PUTS("ieee_process: starting\n");

  ieee_init();
  ieee_serial_init();

  PT_INIT(&ieee_mlme); ieee_mlmehandler = ieee_mlmept;
  PT_INIT(&ieee_mcps); ieee_mcpshandler = ieee_mcpspt;

  /* start the mlme thread by requesting a scan. */
  req_scan(MAC_MLME_SCAN_TYPE_ACTIVE,0);

  PUTS("ieee_process: started\n");

  /* run until this process is exiting */
  while(true)
  {
    size_t i;
    MAC_DcfmIndHdr_s *macev;

    for(i=0; i<RX_QUEUE_SIZE && (macev=rxq_peek())!=NULL; i++)
    {
      if(rxq_peektype()==MLME) {
        //ieee_serial_mlme((MAC_MlmeDcfmInd_s*) macev);
        ieee_mlmehandler((MAC_MlmeDcfmInd_s*) macev);
      }
      else if(rxq_peektype()==MCPS) {
        //ieee_serial_mcps((MAC_McpsDcfmInd_s*) macev);
        ieee_mcpshandler((MAC_McpsDcfmInd_s*) macev);
      }

      rxq_dequeue();
    }

    if (ev==ieee_event && data == IEEE_STARTED)
      ieee_started = true;

    PROCESS_YIELD();
  }

  PUTS("ieee_process: exiting\n");
  PROCESS_END();
}