//ticsa *createIntegerCSA(uint **aintVector, uint textSize, char *build_options) {
int buildIntIndex (uint *aintVector, uint n, char *build_options, void **index ){
	uint textSize=n;	
	intVector = aintVector;  //global variable
	ticsa *myicsa;
	myicsa = (ticsa *) malloc (sizeof (ticsa));
	uint *Psi, *SAI, *C, vocSize;
	register uint i, j;
	uint nsHUFF;

	parametersCSA(myicsa, build_options);
	
	nsHUFF=myicsa->tempNSHUFF;
	
	// Almacenamos o valor dalguns parametros
	myicsa->suffixArraySize = textSize;
	myicsa->D = (uint*) malloc (sizeof(uint) * ((textSize+31)/32));	
	
	myicsa->samplesASize = (textSize + myicsa->T_A - 1) / myicsa->T_A;// + 1;
	myicsa->samplesA = (uint *)malloc(sizeof(int) * myicsa->samplesASize);
	myicsa->BA = (uint*) malloc (sizeof(uint) * ((textSize+31)/32));
	myicsa->samplesAInvSize = (textSize + myicsa->T_AInv - 1) / myicsa->T_AInv;
	myicsa->samplesAInv = (uint *)malloc(sizeof(int) * myicsa->samplesAInvSize);

	// Reservamos espacio para os vectores
	Psi = (uint *) malloc (sizeof(uint) * textSize);

	// CONSTRUIMOS A FUNCION C
	vocSize = 0;
	for(i=0;i<textSize;i++) if(intVector[i]>vocSize) vocSize = intVector[i];
	C = (uint *) malloc(sizeof(uint) * (vocSize + 1));	// Para contar o 0 terminador
	for(i=0;i<vocSize;i++) C[i] = 0;
	for(i=0;i<textSize;i++) C[intVector[i]]++;
	for (i=0,j=0;i<=vocSize;i++) {
		j = j + C[i];
		C[i] = j;
	}
	for(i=vocSize;i>0;i--) C[i] = C[i-1];
	C[0] = 0;

	// Construimos o array de sufixos (en Psi) - con quicksort
	printf("\n\t *BUILDING THE SUFFIX ARRAY over %d integers... (with qsort)", textSize);fflush(stdout);
	for(i=0; i<textSize; i++) Psi[i]=i;
	
	qsort(Psi, textSize, sizeof(uint), suffixCmp);
	
	
	printf("\n\t ...... ended.");


	// CONSTRUIMOS A INVERSA DO ARRAY DE SUFIXOS
	SAI = (uint *) malloc (sizeof(uint) * (textSize + 1));	// +1 para repetir na ultima posición. Evitamos un if
	for(i=0;i<textSize;i++) SAI[Psi[i]] = i;
	SAI[textSize] = SAI[0];

	// ALMACENAMOS AS MOSTRAS DO ARRAY DE SUFIXOS
	for(i=0;i<((textSize+31)/32);i++) myicsa->BA[i] = 0;
	for(i=0; i<textSize; i+=myicsa->T_A) bitset(myicsa->BA, SAI[i]);
	bitset(myicsa->BA, SAI[textSize-1]);			// A ultima posicion sempre muestreada
	//printf("TextSize = %d\n", textSize);
	myicsa->bBA = createBitmap(myicsa->BA, textSize);
	for(i=0,j=0; i<textSize; i++) if(bitget(myicsa->BA, i)) myicsa->samplesA[j++] = Psi[i];
	
	// ALMACENAMOS AS MOSTRAS DA INVERSA DO ARRAY DE SUFIXOS
	for(i=0,j=0;i<textSize;i+=myicsa->T_AInv) myicsa->samplesAInv[j++] = SAI[i];
	
	// CONSTRUIMOS E COMPRIMIMOS PSI
	printf("\n\t Creating compressed Psi...");
	for(i=0;i<textSize;i++) Psi[i] = SAI[Psi[i]+1];
	
	//FILE *ff = fopen("psi.log","w");
	//for (i=0;i<textSize;i++) fprintf(ff,"%d::%u",i,Psi[i]);
	//fclose(ff);	
	
	free(SAI);
	#ifdef PSI_HUFFMANRLE	
	myicsa->hcPsi = huffmanCompressPsi(Psi,textSize,myicsa->T_Psi,nsHUFF);
	#endif				
	#ifdef PSI_GONZALO	
	myicsa->gcPsi = gonzaloCompressPsi(Psi,textSize,myicsa->T_Psi,nsHUFF);
	#endif			
	#ifdef PSI_DELTACODES
	myicsa->dcPsi = deltaCompressPsi(Psi,textSize,myicsa->T_Psi);		
	#endif
  	free(Psi);	
	
	// Contruimos D
	for(i=0;i<((textSize+31)/32);i++) myicsa->D[i] = 0;	
	for(i=0;i<=vocSize;i++) bitset(myicsa->D, C[i]);
	myicsa->bD = createBitmap(myicsa->D,textSize);
	free(C);

	// VARIABLE GLOBAL QUE ALMACENA O ESTADO DOS DISPLAYS (IMPORTANTE PARA DISPLAY SECUENCIAL)
	// Almacena a última posición do array de sufixos que mostramos con display ou displayNext
	// Se nos piden un displayNext, aplicamos PSI sobre esta posición e obtemos a seguinte,
	// coa que podemos obter o símbolo pedido, e actualizamos displayState
	myicsa->displayCSAState = 0;
	myicsa->displayCSAPrevPosition = -2;  //needed by DisplayCSA(position)
	
	aintVector = intVector;
	// Liberamos o espacion non necesario

	*index = myicsa;
	//return (myicsa);
	return 0;
}