// Start ISR, Fill array, Return array, Stop ISR
uint8 ultrasonic_get_reading(UltrasonicReading *reading) {
    
    int i, j;
    char depth[DEPTH_STRING_LENGTH], s[MAX_STRING_LENGTH];

    // Reset variables
    (*reading).valid = 0u;
    (*reading).temp = -9999;    
    (*reading).depth = -9999;
    uart_ultrasonic_string_reset();

    isr_byte_ultrasonic_rx_StartEx(isr_byte_ultrasonic_rx); // Start the ISR to read the UART
    ultrasonic_power_on();                                  // Power on the sensor
    CyDelay(1500u);                                         // Wait for UART to get readings from sensor
    
    isr_byte_ultrasonic_rx_Stop();                          // Stop the ISR to read the UART
    ultrasonic_power_off();                                 // Power off the sensor

    // store relevant strings to ultrasonic_packet
    strcpy(s,uart_ultrasonic_received_string);
    /*
    for(i = 0; i < strlen(uart_ultrasonic_received_string); i++){
        s = uart_ultrasonic_received_string[i];
        
        if(R_count > 4 && s == '\r'){
            (*reading).valid = 1u;
            break; 
        }else if(R_count > 4){
            depth[index] = s;
            index++;
        }
        if(s == 'R'){
            R_count++;      // increment everytime an "R" ascii character is encountered
        }
    }
    */

    for(i = 0; i < MAX_STRING_LENGTH-1-DEPTH_STRING_LENGTH; i++){
        if( s[i] == 'R' && s[i+1+DEPTH_STRING_LENGTH] == '\r' ) {
            for(j = 0; j < DEPTH_STRING_LENGTH; j++) {
                depth[j] = s[i+j+1];
            }
            (*reading).valid = 1u;
            break;
        }
    }
    
    if ((*reading).valid) {
        (*reading).depth = strtof(depth,(char **) NULL); //(float)atof(depth);
/*        
        //(*reading).depth = (float) ultrasonic_depth;
        if ((*reading).depth > 9999) { // Recorded depth greater than 4 digits... (eg 13582 vs 1358)
            (*reading).depth = (float) (int)( (*reading).depth  / 10) ;
            
            debug_write("Ultrasonic Warning.  depth > 5 digits.  Truncated depth reported.");
            debug_write(uart_ultrasonic_received_string);           
        }
    }    
    else if(R_count <= 4){
        debug_write("Ultrasonic No Reading Found.  R_count <= 4.");
        debug_write(uart_ultrasonic_received_string);
*/        
    }
    else {
        debug_write("Ultrasonic Invalid Reading.");
        debug_write(uart_ultrasonic_received_string);
    }
    
    return (*reading).valid;
}