void SSIEIGEN::ErrorCalc()
{
	int i,j;
	double s_freq,s_form;

	char tmpbuf[256];

	if (ITL > ITLlastshift)
	{
		err_freq_old = err_freq;
		err_form_old = err_form;

		err_freq = 0;
		err_form = 0;
		for (i=0; i<nform; i++)
		{
			err_freq_mas[i] = abs((LM[tmpi[i]] - LMold[tmpi_old[i]])/LM[tmpi[i]]);
			err_form_mas[i] = abs((UFmax[tmpi[i]] - UFmaxold[tmpi_old[i]])/UFmax[tmpi[i]]);
		}
		for (i=0; i<nf; i++)
		{
			s_freq = abs((LM[tmpi[i]] - LMold[tmpi_old[i]])/LM[tmpi[i]]);
			s_form = abs((UFmax[tmpi[i]] - UFmaxold[tmpi_old[i]])/UFmax[tmpi[i]]);
			if ( low_err[tmpi[i]] == 0 && err_freq < s_freq) err_freq = s_freq;
			fprintf(fp,"low_err %d = %d\n",i,low_err[tmpi[i]]);
			fprintf(fp,"freq %d = %e   err_freq = %e  \n",i,LM[tmpi[i]],s_freq);
			
			if ( low_err[tmpi[i]] == 0 && err_form < s_form) err_form = s_form;
			fprintf(fp,"form %d = %e   err_form = %e  \n",i,UFmax[tmpi[i]],s_form);
			fprintf(fp,"\n");
			fflush(fp);
		}
	}
	_strtime_s( tmpbuf, 128 );
	fprintf(fp," TOLLERANCE  ITL = %d    freq = %f  form = %f      OS time:\t%s\n\n\n",ITL,err_freq,err_form,tmpbuf);
	fflush(fp);

//определение количества сошедшихся до требуемой точности частот, следующих подряд
	consecutive_convfreq = 0;
	for (i=0; i<nform; i++)
	{
		if ( err_freq_mas[i] < eps_freq )
		{
			consecutive_convfreq++;
		}
		else
		{
			break;
		}
	}

}