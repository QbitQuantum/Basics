void GraficoFluxSecund ( void )

	{
	float	volume = 0;

	float	far	*apt;

	inicFlux2 = inicFlux1;
	AtivaJanelaGrafica ( GRAF2,0 );
	clearviewport ();
	DesenhaEixos ( 25 , 235 , 10 , 110 , 0 , 36 , 40 , 12 );
	ScalaFluxSecund ();
	moveto ( 25 , 110 );
	apt = inicFlux2;
	volume = 0;
	for (; (*(apt + 1) != FIM) &&
		(apt < (inicFlux2 + NUMMAXPONTOSINF)) ; apt++)
		if (*apt != 4096)
			{
			volume += *apt / FREQ;
			lineto ( volume * 20 + 25 , *apt * (-3.0) + 74 );
			}
	lineto ( volume * 20 + 25 , 74 );
	CVF2 = CVF1;
	PeakFlow2 = PeakFlow1;
	VEF1DEUX = VEF1UN;
	TIFFDEUX = TIFFUN;
	FEF50DEUX = FEF50UN;
	FEF75DEUX = FEF75UN;
	FEF2575DEUX = FEF2575UN;
	FEF7585DEUX = FEF7585UN;
	CVFpercent2 = CVFpercent1;
	PeakFlowpercent2 = PeakFlowpercent1;
	VEF1percent2 = VEF1percent1;
	TIFFpercent2 = TIFFpercent1;
	FEF50percent2 = FEF50percent1;
	FEF75percent2 = FEF75percent1;
	FEF2575percent2 = FEF2575percent1;
	FEF7585percent2 = FEF7585percent1;
	VolumeExtDEUX = VolumeExtUN;
	TempoCurvaDEUX = TempoCurvaUN;
	MET2 = MET1;
	METpercent2 = METpercent1;
	ExibeParametrosDEUX ( 5 , 110 );
	DesativaJanelaGrafica ( GRAF2 );
	}