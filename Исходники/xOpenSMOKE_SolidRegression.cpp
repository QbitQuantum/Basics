void OpenSMOKE_SolidRegression::ModelOdeRegression(int model, int ex, BzzVector &b, BzzVector &x, BzzVector &y)
{
	int i;

	for(i=1;i<=nCases;i++)
		if(ex == indices[i])
		{
			cout << "Initialize " << i << "(" << ex << ")" << endl;
			kOde[1] = b[1];
			kOde[2] = b[2]/experiments[i].temperature;
			kOde[3] = pow(experiments[i].pressureO2, b[3]);
			o.Deinitialize();
			BzzVector y0(1, initialconditions_y[i]);
			o.SetInitialConditions(y0, initialconditions_x[i], BzzOdeModel_01);
			o.SetMinimumConstraints(&yMin);
			//break;
		}

	for(i=1;i<=nCases;i++)
		if(ex == indices[i])
		{
			cout << "Calculating " << i << "(" << ex << ")" << endl;

			for(int j=1;j<=experiments[i].nPoints;j++)
			{
				cout << indices[i]+j-1 << "\t" << experiments[i].x[j] << endl;
				yy = o(experiments[i].x[j]);
				YY.SetRow(indices[i]+j-1,yy); 
			}
			break;
		}
	
	YY.GetRow(ex, &y);
}