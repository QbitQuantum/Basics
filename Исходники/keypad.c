int main(void) {
  SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);//1024hz = 15625
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);
  GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_3);
  GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
  GPIOPinConfigure(GPIO_PB1_U1TX);
  GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_1);
  UARTConfigSetExpClk(b1, SysCtlClockGet(), 9600, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
  UARTEnable(b1);

  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);


  GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, (GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_1));
  GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
  frequency = SysCtlClockGet()/2;

  changeCursorUnderscore();
  toggleLED();


  //Clear Display
  clearDisplay();
  //putPhrase("Hello World!");
  //Timer Configuration
  TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
  TimerLoadSet(TIMER0_BASE, TIMER_A, frequency);
  TimerControlEvent(TIMER0_BASE, TIMER_A, TIMER_EVENT_POS_EDGE);
  TimerEnable(TIMER0_BASE, TIMER_A);

  //Timer Interrupt Enable
  TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  TimerIntRegister(TIMER0_BASE, TIMER_A, timer_interrupt);


  while(1){
    if(flag = 1){  
    //Reset the line read
      code = 0;

    //Turn on the scan for a line
      if(counter == 0) GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x8);
      if(counter == 1) GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0x10);
      if(counter == 2) GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0x20);
      if(counter == 3) GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0x40);

    //Check which button on the line was pressed
      if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_5) == 0x20) {
        code = 1;
        temp = log_code;
      }
      if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_6) == 0x40) {
        code = 2;
        temp = log_code;
      }
      if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_7) == 0x80) {
        code = 3;
        temp = log_code;
      }

    //Turn off the scan for a line
      if(counter == 0) GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x0);
      if(counter == 1) GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0x0);
      if(counter == 2) GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0x0);
      if(counter == 3) GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0x0);

    //Check the next line on the next run and if overflows, reset


    //Calculate the index_code for the lookup table
      index_code = temp + code;
      key_char = lookup_table[index_code];
      log_code = log_code + 4;
      if(log_code > 12){
        log_code = 0;
      }

      counter++;
      if(counter > 3) counter = 0;
      if(key_char != 'x'){
        //toggleLED();
        putChar(key_char);
      //SysCtlDelay(100000);
        index_code = 0;
      }
      flag = 0;
    }
  }

}