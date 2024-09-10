/*----------------------------------------------------------------------
  hbInkey
  ----------------------------------------------------------------------*/
int hbInkey(int Tijdsduur)
{

  int Toets;
  time_t BeginTijd=0;
  char HuidigeTijd[9];

  Tijdsduur++;   /* WEGHALEN !!!!! alleen om warning te vermijden. */
  /* BeginTijd=time(NULL); */

  for(;;) {
	 /* Doe van alles en nog wat. */
	 /* Kijk of er een muistoets is ingedrukt etc. */
	 if ((time(NULL)-BeginTijd) >= 1) {
		_strtime(HuidigeTijd);
		hbPrint(TijdY,TijdX,HuidigeTijd,Kleur);
		BeginTijd=time(NULL);
	 }

	 if (bioskey(1)>0) {
		Toets=bioskey(0);
		Toets=((Toets & 0xff)==0 ? -(Toets>>8) : (Toets & 0xff));

		if (Toets==K_F1)
		  Help();
		else
		  break;
	 }
  }