/***************************************************************************
Child main program
***************************************************************************/
int child_main(Controller* ctlPtrChild) {
   struct timespec lastSleep;
   long PWMcounter;
   long beepCounter;
   int PWM;
      
   //make sure output is not buffered (this program generally a child to a nodejs program) and set signal handler
   setbuf(stdout, NULL);
   setbuf(stderr, NULL);
   signal(SIGINT, sig_handler_child);
   signal(SIGTERM, sig_handler_child);
   
   PWMcounter = 0;
   beepCounter = 0;
   clock_gettime(CLOCK_MONOTONIC, &lastSleep);  //capture current time as time of 'last sleep'
   while (1) {
      sync_clock_delay(PWMCycle_ns, &lastSleep);
      PWM = (int)(ctlPtrChild->out + 0.5);
      PWMcounter++;
      // PWMcounter %= 100;
      if (PWMcounter == 100) {
         // printf("PWM: %d, Out: %f\n",PWM, ctlPtrChild->out);
         PWMcounter = 0;
         pidControl(ctlPtrChild); //run PID algorithm
         printJSON(ctlPtrChild); //send data out formatted as JSON
      }
      if (PWMcounter < PWM) {
         GPIO_SET = 1<<SSR1_GPIO; //turn on SSR pin
      } else {
         GPIO_CLR = 1<<SSR1_GPIO; //turn off SSR pin
         // printf("SSR Off. PWM: %d, PWMcounter: %d, Out: %f\n", PWM, PWMcounter, ctlPtrChild->out);
      }
      //Manage beeper
      ctlPtrChild->beep_mode = BEEP(ctlPtrChild->beep_mode);
   }
}