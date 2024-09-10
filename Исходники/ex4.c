//void puts();
//void putc();
//void delay();
int main (void)
{
//configure uart
//ler buad
printStr("Insira o valor de baud");
int buad=readInt10();

//ler parity
printStr("paridade: ");
char parity=getChar();

//ler stopbits

printStr("Stop bits: ");
int stopbits=readInt10();

//configurar com os values pretedendidos

configure_UART(buad,parity,stopbits);

while(1)
return 0;

}//end main