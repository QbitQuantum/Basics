static gboolean read_sample_2columns_file(GabeditFileChooser *SelecFile, gint response_id)
{
 	gchar t[BSIZE];
 	gboolean OK = TRUE;
	gint numberOfFrequencies = 0;
	gdouble* frequencies = NULL;
	gdouble* intensities = NULL;
	gchar *FileName;
 	FILE *fd;
	gdouble a;
	gdouble b;
	int ne = 0;

	if(response_id != GTK_RESPONSE_OK) return FALSE;
 	FileName = gabedit_file_chooser_get_current_file(SelecFile);

 	fd = FOpen(FileName, "rb");
	if(!fd) return FALSE;

 	while(!feof(fd))
	{
	 	if(!fgets(t,BSIZE,fd))break;
		ne = sscanf(t,"%lf %lf",&a,&b);
		if(ne==2)
		{
			numberOfFrequencies++;
			frequencies = g_realloc(frequencies, numberOfFrequencies*sizeof(gdouble));
			intensities = g_realloc(intensities, numberOfFrequencies*sizeof(gdouble));
			frequencies[numberOfFrequencies-1] = a;
			intensities[numberOfFrequencies-1] = b;
		}
 	}

	if(numberOfFrequencies>0)
	{
		createRamanSpectrumWin(numberOfFrequencies, frequencies, intensities);
	}
	else
	{
		OK = FALSE;
		messageErrorFreq(FileName);
	}


	if(frequencies) g_free(frequencies);
	if(intensities) g_free(intensities);
	fclose(fd);
	return OK;
}