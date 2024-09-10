void GraficoEspSecund ( void )

	{
	int	col;

	float	far	*apt;

	inicEsp2 = inicEsp1;
	AtivaJanelaGrafica ( GRAF2 );
	clearviewport ();
	DesenhaEixos ( 25 , 235 , 10 , 110 , 0 , 0 , 50 , 12 );
	ScalaEspSecund ();
	moveto ( 25 , 62 );
	apt = inicEsp2;
	col = 25;
	for (; (*apt != FIM) && (apt < (inicEsp2 + NUMMAXPONTOS - 40)) ;
		apt += 40 , ++col)
		lineto ( col , 62 - *apt * 12 );
	CapacVital2 = CapacidadeVital;
	CapacInspi2 = CapacidadeInspiratoria;
	VolResExpi2 = VolumeReservaExpiratorio;
	CVpercen2 = CVpercent;
	gprintf ( 5 , 160 , "Param.  Teorico   Calculado   %%");
	gprintf ( 5 , 170 , " CV     %7.2f       %6.2f	 %5d" ,
		CVteorico , CapacVital2 , (int)(CVpercen2 + 0.5) );
	gprintf ( 5 , 180 , " CI        -        %6.2f     -" , CapacInspi2 );
	gprintf ( 5 , 190 , " VRE       -        %6.2f     -" , VolResExpi2 );
	DesativaJanelaGrafica ( GRAF2 );
	}