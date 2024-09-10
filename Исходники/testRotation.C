void testRotation(){
	

	//LOAD LIBS
	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	
	
	
	
	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOutputAll/all_0.root");

	
	//SET UP TREE TO RECEIVE INPUT
	pionPair* pair1 = new pionPair();
	TTree* pairTree = infile->Get("pionPairTree");
	pairTree->SetBranchAddress("pionPair", &pair1);

	
	for (int iPair = 0; iPair < pairTree->GetEntries(); iPair++)
	{
		if (iPair%10000 == 0) {cout << "processing pair number " << iPair << endl;}
		//cout << "processing pair number " << iPair << endl;
		
		
		//if (iPair == 661){continue;}
		
		pairTree->GetEntry(iPair);
		
		TVector3 spinVec;
		
		
		if (pair1->withinRadius(0.05, 0.3))
		{
			
			
			int spinB = pair1->spinBit();
			
			if (spinB == 5 || spinB == 9) //yelow down
			{
				spinVec.SetXYZ(0, -1, 0);
			}
			
			if (spinB == 6 || spinB == 10) //yellow up
			{
				spinVec.SetXYZ(0, 1, 0);
			}
			
			if (spinB == 5 || spinB == 6 || spinB == 9 || spinB == 10)
			{
				
				
				
				TVector3 Ph = pair1->piPlusLV().Vect() + pair1->piMinusLV().Vect();
				TVector3 Rh  = pair1->piPlusLV().Vect() - pair1->piMinusLV().Vect();
				
				
				TVector3 Pa;
				Pa.SetXYZ(0, 0, 1);   //blue is unpolarized beam
				
				TVector3 Pb;
				Pb.SetXYZ(0, 0, -1);  //yellow is polarized beam
				
				
				//ROTATE EVERYTHING BY PI AROUND Y AXIS
				
				Ph.RotateY(TMath::Pi());
				Rh.RotateY(TMath::Pi());
				Pa.RotateY(TMath::Pi());
				Pb.RotateY(TMath::Pi());
				
				
			//	cout << Ph << endl;
			//	cout << Rh << endl;
			//	cout << Pa << endl;
			//	cout << Pb << endl;
				
				
				//cout << "\n";
				
				//cout << Ph.Unit().Cross(Pa) << endl;
				//cout << Ph.Unit().Cross(Rh) << endl;
				
				double cosPhi_S = Pb.Unit().Cross(Ph).Unit() * Pb.Unit().Cross(spinVec).Unit();
				
				double cosPhi_R = Ph.Unit().Cross(Pa).Unit() * Ph.Unit().Cross(Rh).Unit();
				
				double sinPhi_S = Ph.Cross(spinVec) * Pb.Unit() / (Pb.Unit().Cross(Ph).Mag() * Pb.Unit().Cross(spinVec).Mag());
				
				double sinPhi_R = Pa.Cross(Rh) * Ph.Unit() / (Ph.Unit().Cross(Pa).Mag() * Ph.Unit().Cross(Rh).Mag());
				
				
				
				double sinPhi_S_R = sinPhi_S*cosPhi_R - cosPhi_S*sinPhi_R;
				
				double cosPhi_S_R = cosPhi_S*cosPhi_R + sinPhi_S*sinPhi_R;
				
				
				
				double phi_S_R;
				
				if (cosPhi_S_R >= 0)
				{
					phi_S_R = asin(sinPhi_S_R);
				}
				else if (cosPhi_S_R < 0)
				{
					
					if (sinPhi_S_R >= 0)
					{
						phi_S_R = TMath::Pi() - asin(sinPhi_S_R);
					}
					if (sinPhi_S_R < 0)
					{
						phi_S_R = -TMath::Pi() - asin(sinPhi_S_R);
					}
					
				}
				
				
				
				cout << "regular Phi_SR = " << pair1->phiSR('y') << "   rotated Phi_SR = " << phi_S_R << endl;
				
			}
			
			
			
			
		}
		
	}
	
	
	
	
	
	
	
}