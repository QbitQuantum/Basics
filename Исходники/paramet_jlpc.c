float TramaParametriza(Ttrastero *trastero,TTrastero2 *trastero2,int32 nframes, Tparamet *paramet)
	{
   float total;
   FILE *fp;
   static int gendatos = 0;

   if (gendatos == 0)
     {
     fp = fopen("datospar.sal", "wt");
     fprintf(fp, "Coef preenf:          %f\n", __coef_preenf);
     fprintf(fp, "Coef rasta :          %f\n", __coef_rasta);
     fprintf(fp, "Coef preenf rasta:    %f\n", trastero->preenf);
     fclose(fp);
     }
   else
     gendatos = 1;

	VectorImprimir("jlpc.dep",nframes,trastero->a,__long_ventana,"antes preenf...");
	//VectorImprimir("jlpc.dep",nframes,trastero->hamwei,__long_ventana,"hamwei");
	Hamm_Preenf(trastero->a, trastero->hamwei,__coef_preenf);
	VectorImprimir("jlpc.dep",nframes,trastero->a,__long_ventana,"tras preenf...");

	/* CÁLCULO DE LA FFT PARA CADA TRAMA */
   realfft(__fft_points,trastero->a);

   Energia(trastero->a,trastero->c,__fft_points/2,trastero->y);
	VectorImprimir("jlpc.dep",nframes,trastero->c,__fft_points/2,"FFT");

   total=Promedio(trastero->c,__fft_points/2);
   total=10*LOG10(total);

  __energias[nframes]=paramet->mfc[0][nframes][__numParam-1]=trastero->nmfc[nframes][__numParam-1]=total;
  //__ErrMsg(stderr,"mfcc y energ'ia\n");

	/* ENERGÍA EN CADA FILTRO */
	plp(trastero->pptr.nfilts, trastero->filwei, trastero->ibegen, trastero->c,
       trastero->sp, trastero->splog, nframes, trastero->filtertype);
	VectorImprimir("jlpc.dep",nframes,trastero->splog[nframes],
                  trastero->pptr.nfilts,"LogEnergBand tras PLP");
  //__ErrMsg(stderr,"plp\n");
  /* RASTA FILTERING AND RASTA MEL */

  rasta_trama (trastero->pptr.nfilts, trastero->preenf, trastero->sp,
               trastero->splog, trastero->spfilt, nframes, paramet->mfc,
               trastero->nmfc,trastero->filtertype, trastero->_melNum,&(trastero->pptr));
  if (nframes>=4)
  		{
		VectorImprimir("jlpc.dep",nframes-4,trastero->splog[nframes-4],trastero->pptr.nfilts,"LogEnergBand2 tras PLP");
		VectorImprimir("jlpc.dep",nframes-3,trastero->splog[nframes-3],trastero->pptr.nfilts,"LogEnergBand2 tras PLP");
		VectorImprimir("jlpc.dep",nframes-2,trastero->splog[nframes-2],trastero->pptr.nfilts,"LogEnergBand2 tras PLP");
		VectorImprimir("jlpc.dep",nframes-1,trastero->splog[nframes-1],trastero->pptr.nfilts,"LogEnergBand2 tras PLP");
		VectorImprimir("jlpc.dep",nframes,trastero->splog[nframes],trastero->pptr.nfilts,"LogEnergBand2 tras PLP");
		VectorImprimir("jlpc.dep",nframes,trastero->spfilt[nframes],trastero->pptr.nfilts,"LogEnergBand tras rasta");
      VectorImprimir("jlpc.dep",nframes,paramet->mfc[0][nframes],trastero->_melNum,"parrasta");
      }
  if (paramet->n_codeBooks > 1)
  	{
   __CalculaDelta_trama (paramet, nframes-DELTA,trastero2);
  if (nframes>=DELTA)
      VectorImprimir("jlpc.dep",nframes-DELTA,paramet->mfc[1][nframes-DELTA],trastero->_melNum,"delta parrasta");
   }
	//falta un factor 2 PI? parece que no
  return total;
  }