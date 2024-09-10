	double energyAndGrad(std::vector<Atom>& atoms) const
	{	double eta = sqrt(0.5)/sigma, etaSq=eta*eta;
		double sigmaSq = sigma * sigma;
		double detR = fabs(det(R)); //cell volume
		//Position independent terms:
		double Ztot = 0., ZsqTot = 0.;
		for(const Atom& a: atoms)
		{	Ztot += a.Z;
			ZsqTot += a.Z * a.Z;
		}
		double E
			= 0.5 * 4*M_PI * Ztot*Ztot * (-0.5*sigmaSq) / detR //G=0 correction
			- 0.5 * ZsqTot * eta * (2./sqrt(M_PI)); //Self-energy correction
		//Reduce positions to first centered unit cell:
		for(Atom& a: atoms)
			for(int k=0; k<3; k++)
				a.pos[k] -= floor(0.5 + a.pos[k]);
		//Real space sum:
		vector3<int> iR; //integer cell number
		for(const Atom& a2: atoms)
			for(Atom& a1: atoms)
				for(iR[0]=-Nreal[0]; iR[0]<=Nreal[0]; iR[0]++)
					for(iR[1]=-Nreal[1]; iR[1]<=Nreal[1]; iR[1]++)
						for(iR[2]=-Nreal[2]; iR[2]<=Nreal[2]; iR[2]++)
						{	vector3<> x = iR + (a1.pos - a2.pos);
							double rSq = RTR.metric_length_squared(x);
							if(!rSq) continue; //exclude self-interaction
							double r = sqrt(rSq);
							E += 0.5 * a1.Z * a2.Z * erfc(eta*r)/r;
							a1.force += (RTR * x) *
								(a1.Z * a2.Z * (erfc(eta*r)/r + (2./sqrt(M_PI))*eta*exp(-etaSq*rSq))/rSq);
						}
		//Reciprocal space sum:
		vector3<int> iG; //integer reciprocal cell number
		for(iG[0]=-Nrecip[0]; iG[0]<=Nrecip[0]; iG[0]++)
			for(iG[1]=-Nrecip[1]; iG[1]<=Nrecip[1]; iG[1]++)
				for(iG[2]=-Nrecip[2]; iG[2]<=Nrecip[2]; iG[2]++)
				{	double Gsq = GGT.metric_length_squared(iG);
					if(!Gsq) continue; //skip G=0
					//Compute structure factor:
					complex SG = 0.;
					for(const Atom& a: atoms)
						SG += a.Z * cis(-2*M_PI*dot(iG,a.pos));
					//Accumulate energy:
					double eG = 4*M_PI * exp(-0.5*sigmaSq*Gsq)/(Gsq * detR);
					E += 0.5 * eG * SG.norm();
					//Accumulate forces:
					for(Atom& a: atoms)
						a.force -= (eG * a.Z * 2*M_PI * (SG.conj() * cis(-2*M_PI*dot(iG,a.pos))).imag()) * iG;
				}
		return E;
	}