/**
* AT Command receiving thread. ( ** AT Command Server ** )
* This thread keeps calling a callback function stored
* in 'func_ptrs.read' to fetch data, accumulates these data until
* a full AT command has been received, and then call the AT decoder.
* */
DEFINE_THREAD_ROUTINE_STACK(ATcodec_Commands_Server,data,ATCODEC_STACK_SIZE)
{
  ATcodec_Tree_t *tree = &default_tree;
  AT_CODEC_ERROR_CODE res;
  int32_t v_loop, v_read, len, nb_cmd = 0;
  char buffer[INTERNAL_BUFFER_SIZE]; // user-defined
  char global_buffer[INTERNAL_BUFFER_SIZE];
  char safety[16];  // Absorbs data overflowing from global_buffer.
  int global_len=0;
	
  v_continue = 1;
  PRINT("Thread AT Commands Server Start\n");
	
  while(!atcodec_lib_init_ok)
  {
    vp_os_thread_yield();
  }
	
  while(v_continue)
  {
    vp_os_memset(buffer,0,sizeof(buffer));
    vp_os_memset(global_buffer,0,sizeof(global_buffer));global_len=0;
    vp_os_memset(safety,0,sizeof(safety));

    // open and init
		  if((res = func_ptrs.open()) != AT_CODEC_OPEN_OK){
      v_continue = 0;
    }
		
    for ( v_loop = 1 ; v_loop && func_ptrs.enable() == AT_CODEC_ENABLE_OK; )
    {
      v_read = 1;
      do
      {
        // wait so that thread can give the hand : delay user-defined / OS-dependent
        //vp_os_thread_yield();

        // -> we do a blocking read few lines after, thus
        // other threads will be able to run during the I/O

        /* In case of reading from packets, we clear the incoming buffer.
         * Splitting AT commands into several packets would be a bad idea since packet order in not guaranteed in UDP.
         */
		if (at_codec_reading_mode==ATCODEC_READ_FROM_PACKETS){
          vp_os_memset(global_buffer,0,sizeof(global_buffer));
          global_len=0;
        }

        /*
         * Read some bytes; this function blocks until some data are made
         * available by the VP_COM thread.
         */
        len = sizeof(buffer); //INTERNAL_BUFFER_SIZE/*/2*/; // user-defined
        res = func_ptrs.read((uint8_t*)&buffer[0], (int32_t*)&len);

        if(res == AT_CODEC_READ_OK)
        {
          if(len > 0)
          {
            // process characters and update v_read
            // \todo Do not use nb_cmd ?

            /* Data are accumulated in the global buffer until at least one '\r' is found. */
            if((nb_cmd = append_reception(&buffer[0], len, &global_buffer[0], &global_len,sizeof(global_buffer))) > 0)
            {
              v_read = 0;
            }
            else if(nb_cmd == -1) /* no \r found in the global_buffer*/
            {
              // a buffer overflow occurs
              switch(at_codec_reading_mode)
              {
                case ATCODEC_READ_FROM_STREAM:
                  PRINT("AT Codec buffer was filled before a full AT commands was received.");
                  break;
                case ATCODEC_READ_FROM_PACKETS:
                  PRINT("AT Codec received a packet with no complete AT command or buffer was too small to store the whole packet.");
                  break;
              }
              //ATCODEC_PRINT("Overflow\n");

              /* In case of overflow, a TCP connection should be reinitialized in order to resynchronize
               * the client and the server. Otherwise there is no way to find the beginning of the next AT Command.
               * For a UDP connection, we assume all packets begin with an AT Command, and we just wait
               * for the next packet to arrive.
               */
              if (at_codec_reading_mode==ATCODEC_READ_FROM_STREAM) { v_loop = 0; }
            }
            else
            {
              v_read = 1;
            }
          }
          else
          {
            if(len < 0)
            {
              ATCODEC_PRINT("read returns a neg length\n");
              v_loop = 0;
            }
          }
        }
        else /* if (res == AT_CODEC_READ_OK) */
        {
          // an error occurred
          ATCODEC_PRINT("an error occurs\n");
          v_loop = 0;
        }
      }
      while (v_read && v_loop);

      // process what has been received if no error occurs
      if(v_loop)
      {
        // ...
        if(process_received_data(tree, nb_cmd, &global_buffer[0], &global_len) != ATCODEC_TRUE)
        {
          ATCODEC_PRINT("process_received returns false\n");
          v_loop = 0;
        }
      }
    } /*for*/
		
    // close and un-init : user-defined
    if((res = func_ptrs.close()) != AT_CODEC_CLOSE_OK)
      v_continue = 0;

  }/* while */
	
  if ((res = func_ptrs.shutdown()) != AT_CODEC_SHUTDOWN_OK)
  {
    ATCODEC_PRINT("ATcodec Shutdown error\n");
  }
	
  return((THREAD_RET)0);
}