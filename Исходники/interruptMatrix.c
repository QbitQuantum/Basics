interrupt void port1ISR(){
	_disable_interrupts();
	msdelay(20); // delay for 20 ms
	ISRc = getC();
	P1IFG &= ~(ALLROWS); // clears the interrupt flag
	_enable_interrupts();
}