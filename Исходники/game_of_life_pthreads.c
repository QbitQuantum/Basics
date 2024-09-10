//===================================
// Function Start
//===================================
int main (void)
{
	init ();
	ThreadInit();
	LifeGame();
#ifndef __NOOUTPUT
	Out ();
#endif
	
	Terminate ();
	
	return 0;
}