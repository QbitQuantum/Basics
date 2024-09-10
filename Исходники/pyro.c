void main(){

setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256);
setup_timer_1(T1_DISABLED);
setup_oscillator (OSC_8MHZ);
setup_adc_ports(NO_ANALOGS|VSS_VDD);
setup_adc(ADC_OFF);
setup_comparator(NC_NC_NC_NC);
setup_vref(FALSE);

//Software workaround for the power switch floating
/*
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
*/
for (i=1;i<5;i++){
output_high(pin_A4);
delay_ms(250);
output_low(pin_A4);
delay_ms(250);
}

while(true){

//Use the following to determine the state of the one wire net
//Will report if device present, not, or shorted
//Comment out rest of code
//onewire_init_with_error_check();
//read_status();
//printf("status byte is ====>(%x)\n\r",status);
//printf("Please enter a command (h for help):\n\r");

//Waits for a command to come in over the serial port   
//printf("Enter Command\n\r");
//Base commands are:
//N =  Print out the net address of one attached sensor
//K =  Return the current in micro volts
//C =  Return the chip temperature in celsius
//F =  Return the chip temperature in fahrenheit
if (interactive == 1)
   printf("Enter Command:\n\r");
gets(command);
//Check to see if controller is present   
if (command[0] == 'p'){
   printf("Pyro Logger found and responding...\n\r");
   printf("Firmware Version 1\n\r");
   printf("N - Get Net address\n\r");
   printf("Kaddress - Thermo uV's\n\r");
   printf("Caddress - Temp in C\n\r");
   printf("Faddress - Temp in F\n\r");
   printf("i - toggle interactive\n\r");
   interactive = 1;
}

if (command[0] == 'i'){
   interactive = 0;
}



//Print out the Net address for configuring other software   
if (command[0] == 'N'){
   printf("Reading Net Address...\r\n");
         read_netaddress();
}
//****************************************************
//READ Current from Sensor
//****************************************************
if (command[0] == 'K'){
   
//Initialize the Temporary Buffer and make sure you have the null char
tmp_buff[0]='0';
tmp_buff[1]='X';
tmp_buff[2]='0';
tmp_buff[3]='0';
tmp_buff[4]='\n';
   
   i=0;
   for(j=1; j<=15; j+=2) {
   tmp_buff[2]=command[j];
   tmp_buff[3]=command[j+1];
   address_array[i]=ATOI(tmp_buff);
   i++;   
}
onewire_init();
onewire_sendbyte(0x55);  //Transmit skip Rom Command
//Unique 64 Bit address
for(j=0; j<=7; j++)
{
onewire_sendbyte(address_array[j]);
}
onewire_sendbyte(0x69);  //0x69 Transmit Read RAM command
onewire_sendbyte(0x0E); //Transmit Read start address
data_MSB=onewire_readbyte();
data_LSB=onewire_readbyte();
//printf("MSB ====>(%x)\n\r",data_MSB);
//printf("LSB ====>(%x)\n\r",data_LSB);
current=make16(data_MSB,data_LSB);
current=current >> 3;
current_float=(current*.000015625);
printf("%4.7f\r\n",current_float);
blink();
}

//***********************************************************
//Read Temperature of the on Chip Sensor
//***********************************************************
//DS2760 can measure 0.125 deg C per bit
//Whole number temperature values can be had by simpling taking the high byte
//Or if high and low bytes are used shift right 5 places and multiply by .125 in a float

if (command[0] == 'C' || command[0] == 'F'){
//Initialize the Temporary Buffer and make sure you have the null char
tmp_buff[0]='0';
tmp_buff[1]='X';
tmp_buff[2]='0';
tmp_buff[3]='0';
tmp_buff[4]='\n';

//Pull the address out of the command 8 bytes of HEX
//Changes it from a string  to array stuffed in address_array   
   i=0;
   for(j=1; j<=15; j+=2) {
   tmp_buff[2]=command[j];
   tmp_buff[3]=command[j+1];
   address_array[i]=ATOI(tmp_buff);
   i++;   
}

//Send the addresss down the One Wire Buss
onewire_init();
onewire_sendbyte(0x55); //Match Net Address Command 
for(j=0;j<=7;j++){
onewire_sendbyte(address_array[j]);
}

//Read Data
onewire_sendbyte(0x69);  //0x69 Transmit Read RAM command
onewire_sendbyte(0x18); //Transmit Read start address
data_MSB=onewire_readbyte();
data_LSB=onewire_readbyte();
temp=make16(data_MSB,data_LSB);

//Check for a negative temperature for cold junction.  Really cold junction 
//can only be positive or zero.  Cold junction reference should never fall below zero
//so if its below zero  make it zero, about the best we could do aside throwing up errors
//To force temperature negative for testing uncomment below
//temp = temp + 32768;

//The Check
if (bit_test(temp,15) == 1)
   temp = 0;

/*
//Bit Shift Math For Whole Number Only
temp=temp>>8;
temp_float = temp;
*/
//Shift the data 5 bits to the right
temp=temp >> 5;

//Math for celsius
temp_float=(temp *.125);
//Math for fahrenheit
temp_float_faren=((temp_float * 1.8) + 32);


//Print out either celsius or fahrenheit
//Over the serial Port
if (command[0] == 'C' )
   printf("%3.2f\r\n",temp_float);
if (command[0] == 'F' )
   printf("%3.2f\r\n",temp_float_faren);
   
//Flash the leds to show there is communication
blink();
}