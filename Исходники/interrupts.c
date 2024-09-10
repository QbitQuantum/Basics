/*---------------------------------------------------------------------
	Function:	InterruptInit
	Purpose:	Initialisation of interrupt handling
	Arguments:	void
	Return:		void
---------------------------------------------------------------------*/
void InterruptInit(void)
{
	/* initialise vector tables */
	_init_vectab();
	/* enable external interrupts */
	_enable();
}