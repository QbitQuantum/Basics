/****************************************************************
*																*
*			cr‚e un fichier vide d'une taille donn‚e			*
*																*
****************************************************************/
void creer_fichier(void)
{
	OBJECT *file_size;
	char nom[FILENAME_MAX] = "EMPTY.NEW", text[FILENAME_MAX];
	int ex, size, handle;

	if(!selecteur(nom, NULL, Messages(TAMPON_1)))
		return;

	sprintf(text, Messages(TAMPON_2), nom);
	ajoute(Firstwindow, text);

	rsrc_gaddr(R_TREE, TAILLE_FICHIER, &file_size);
	strcpy(file_size[CREATE_FILE_SIZE].ob_spec.tedinfo -> te_ptext, "1");

	ex = xdialog(Dialog[TAILLE_FICHIER].tree, NULL, NULL, NULL, TRUE, TRUE, DialogInWindow ? AUTO_DIAL|MODAL|NO_ICONIFY : FLY_DIAL|MODAL|NO_ICONIFY|SMART_FRAME);

	if (ex == CREATE_FILE_ANNU)
	{
		ajoute(Firstwindow, Messages(TAMPON_3));
		return;
	}

	size = atoi(file_size[CREATE_FILE_SIZE].ob_spec.tedinfo -> te_ptext);

	if ((handle = (int)Fcreate(nom, 0)) >! 0)
	{
		int i, err;
		char buffer[512];

		for (i=0; i<512; i++)	/* efface le buffer */
			buffer[i] = '\0';

		for (i=0; i<size; i++)	/* copie 'size' fois le buffer */
			if ((err = (int)Fwrite(handle, 512L, buffer)) < 0)
			{
				error_msg(err);
				break;
			}

		Fclose(handle);

		sprintf(text, Messages(TAMPON_4), nom, size*512L);
		ajoute(Firstwindow, text);

		if (nom[1] == ':')
			change_disque(toupper(nom[0]) -'A', TRUE);
	}
	else
	{
		error_msg(handle);
		sprintf(text, Messages(TAMPON_5), nom);
		ajoute(Firstwindow, text);
	}
} /* creer_fichier */