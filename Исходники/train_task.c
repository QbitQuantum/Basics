void train_code(){
	char tr_speeds [NUM_TRAINS];
	// initialization
	int i;
	for (i = 0; i < NUM_TRAINS; i++){
		tr_speeds[i] = 0;
	}
	
	char stop[3];
	char rcv_buff[3];
	stop[0] = stop[1] = stop[2] = rcv_buff[0] = rcv_buff[1] = rcv_buff[2] = 0;
	
	char reply_buff = 0;
	int prompt_tid;
	while(1){
		// Need to receive 2 bytes for the train command
		Receive(&prompt_tid, &rcv_buff, 2*sizeof(char));
		if (rcv_buff[0] == 15){								// Reversing
			stop[1] = rcv_buff[1];							//	train number
			Putc(COM1, 0);	Putc(COM1, stop[1]);			// Stop
			Reply(prompt_tid, &reply_buff, sizeof(char));
			Delay(200);
			Putstr(COM1, rcv_buff);							// Reverse
			rcv_buff[0] = tr_speeds[rcv_buff[1]-1];			// stored speed of the train
			Putstr(COM1, rcv_buff);							// Set speed
		}
		else if(rcv_buff[0] == 0){
			tr_speeds[rcv_buff[1]-1] = 0;
			Putc(COM1, 0);	Putc(COM1, rcv_buff[1]);
			Reply(prompt_tid, &reply_buff, sizeof(char));
		}
		else {												// Setting speed
			tr_speeds[rcv_buff[1]-1] = rcv_buff[0];
			Putstr(COM1, rcv_buff);
			Reply(prompt_tid, &reply_buff, sizeof(char));
		}
	}
	
	Exit();
	kprintf("Unexpected return from Exit() at train_code\n\r");
}