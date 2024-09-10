//
// Les entrées de la fonction d'asservissement
//
// Utilise les tableaux PosLRTA et VitLRTA, et pire encore, les modifie !!!
// Ils doivent donc etre mis a jour avant chaque appel !!!!!!!!!!!!!!!!!!!!
// Utilise également IntervalleTemps et VEqui
//
// Les sorties de la fonction d'asservissement
//
//--Modifie les valeurs du tableau Commande[]
void Asservissement_Controle() {

	// Calculer la commande en fonction de la position, de la vitesse, de la commande et des différents réglages
	//  (gains et systeme de prédiction) définis dans Params.c
	
	for (i = 0; i < 4; i++) {
		
		//
		// Récupération des données réelles
		//
		predPosLRTA[i] = PosLRTA[i];
		predVitLRTA[i] = VitLRTA[i];
		
		//
		// Mise é jour des intégrales
		//
		intLRTA[i] += IntervalleTemps * (ancLRTA[i] + PosLRTA[i] - 2.0F * ConsLRTA[i]) * 0.5F;
		ancLRTA[i] = PosLRTA[i];
	}
	
	

	//
	// Mise en mémoire de la commande actuelle pour s'en servir plus tard
	//
	histURT[indexHistorique][0] = ULRTA[1];
	histURT[indexHistorique][1] = ULRTA[2];
	indexHistorique++;
	if (indexHistorique == ESTIMATEUR_TEMPS_DE_REACTION + 1) {
		indexHistorique = 0;
	}

	//
	// Calcul de la commande future en anticipant sur les positions et vitesses futures
	//
	for (i = 0; i < ESTIMATEUR_TEMPS_DE_REACTION; i++) {

		//
		// Intégration des accélérations et vitesses suivant les lois de la dynamique
		//
		predVitLRTA[1] += ESTIMATEUR_GAIN_POUSEE * ESTIMATEUR_PAS_DE_TEMPS_MOYEN 
			* histURT[(indexHistorique + i) % (ESTIMATEUR_TEMPS_DE_REACTION + 1)][0];
		predVitLRTA[2] += ESTIMATEUR_GAIN_POUSEE * ESTIMATEUR_PAS_DE_TEMPS_MOYEN
			* histURT[(indexHistorique + i) % (ESTIMATEUR_TEMPS_DE_REACTION + 1)][1];
		
		predPosLRTA[1] += ESTIMATEUR_GAIN_INTEGRATION * ESTIMATEUR_PAS_DE_TEMPS_MOYEN * predVitLRTA[1];
		predPosLRTA[2] += ESTIMATEUR_GAIN_INTEGRATION * ESTIMATEUR_PAS_DE_TEMPS_MOYEN * predVitLRTA[2];
	}

	//
	// Calcul des commandes
	//
	for (i = 0; i < 4; i++) {
		if (CONTROLE_LRTA[i]) {
			ULRTA[i] = -GAINS_PRO[i] * (predPosLRTA[i] - ConsLRTA[i])
					- GAINS_DER[i] * predVitLRTA[i] - GAINS_INT[i] * intLRTA[i];
			
			if(i == 0) {
				// Bornage de la commande lacet
				if(ULRTA[0] > UL_MAX) {
					ULRTA[0] = UL_MAX;
					printf(" BUL");
				} else if(ULRTA[0] < UL_MIN) {
					ULRTA[0] = UL_MIN;
					printf(" BUL");
				}
				
			} else if(i == 3) {
				// Bornage de la commande altitude
				if(ULRTA[3] > UA_MAX) {
					ULRTA[3] = UA_MAX;
					printf(" BUA");
				} else if(ULRTA[3] < UA_MIN) {
					ULRTA[3] = UA_MIN;
					printf(" BUA");
				}
				
			} else {
				// Bornage des commandes R&T
				if(ULRTA[i] > URT_MAX) {
					ULRTA[i] = URT_MAX;
					printf(" BURT");
				} else if(ULRTA[i] < URT_MIN) {
					ULRTA[i] = URT_MIN;
					printf(" BURT");
				}
			}
		} else {
			ULRTA[i] = 0.0F;
		}
	}
	

	//
	// Assignation des commandes sur les différents moteurs
	//
	CPAA = Cos(PosLRTA[1]) * Cos(PosLRTA[2]); // Prise en compte des angles RT pour
	CPAA = 1.0F / CPAA;                       // calculer la poussée utile (projeté sur Z)

	Commande[0] = Vactu + CPA * CPAA * ULRTA[3] + CPL * ULRTA[0] + CPT * ULRTA[2];
	Commande[1] = Vactu + CPA * CPAA * ULRTA[3] + CPL * ULRTA[0] - CPT * ULRTA[2];
	Commande[2] = Vactu + CPA * CPAA * ULRTA[3] - CPL * ULRTA[0] + CPR * ULRTA[1];
	Commande[3] = Vactu + CPA * CPAA * ULRTA[3] - CPL * ULRTA[0] - CPR * ULRTA[1];
}