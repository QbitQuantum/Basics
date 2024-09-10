void main(){
   setup_oscillator( OSC_8MHZ );
   setup_adc_ports(sAN6|VSS_VDD);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_counters(RTCC_INTERNAL,RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

//Software workaround for the power switch floating
onewire_init();
onewire_sendbyte(0xCC);
onewire_sendbyte(0x6C);    //Write Data Command
onewire_sendbyte(0x31);    //Eeprom address but actually gets written to Shadow Ram
onewire_sendbyte(0xE7);    //Value to make PMOD1 SWEN=0 RNAOP=0

//Copy the shadow Ram written above over to actual EEPROM
onewire_init();
onewire_sendbyte(0xCC);
onewire_sendbyte(0x48);    //send the copy command
onewire_sendbyte(0x30);    //copy shadow ram to the block containing 31

while(true){
/*-------------------------------------------------------------------
Pull Reading From Temp Probe
-------------------------------------------------------------------*/
//Use the following to determine the state of the one wire net
//Will report if device present, not, or shorted
//Comment out rest of code
//onewire_init_with_error_check();
//read_status();
//printf("status byte is ====>(%x)\n\r",status);
printf("Please enter a command (h for help):\n\r");

command = getc();  //Gets a key from the keyboard
   switch (command){
   case 'h' :
         printf("Type any of the following commands:\n\r");
         printf("h     This Help Message\n\r");
         printf("C     Ambiant Temp in deg. C\n\r");
         printf("c     Ambiant Temp in deg. C(No Formatting)\n\r");
         printf("F     Ambiant Temp in deg. F\n\r");
         printf("f     Ambiant Temp in deg. F(No Formatting)\n\r");
         printf("N     64 bit node address in Hex\n\r");
         printf("K     Thermo millivolts\n\r");
         printf("k     Thermo millivolts(No Formatting)\n\r");
         printf("s     One line scroll test\n\r");
         break;
   case 'C' :
         read_temp();
         printf("    deg C===>(%3.2f)\n\r",temp_float);
         break;
   case 'c' :
         read_temp();
         printf("%3.2f\n\r",temp_float);
         break;
   case 'F' :
         read_temp();
         printf("    deg F===>(%3.2f)\n\r",temp_float_faren);
         break;
   case 'f' :
         read_temp();
         printf("%4.2f",temp_float_faren);
         break;
   case 'K' :
         read_current();
         printf("mV===>(%4.3f)\n\r",current_float);
         break;
   case 'k' :
         read_current();
         printf("%4.3f\n\r",current_float);
         break;
   case 's' :
         scroll_test();
         break;
   default :
         printf("Not a valid command:\n\r");
         }
         
delay_ms(1000);
}
}