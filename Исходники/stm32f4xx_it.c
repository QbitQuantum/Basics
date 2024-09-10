/**
* @brief  This function handles Hard Fault exception.
* @param  None
* @retval None
*/
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
//	while (1)
//	{
//	}
	__NOP();
}