void prompt_code(){
	Putc(COM1, 96);					// GO command for trains
	Create(8, timer_code);
	int dfa_tid = Create(10, dfa_code);
	int train_tid = Create(10, train_code);
	int switch_tid = Create(10, switch_code);
	Create(10, sensor_code);
	
	char input, state;
	char buff[3];
	
	while (1){
		input = Getc(COM2);
		if (input == 'q'){
			Putc(COM1, 97);							// Stop command for trains
			Putc(COM2, input);						// ECHO
			// Printf(COM2, "\033[2J\033[1;1H");		// clear the screen
			Printf(COM2, " ");Printf(COM2, " ");Printf(COM2, " ");
			SHUTDOWN();								// CALL SHUTDOWN SYSCALL to shutdown the program
		}
		Send(dfa_tid, &input, sizeof(char), &buff, 3*sizeof(char));
		state = buff[2];
		switch (state){
			case DFA_FULL:
				Printf(COM2, "\033[s\033[%d;%dHPrompt is full!                  \033[u", CMD_OUT_ROW, CMD_OUT_COL);
				break;
			case DFA_INVALID:
				Printf(COM2, "\033[%d;%dHInvalid input!!!                       \033[%d;%dH", CMD_OUT_ROW, CMD_OUT_COL, CMD_ROW, CMD_COL);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				break;
			case DFA_OK:
				Putc(COM2, input);			// ECHO
				//Printf(COM2, "\033[s\033[%d;%dHTyping...                      \033[u", CMD_OUT_ROW, CMD_OUT_COL);
				break;
			case DFA_BACKSPACE:
				Printf(COM2, "%c %c", input, input);		// Echo
				//Printf(COM2, "\033[s\033[%d;%dHRemoving...    \033[u", CMD_OUT_ROW, CMD_OUT_COL);
				break;
			case DFA_NO_BACKSPACE:
				Printf(COM2, "\033[s\033[%d;%dH                                 \033[u", CMD_OUT_ROW, CMD_OUT_COL);
				break;
			case DFA_TR_SP:
				Printf(COM2, "\033[s\033[%d;%dHSetting speed of tr#%d to %d...  \033[u", CMD_OUT_ROW, CMD_OUT_COL, buff[1], buff[0]);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				// Send command to the train task to set speed of the train
				Send(train_tid, &buff, 2*sizeof(char), &input, sizeof(char));
				break;
			case DFA_TR_RV:
				Printf(COM2, "\033[s\033[%d;%dHReversing tr#%d...               \033[u", CMD_OUT_ROW, CMD_OUT_COL, buff[1], buff[0]);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				buff[0] = 15;
				Send(train_tid, &buff, 2*sizeof(char), &input, sizeof(char));
				break;
			case DFA_SW:
				Printf(COM2, "\033[s\033[%d;%dHThrowing sw#%d to %c...          \033[u", CMD_OUT_ROW, CMD_OUT_COL, buff[1], buff[0]);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				Send(switch_tid, &buff, 2*sizeof(char), &input, sizeof(char));
				break;
			default:
				Printf(COM2, "\033[s\033[%d;%dHDFA PROBLEM!!!                   \033[u", CMD_OUT_ROW, CMD_OUT_COL);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				break;
		}
	}
	Putc(COM1, 97);			// Stop command for trains
	
	Exit();
	kprintf("Unexpected return from Exit() at prompt_code\n\r");
}