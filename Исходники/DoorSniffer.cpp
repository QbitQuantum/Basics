int main(int argc, char *argv[]) {
  
     // This pin is not the first pin on the RPi GPIO header!
     // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     // for more information.
     int PIN = 2;
     int OPENDOOR = 3;
     int CLOSEDOOR = 4;
     time_t now1,now2;
     bool flag=false;
     
     if(wiringPiSetup() == -1) {
       printf("wiringPiSetup failed, exiting...");
       return 0;
     }

     int pulseLength = 0;
     if (argv[1] != NULL) pulseLength = atoi(argv[1]);

     mySwitch = RCSwitch();
     ledSwitch = RCSwitch();
     closeDoorLed = RCSwitch();
	 if (pulseLength != 0) mySwitch.setPulseLength(pulseLength);
     mySwitch.enableReceive(PIN);  // Receiver on interrupt 0 => that is pin #2
     ledSwitch.enableTransmit(OPENDOOR);
     closeDoorLed.enableTransmit(CLOSEDOOR);
    
     while(1) {
  
      if (mySwitch.available()) {
    
        int value = mySwitch.getReceivedValue();
    
        if (value == 0) {
          printf("Unknown encoding\n");
        } else {    
          if(value==5396){
             if(!flag){
                time(&now1); 
	     }
             flag = true;
             printf("Door is Open\n");
             ledSwitch.send(15,24);
             
          } else {
              if(flag){
                 time(&now2);
                 flag = false;
                 printf("Door was open for: %.f seconds\n",difftime(now2,now1));
              }
              printf("Door is Closed\n");
              closeDoorLed.send(15,24);
          }
        }
        mySwitch.resetAvailable();
    
      }
      
  
  }

  exit(0);


}