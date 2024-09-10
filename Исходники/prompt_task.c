void prompt_code(){
	Putc(COM1, 96);					// GO command for trains
	Create(PR_TIMER, timer_code);
	int dfa_tid = Create(PR_DFA, dfa_code);
	int train_tid = Create(PR_TRAIN_COMMANDER, train_commander_code);
	int switch_tid = Create(PR_SWITCH, switch_code);
	Create(PR_SENSOR, sensor_code);
	
	char input, state;
	char buff[9];
	train_server_request tsr;
	
	int node_index = 0;
	
	while (1){
		input = Getc(COM2);
		if (input == 'q'){
			Putc(COM1, 97);							// Stop command for trains
			Putc(COM2, input);						// ECHO
			Printf(COM2, " ");Printf(COM2, " ");Printf(COM2, " ");
			// send signal to calibration server to print calibration data and halt the system.
			// Send(WhoIs("CALIBRATIONSERVER"), &input, sizeof(char), &input, sizeof(char));
			
			SHUTDOWN();								// CALL SHUTDOWN SYSCALL to shutdown the program
		}
		else if (input == '/'){
			Debug("[Time: %d     ]", Time());
			continue;
		}
		Send(dfa_tid, &input, sizeof(char), &buff, 9*sizeof(char));
		state = buff[0];
		switch (state){
			case DFA_FULL:
				Printf(COM2, "\033[s\033[%d;%dHPrompt is full!                    \033[u", CMD_OUT_ROW, CMD_OUT_COL);
				break;
			case DFA_INVALID:
				Printf(COM2, "\033[%d;%dHInvalid input!!!                         \033[%d;%dH", CMD_OUT_ROW, CMD_OUT_COL, CMD_ROW, CMD_COL);
				Printf(COM2, "\033[%d;%dH\033[s                     \033[u", CMD_ROW, CMD_COL);
				break;
			case DFA_OK:
				Putc(COM2, input);			// ECHO
				break;
			case DFA_BACKSPACE:
				Printf(COM2, "%c %c", input, input);		// Echo
				break;
			case DFA_NO_BACKSPACE:
				Printf(COM2, "\033[s\033[%d;%dH                                          \033[u", CMD_OUT_ROW, CMD_OUT_COL);
				break;
			case DFA_TR_SP:
				Printf(COM2, "\033[s\033[%d;%dHSetting speed of tr#%d to %d...           \033[u", CMD_OUT_ROW, CMD_OUT_COL, buff[2], buff[1]);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				// Send command to the train task to set speed of the train
				Send(train_tid, buff+1, 2*sizeof(char), &input, sizeof(char));
				break;
			case DFA_TR_SP_AT_NODE:
				Printf(COM2, "\033[s\033[%d;%dHSetting speed of tr#%d to %d at node %s...\033[u", CMD_OUT_ROW, CMD_OUT_COL, buff[2], buff[1], (buff+3));
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				tsr.type = TRAIN_TYPE_SPEED_AT_NODE;
				tsr.data.speed_request.speed = buff[1];
				tsr.data.speed_request.tr_num = buff[2];
				strncpy(tsr.data.speed_request.node_name, buff+3, 6);
				Send(WhoIs("TRAINSERVER"), &tsr, sizeof(train_server_request), &input, sizeof(char));
				
				break;
			case DFA_TR_RV:
				Printf(COM2, "\033[s\033[%d;%dHReversing tr#%d...                        \033[u", CMD_OUT_ROW, CMD_OUT_COL, buff[2]);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				buff[1] = 15;
				Send(train_tid, buff+1, 2*sizeof(char), &input, sizeof(char));
				break;
			case DFA_SW:
				Printf(COM2, "\033[s\033[%d;%dHThrowing sw#%d to %c...                   \033[u", CMD_OUT_ROW, CMD_OUT_COL, buff[2], buff[1]);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				Send(switch_tid, buff+1, 2*sizeof(char), &input, sizeof(char));
				break;
			case DFA_STOP_AT:
				Printf(COM2, "\033[s\033[%d;%dHStopping train %d at %s                   \033[u", CMD_OUT_ROW, CMD_OUT_COL, buff[2], (buff+3));
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				// Send appropriate command to train server to stop the train at the appropriate location
				tsr.type = TRAIN_TYPE_SPEED_AT_NODE;
				tsr.data.speed_request.speed = buff[1];
				tsr.data.speed_request.tr_num = buff[2];
				strncpy(tsr.data.speed_request.node_name, buff+3, 6);
				Send(WhoIs("TRAINSERVER"), &tsr, sizeof(train_server_request), &input, sizeof(char));
				break;
			case DFA_GO_TO:
				tsr.type = TRAIN_TYPE_GO_TO_NODE;
				tsr.data.speed_request.tr_num = buff[2];
				strncpy(tsr.data.speed_request.node_name, buff+3, 6);
				Send(WhoIs("TRAINSERVER"), &tsr, sizeof(train_server_request), &node_index, sizeof(int));
				if(node_index != -1) {
					Printf(COM2, "\033[s\033[%d;%dHMoving train %d to %s                    \033[u", CMD_OUT_ROW, CMD_OUT_COL, buff[2], (buff+3));
					Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				}
				else {
					Printf(COM2, "\033[s\033[%d;%dHInvalid node name                        \033[u", CMD_OUT_ROW, CMD_OUT_COL);
					Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				}
				break;
			case DFA_SW_ALL_C:
				Printf(COM2, "\033[s\033[%d;%dHInitializing switches to C (curve)...     \033[u", CMD_OUT_ROW, CMD_OUT_COL);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				buff[2] = SWICTH_ALL_C;
				Send(switch_tid, buff+1, 2*sizeof(char), &input, sizeof(char));
				break;
			case DFA_SW_ALL_S:
				Printf(COM2, "\033[s\033[%d;%dHInitializing switches to S (straight)...  \033[u", CMD_OUT_ROW, CMD_OUT_COL);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				buff[2] = SWICTH_ALL_S;
				Send(switch_tid, buff+1, 2*sizeof(char), &input, sizeof(char));
				break;
			case DFA_SW_SMALL_LOOP1:
				Printf(COM2, "\033[s\033[%d;%dHInitializing switches to small loop 1...  \033[u", CMD_OUT_ROW, CMD_OUT_COL);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				buff[2] = SWICTH_SMALL_LOOP1;
				Send(switch_tid, buff+1, 2*sizeof(char), &input, sizeof(char));
				break;
			case DFA_SW_SMALL_LOOP2:
				Printf(COM2, "\033[s\033[%d;%dHInitializing switches to small loop 2...  \033[u", CMD_OUT_ROW, CMD_OUT_COL);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				buff[2] = SWICTH_SMALL_LOOP2;
				Send(switch_tid, buff+1, 2*sizeof(char), &input, sizeof(char));
				break;
			case DFA_SW_MEDIUM_LOOP:
				Printf(COM2, "\033[s\033[%d;%dHInitializing switches to medium loop...   \033[u", CMD_OUT_ROW, CMD_OUT_COL);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				buff[2] = SWICTH_MEDIUM_LOOP;
				Send(switch_tid, buff+1, 2*sizeof(char), &input, sizeof(char));
				break;
			case DFA_SW_LARGE_LOOP:
				Printf(COM2, "\033[s\033[%d;%dHInitializing switches to large loop...    \033[u", CMD_OUT_ROW, CMD_OUT_COL);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				buff[2] = SWICTH_LARGE_LOOP;
				Send(switch_tid, buff+1, 2*sizeof(char), &input, sizeof(char));
				break;
			case DFA_SW_EXTRA_LARGE_LOOP:
				Printf(COM2, "\033[s\033[%d;%dHInitializing switches to extra large loop \033[u", CMD_OUT_ROW, CMD_OUT_COL);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				buff[2] = SWICTH_EXTRA_LARGE_LOOP;
				Send(switch_tid, buff+1, 2*sizeof(char), &input, sizeof(char));
				break;
			case DFA_SW_DEFAULT:
				Printf(COM2, "\033[s\033[%d;%dHInitializing switches to default state... \033[u", CMD_OUT_ROW, CMD_OUT_COL);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				buff[2] = SWICTH_DEFAULT;
				Send(switch_tid, buff+1, 2*sizeof(char), &input, sizeof(char));break;
				break;
			default:
				Printf(COM2, "\033[s\033[%d;%dHDFA PROBLEM!!!                           \033[u", CMD_OUT_ROW, CMD_OUT_COL);
				Printf(COM2, "\033[%d;%dH\033[s                    \033[u", CMD_ROW, CMD_COL);
				break;
		}
	}
	
	Warning(0,"Unexpected return from Exit() at prompt_code\n\r");
	Exit();
	Warning(0,"Unexpected return from Exit() at prompt_code\n\r");
}