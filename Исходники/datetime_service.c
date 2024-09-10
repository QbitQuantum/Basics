PROCESS_THREAD(datetime_service_process, ev, data) {

    static struct etimer update_timer;
    static int valid_counter;

    PROCESS_BEGIN();

    timestamp = 0;
    time_valid = false;
    valid_counter = VALID_TIME;

    etimer_set(&update_timer, CLOCK_SECOND * UPDATE_INTERVALL);

    while(1) {
        PROCESS_WAIT_EVENT();

        if(ev == PROCESS_EVENT_TIMER) {
            PRINTF("Time: %d:%d:%d\t%d.%d.%d Day: %d Valid: %d\n", current_dt.hour, current_dt.minute, current_dt.second, current_dt.day, current_dt.month, current_dt.year, current_dt.weekday, time_valid);

            if(etimer_expired(&update_timer)){
                etimer_reset(&update_timer);
            }

            timestamp++; // update timestamp

            if(valid_counter < VALID_TIME) {
                valid_counter+=1;
            } else {
                time_valid = false;
            }

            current_dt.second+=1;
            if(current_dt.second > 59) {
                current_dt.second = 0;
                current_dt.minute+=1;
                if(current_dt.minute > 59) {
                    current_dt.minute = 0;
                    current_dt.hour+=1;
                    if(current_dt.hour > 23) {
                        current_dt.hour = 0;
                        current_dt.day+=1;
                        current_dt.weekday+=1;
                        if(current_dt.weekday>6) {
                            current_dt.weekday=0;
                        }
                        if( ((current_dt.month==1||current_dt.month==3||current_dt.month==5||current_dt.month==7||current_dt.month==8||current_dt.month==10||current_dt.month==12)&&current_dt.day>31) || ((current_dt.month==4||current_dt.month==6||current_dt.month==9||current_dt.month==11)&&current_dt.day>30) || (current_dt.month==2 && current_dt.day>28)) { //TODO Schaltjahre >.<
                            current_dt.day=0;
                            current_dt.month+=1;
                            if(current_dt.month>12) {
                                current_dt.month=0;
                                current_dt.year+=1;
                            }
                        }
                    }
                }
            }
        } else if(ev == dt_update_event) {
            PRINTF("Time: Got update.\n");

            current_dt = *(struct datetime*)&(((struct hxb_envelope*)data)->value.data);
            time_valid = true;
            valid_counter = 0;

            etimer_restart(&update_timer);
            free(data);
        }
    }
    PROCESS_END();
}