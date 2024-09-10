 void _IOFF (void) {  // Disable (close) Hardware Interrupts
#ifdef	Watcom
 	_disable();
#endif
 }