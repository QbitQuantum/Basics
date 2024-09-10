/* Code Principal */

int main(void)
{
	int ability,i,fhandle;
	char buffer[2000];
	DTA *mydta;
    char *pmodule;	   
	
	if ((mydta = (long)(Malloc(44))) == NULL)
	  {
	    printf("Erreur Reservation memoire !!!");
	    return -4;
	  }
	  
	Fsetdta(mydta);
	
	printf("\033E");

    /* Initialisation du DSP */

	ability=xbios(113);
	
	if ((Dsp_LoadProg(DSP_CODE,ability,buffer))==0)
	  printf("Chargement du code DSP = OK !!!\n");
	else
	  {
	     printf("Erreur de chargement du programme DSP !!!\n");
	     i=getchar();
	     return -1;
	  }
	  
	/* Chargement du module */
	  
	if (Fsfirst(MODULE,0) == 0)
      if ((pmodule=Malloc(TAILLE_BUFF+(mydta->d_length))) != NULL)
		{
          fhandle=Fopen(MODULE,0 );
		  Fread(fhandle,mydta->d_length,pmodule);
		  Fclose(fhandle);
		}
	  else
	    {
	      printf("Pas assez de memoire !!!\n");
	      i=getchar();
	      return -2;
	    }
	else
	  {
	    printf("Module introuvable\n");
	    i=getchar();
	    return -3;
	  }
	  
	/* Initialisation du player */

	printf("Un petit moment SVP...\n");
	
	if (Player_dtm(0,pmodule,pmodule+mydta->d_length)==-1)
	  {
	     printf("Erreur initialisation du module !!!");
	     i=getchar();
	     return -2;
	  }
	
	printf("Appuyez sur une RETURN...\n");
		