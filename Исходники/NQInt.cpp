//синус
NQInt NQInt::sin(int Err)
{//чтобы увеличить точноть расчета уменьшим его точность
	
	if (!NQInt(0).Compare(THIS)) return *(new NQInt(0));
	NQInt PI = NQInt(false);
	if (Err >= PI.underValueLeng)
		Err -= 1;//уменьшаем если на критической
	else Err++;//увеличиваем если мы не на критической отметке
	NQInt X = THIS %(PI+PI);
	X.errSize = errSize;
	X.Trancate(Err);
	X.deleteNullsItems();

	int n = 1;
	NQInt k;
	k.setErrSize(errSize);

	NQInt Eps(1);
	Eps.setErrSize(errSize);
	NQInt Resulted = X;
	Resulted.setErrSize(errSize);
	int SErr = Err;
	while (SErr > 0)
	{//Накопление погрешности
		Eps = Eps/NQInt(10);
		Eps.setErrSize(errSize);
		SErr--;
	}
	do 
	{//Ряд Тейлора
		bool posit = n%2 - 1;
		NQInt PreX = (X.pow(NQInt(2*n+1)));
		PreX.Trancate(Err);
		PreX.setErrSize(errSize);
		PreX.deleteNullsItems();
		k = (NQInt(2*n+1).Fact());
		k.Trancate(Err);
		k = PreX/k;
		k.deleteNullsItems();

		if (!posit) //определение положительности
		Resulted = Resulted - k; 
		else
		Resulted = Resulted + k;

		n++;

	} while (Eps.Compare(k) != 1);
	if (!Positive) Resulted.Positive = !Resulted.Positive;
	return Resulted;
}