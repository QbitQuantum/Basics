static void
populatebynonzero(IloModel model, NumVarMatrix varOutput, NumVar3Matrix varHelp, Range3Matrix con)
{
	IloEnv env = model.getEnv();

	IloObjective obj = IloMaximize(env); //maximization function


	for (int j = current; j < current + J; ++j)
	{
		for (int k = 0; k < K; ++k)
		{
			
			obj.setLinearCoef(varOutput[j][k], 1.0);//add all variables to objective function, factor 1 
			
			//constraint 0: express value of output objective variables
			model.add(varOutput[j][k] + varHelp[j][k][2] - varHelp[j][k][3] == 0);

			//constraint 1: Td2a>=+Td2b
			model.add(varHelp[j][k][5] - varHelp[j][k][4] >= 0);

			//constraint 2: Tj>=Td2a + Tdc + Tblow
			model.add(varHelp[j][k][5] <= T[j] - Tdc - Tblow[j] - Tslack);

			//constraint 3: Td2b = Tfa+Tfd
			model.add(Tfd[k] == varHelp[j][k][4] - varHelp[j][k][3]);

			//constraint 4: Td1a >= Td1b
			model.add(0 <= varHelp[j][k][1] - varHelp[j][k][0]);

			//constraint 5: Tfb >= Td1a+Tdf
			model.add(Tdf[k] <= varHelp[j][k][2] - varHelp[j][k][1]);

			//constraint 6: Td1b = T(j-a)+Tcd
			model.add(T[j - a[k]] + Tcd == varHelp[j][k][0]);

			//constraint 7: Td1a >= Td2b(j-b) + Tloss, 1
			model.add(TlossD[k] <= varHelp[j][k][1] - varHelp[j - b[k]][k][4]);

			//constraint 8: Tfb >= Tfa(j-1)+Tloss, 2
			model.add(TlossF[k] <= varHelp[j][k][2] - varHelp[j - 1][k][3]);

			//constraint 9: at least X s for every load
			model.add(varOutput[j][k] >= TloadMin[k]);

		}
		//constraint 10: both spoons are picked up at same time at dropoff: Td2a,1 == Td2a,2
		model.add(varHelp[j][1][5] == varHelp[j][0][5]);

	}

	model.add(obj);
	

}