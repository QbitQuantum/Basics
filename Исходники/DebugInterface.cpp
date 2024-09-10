time DebugInterface::printTimeDet( time input, bool newline )
{
#if SentioEM_Emulator_Interface == OFF && SentioEM_Debug_Interface == ON

	printLine("\n\rSec:", false );
	printDecimal( input.getSecond(), false );
	printLine(" Min:", false );
	printDecimal( input.getMinute(), false );
	printLine(" Hr:", false );
	printDecimal( input.getHour(),false );

	if( newline )
	{
		USART_Tx( DEBUG_USART, '\n' );
		USART_Tx( DEBUG_USART, '\r' );
	}

	while( !( DEBUG_USART->STATUS & USART_STATUS_TXC ) );
#endif

	return input;
}