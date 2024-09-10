// Crée la liste chainée de shifts (1er lancement du programme)
Erreur initListeShift(Shift * * pPDebShift)
{
	FILE *fichierShifts;

	fopen_s(&fichierShifts, FICHIER_SHIFTS, "rb");

	if (fichierShifts == NULL)
	{
		return FICHIER_SHIFTS_INTROUVABLE;
	}
	else
	{
		ShiftFichier shiftLu;
		Shift *pShiftSauve = NULL;
		Erreur codeErreur;

		fread_s(&shiftLu, sizeof(ShiftFichier), sizeof(ShiftFichier), 1, fichierShifts);

		while (!feof(fichierShifts))
		{
			// from gestion.c
			codeErreur = ajoutShift(pPDebShift, &pShiftSauve, shiftLu.date, shiftLu.heure, 0, NULL);
			if (codeErreur == PAS_D_ERREUR)
			{
				fread_s(&shiftLu, sizeof(ShiftFichier), sizeof(ShiftFichier), 1, fichierShifts);
			}
			else
			{
				return codeErreur;
			}
		}

		fclose(fichierShifts);
		return PAS_D_ERREUR;
	}
}