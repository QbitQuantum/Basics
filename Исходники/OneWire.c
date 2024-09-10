CAPTEUR *OneWire_ChercherPere(char *Id)
{
	CAPTEUR *Capteur;
	int i;
	BOOL bOK;


	//Parcours des capteurs
	for(Capteur=g_LstCapteur; Capteur!=NULL; Capteur = Capteur->Suivant)
	{
		bOK = TRUE;
		if(STRNICMP(Id, Capteur->Id, 15)!=0) bOK = FALSE;
		if(bOK == TRUE) return Capteur;
	}
	return NULL;
}