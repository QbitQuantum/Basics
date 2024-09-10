char *Ricerca_e_deriva(char *funzione_1, char *funzione_2, char *operatore, char *output)
	{
		output = (char *)malloc(sizeof(char)*10000);
		if ( strcmp(operatore,"x") == 0 || ( strcmp(operatore,"plus") != 0 && strcmp(operatore,"mul") != 0 && strcmp(operatore,"sot") != 0 && strcmp(operatore,"pow") != 0 ))
			output = D_Fondamentali(operatore); // Se il primo operando è una x oppure non è nessuna delle funzioni previste allora chiama D_Fondamentali 	
	
		if(strcmp(operatore,"pow") == 0)	//	Potenza
			output = Pow(funzione_1,funzione_2, output);
	
		if(strcmp(operatore,"mul") ==  0)	//	Prodotto
			output = Mul(funzione_1 ,funzione_2, output);	
		
		if(strcmp(operatore,"div") == 0)	//	Rapporto
			output = Div(funzione_1 ,funzione_2, output);	
		
		if(strcmp(operatore,"plus") == 0)	//	Somma
			output = Sum(funzione_1,funzione_2, output);
		
		if(strcmp(operatore,"sot") == 0)	//	Differenza
			output = Sot(funzione_1,funzione_2, output);

		if(strcmp(operatore,"sin") == 0)	//	Seno
			output = Sin(funzione_1, "", output);
		
		if(strcmp(operatore,"cos") == 0)	//	Coseno
			output = Cos(funzione_1, "", output);
		
		
		return output;		// Ritorno la funzione già derivata	
}