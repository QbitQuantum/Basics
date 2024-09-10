/**********************************************************
 *  Function: controller
 *********************************************************/
void *controller(void *arg)
{    
	
	char request[10];
	char answer[10];
	MIXER_STATE = 0;
	TIME_LAST_CHANGE_MIXER = time(NULL);
	
    // Endless loop
	memset(request,'\0',10);
	memset(answer,'\0',10);
    
	struct timespec timeInit, timeEnd, timeDiff, timePeriod;
	timePeriod.tv_sec = (time_t) TIME_SEC_CYCLE_SECONDS;
	timePeriod.tv_nsec = (long) TIME_SEC_CYCLE_NANOSECONDS;
	
	while(1) {
//    	- Lectura de la pendiente actual
    	if(read_slope(request, answer) == 2) {
    		printf("Error in read slope");
    	}
    	
    	
//    	- Lectura de la velocidad actual
    	if(read_speed(request, answer) == -1.0) {
    		//Error
    		printf("Error in read speed");
    	}
    	
    	
//    	- Activar el acelerador
    	if(gas_turn(request, answer) != 0 ) {
			//Error
			printf("Error in break. Current value = ");
		}
    	
    	
//    	- Activar el freno
    	if(break_turn(request, answer) != 0 ) {
			//Error
			printf("Error in break. Current value = ");
		}
    	
    	
//    	- Activar el Mezclador
    	if(mixer_turn(request, answer) != 0 ) {
			//Error
			printf("Error in break. Current value = ");
		}
    	
		sec_cycle = (sec_cycle + 1) % TOTAL_SEC_CYCLES;
    	clock_gettime(CLOCK_REALTIME, &timeEnd);
    	
    	diffTime(timeEnd, timeInit, &timeDiff);
    	diffTime(timePeriod, timeDiff, &timeDiff);
    	nanosleep(&timeDiff, NULL);
		addTime(timeInit, timePeriod, &timeInit);		
    }
    //return (0);
}