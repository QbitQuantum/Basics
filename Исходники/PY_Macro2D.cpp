int
PY_Macro2D::update(void)
{
  Domain *theDomain=this->getDomain();
  Tt = theDomain->getCurrentTime();
  double dt = Tt - Ct;

  // determine the strain
  const Vector &disp1 = theNodes[0]->getTrialDisp();
  const Vector &disp2 = theNodes[1]->getTrialDisp();

  double Ru = disp1(1);          // pore water pressure

  // Use displacements to find the total strain in the element
  TU = 0.0;
  for (int i=0; i<2; i++)
  {
    TU -= (disp2(i)-disp1(i)) * trans(0,i);
  }
  // Find the change in strain
  double dU = TU - CU;

  // Declare the other variables required
  double dz, f, f_, Tzold, Tznew;

  dz = K/py*(1-(tanh(a*abs(Cz))/tanh(a))*(b+g*signum(dU*Cz)))*dU;
  Tz = Cz+dz;


 // Pore Pressure Generation Model
	Tforce = py*Tz*CS;
	Ttangent = K*(1-(tanh(a*fabs(Tz))/tanh(a))*(b+g*signum(dU*Tz)))*TS;

	TW = CW;
	double dSb = 0.0;
	if (fabs(Tz) <= 0.67*m2/m1)
	{
		TW = CW+fabs(Tforce*dU)/py/(py/K);
		dSb = exp(-1*pow(TW/w1,1.4))*1.4*pow(TW/w1,0.4)*fabs(Tforce*dU)/py/(py/K)/w1;
	}

	double Sff = 1-Ru;
	double dSd = beta/(0.01+0.99*fabs(Sff-CS0))*pow(CS,p1) *dt/(1+beta/(0.01+0.99*fabs(Sff-CS0))*pow(CS,p1) *dt)*(Sff-CS);
	TS0 = CS0 - dSb + dSd;

	if (fabs(Tz) <= 0.67*m2/m1)
	{
		TS = TS0;
	} else
	{
		double alp = 0.67*m2/m1;
		TS = TS0*(1+alp*alp)/(fabs(Tz)*alp+pow((Tz*alp)*(Tz*alp)+(1-Tz*Tz)*(1+alp*alp),0.5));
	}

 // Compute force and tangent
//	Tforce = py*Tz*TS;
//	Ttangent = K*(1-(tanh(a*fabs(Tz))/tanh(a))*(b+g*signum(dU*Tz)))*TS;



  return 0;
}