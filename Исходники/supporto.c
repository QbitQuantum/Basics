void scatter(DATATYPE* local){
	/* puntatore file dei dati */
	FILE* input;
	/* puntatore alla matrice che verra scatterizzata */
	FILE* out;
	/* array di partizioni */
	DATATYPE* partitions[p];
	/* variabile temporanea per la la lettura del file */
	DATATYPE temp;
	/* indici per i cicli for */
	int i,j;
	/* indice di partizione e offset interno */
	int part_index,part_offset;
	/* array per le coordinate */
	part_id result;
	/* matrice su cui scrivo i dati letti da data */
	DATATYPE matrix[M];
	
	/* apertura del file dei dati */
	input = fopen(INPUT_MATRIX,"r");
	
	ec_meno1( input, "Problema nell'apertura del file dei dati\n" );
	ec_null( input, "Problema nell'apertura del file dei dati\n" );
	
#ifdef DEBUG	
	printf("SCATTER: \n");
#endif	
	/* inizializzazione partizioni */
	for(i = 0; i < p; i++ ){
		partitions[i] = malloc(sizeof(DATATYPE)* localsize);
	}
#ifdef DEBUG	
	printf("PARTIZIONI INIZIALIZZATE\n");
#endif		
	for(i=0; i< M; i++){
		/* leggo il prossimo elemento */
		fscanf(input,FORMAT,&temp);
		matrix[i]=temp;
		
		/* creazione delle coordinate*/
		result = offset2partition(dim,lato,s,i);
		
		/* assegnamento*/
		*(partitions[result.part_index]+result.part_offset) = temp;
		
	}/* LOOP i*/
#ifdef DEBUG	
	printf("RIEMPITE LE PARTIZIONI\n");		

	writeMatrix(SCATTER_MATRIX,matrix);
		
	printf("SCRITTA LA MATRICE SU FILE\n");
#endif		
	/* copio gli elementi nella mia partizione locale */
	for (i=0; i < localsize; i++){
		local[i] = *(partitions[0]+i);
	}
	
	/*invio le partizioni agli altri*/
	for (i=1; i < p; i++){
		if( MPI_Send(partitions[i],localsize, MPI_DATATYPE, i, TAG, MPI_COMM_WORLD) != MPI_SUCCESS ){
			fprintf(stderr,"Fallita la MPI_Send verso %d\n",i);
		}
	}
	
#if DEBUG
	printf("SCATTER TERMINATA\n");
#endif
	
}