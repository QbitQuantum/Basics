void chromosome::mutSelection(double probMut) {
	int ind, num;
	chromosome app(*this);
	int realNumR;

	bool trovato=true;
/*	if (numRul>minRule && Rand()<0.1)
	{	ind = Randint(0, numRul - 1);
		app.vettR[ind].index=dimMatWM;
		app.ordinaIndex();  //ordina gli indici e calcola il numRul
		app.faiMatdaVec();
		app.deleteDup();
		realNumR=app.numRul;
		if (realNumR >= minRule)
		{	if (!CLASSIFICATION)
				copyChrom(app);
			else
				if (controllaPresenzaClassi((int**)app.matR,app.numRul))
					copyChrom(app);
		}
	}*/

	if (dimMatWM > maxRule && Rand() < 0.1)  //modifico o aggiungo una regola
	{
		ind = Randint(0, maxRule - 1);	//elemento del vettore da modificare
		while(trovato)
		{	num = Randint(0, dimMatWM - 1);	//seleziono una regola che non e' gia' presente
			trovato=false;
			for (int i=0;i<numRul;i++)
			if (app.vettR[i].index==num)
			{	trovato=true;
				break;
			}
		}
		app.vettR[ind].index = num;
		/*if (app.vettR[ind].index==dimMatWM)	//sto aggiungendo
		{	*/
		for (int i=0;i<numVar-1;i++)
			if(matWM[num]!=0)
				app.vettR[ind].vectAnt[i]=true;
			else
				app.vettR[ind].vectAnt[i]=false;

		//}

		app.ordinaIndex();  //ordina gli indici e calcola il numRul

		app.faiMatdaVec();
		app.deleteDup();

		realNumR=app.numRul;
		if (realNumR >= minRule)
		{	if (!CLASSIFICATION)
				copyChrom(app);
			else
				if (controllaPresenzaClassi((int**)app.matR,app.numRul))
					copyChrom(app);
		}
	}

	int conta = 0;
	if (SIZE_POP_PR && Rand() < 0.7)
	{	ind = Randint(0, app.numRul - 1);
		for (int i = 0; i < numVar-1; i++)
			if (matWM[ind][i]!=0 && Rand() < (double) 2 / (numVar-1))
				app.vettR[ind].vectAnt[i] = !app.vettR[ind].vectAnt[i];

		for (int i = 0; i < numVar-1; i++)
			if (app.vettR[ind].vectAnt[i] != 0)
				conta++;
	}
	if (conta >= minTerms)
	{	app.faiMatdaVec();
		app.deleteDup();
		realNumR=app.numRul;
		if (realNumR >= minRule)
		{	if (!CLASSIFICATION)
				copyChrom(app);
			else
				if (controllaPresenzaClassi((int**)app.matR,app.numRul))
					copyChrom(app);
		}
	}
}