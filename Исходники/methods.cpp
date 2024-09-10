/*
 * RESUME PROCESS
 *	This method takes in the process ID to be resumed from suspend queue
 *	 and return error if this process isn't suspended.
 */
void resume_Process(INT32 process_ID, INT32 *error, bool iAmResume) {
	bool check = check_PID_existance(process_ID);
	//process don't exists
	if (check) {
		//print
		PCB* temp = proIdToPCB[process_ID];
		if (suspendQueue_proIdToExistance[process_ID] == 1) {
			if (!iAmResume) {
				if (temp->STATE == Waiting_For_RECEIVE) {
					//remove from	suspend queue
					suspend_queue.remove(temp);
					suspendQueue_proIdToExistance[process_ID] = -1;
					//add to ready queue
					add_to_readyQueue(temp);
					receive_suspended[process_ID] = NULL;
					temp->STATE = READY;
				} else if (temp->STATE == SUSPEND_AND_RECIVEING) {
					receive_suspended[process_ID] = NULL;
					temp->STATE = SUSPEND;
				}
			} else {
				if (temp->STATE == SUSPEND) {
					suspend_queue.remove(temp);
					suspendQueue_proIdToExistance[process_ID] = -1;
					//add to ready queue
					add_to_readyQueue(temp);
					temp->STATE = READY;
				} else if (temp->STATE == SUSPEND_AND_BLOCKED) {
					suspend_queue.remove(temp);
					suspendQueue_proIdToExistance[process_ID] = -1;
					//add to ready queue
					add_to_timerQueue(temp);
					temp->STATE = BLOCKED;
				} else if (temp->STATE == Waiting_For_RECEIVE) {
					(*error) = ERR_BAD_PARAM;
					return;
				} else if (temp->STATE == SUSPEND_AND_RECIVEING) {
					temp->STATE = Waiting_For_RECEIVE;

				}
			}
			(*error) = ERR_SUCCESS;
		} else {
			(*error) = ERR_BAD_PARAM;
		}
	} else {
		(*error) = ERR_BAD_PARAM;
	}
}