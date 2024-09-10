void pgsAnalysis::Loop()
{

double tHrec, tZ1m, tZ2m, tcosthetaStar, tPhi, tPhi1, tcostheta1, tcostheta2,tHrec_constr,tZ1m_constr, tZ2m_constr;
string ttype;
hists->Branch("Hrec", &tHrec);
hists->Branch("Z1m", &tZ1m);
hists->Branch("Z2m", &tZ2m);
hists->Branch("costhetaStar", &tcosthetaStar);
hists->Branch("Phi", &tPhi);
hists->Branch("Phi1", &tPhi1);
hists->Branch("costheta1", &tcostheta1);
hists->Branch("costheta2", &tcostheta2);
hists->Branch("type", &ttype);

//event type!!
int eeee, xxxx, eexx, xxee;

double Zmass = 91.19;
double vZmass;
if (pairing == 0){
	vZmass = 91.19;
}
else{
	vZmass = 45.;
}
		TVectorT<double> elSum(4);
		TVectorT<double> muSum(4);


	//electrons array
	vector<int> el; int elC = 0;
	//muons array
	vector<int> mu;	int muC = 0;
	//antielectrons array
	vector<int> antiel;	int antielC = 0;
	//antimuons array
	vector<int> antimu;	int antimuC = 0;

	vector<TVector3> leptons;

	TVector3 lep1,lep2,lep3,lep4;
	TVector3 Za, Zb, Zc, Zd, H;


	int lCounter = 0;
	int totaLlCounter = 0;
	int goodEventCounter = 0;
	int histCounter = 0;

	if (fChain == 0) return;
	

	int nentries = n;

// 	cout << " nentries are "<<nentries<<endl;


	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
	Long64_t ientry = LoadTree(jentry);
	if (ientry < 0) break;
	nb = fChain->GetEntry(jentry);   nbytes += nb;
	// if (Cut(ientry) < 0) continue;

		el.clear();
		antiel.clear();
		mu.clear();
		antimu.clear();
		lCounter = 0;
		eeee = 0;
		xxxx = 0;
		eexx = 0;
		xxee = 0;

		//particles identified by type, ntrk
		for (int inst = 0; inst < npart; inst++){	// inst from "instance" on the scan tree
			
// 			cout<< " instance "<< inst <<endl;
// 			cout<< pT[inst]<< endl;
	
			//fill el mu vectors
			if ( typ[inst] == 1 && ntrk[inst] == -1){
				el.push_back(inst);
				elC++;
				lCounter++;
				totaLlCounter++;
			}
			if ( typ[inst] == 1 && ntrk[inst] == 1){
				antiel.push_back(inst);
				antielC++;
				lCounter++;
				totaLlCounter++;
			}
			if ( typ[inst] == 2 && ntrk[inst] == -1){
				mu.push_back(inst);
				muC++;
				lCounter++;
				totaLlCounter++;
			}
			if ( typ[inst] == 2 && ntrk[inst] == 1){
				antimu.push_back(inst);
				antimuC++;
				lCounter++;
				totaLlCounter++;
			}
			if ( (typ[inst] == 4 && jmas[inst] > 10. )|| (typ[inst] == 6 && pT[inst] > 10. )){
				lCounter = 0; //dont count the event
			}

		
		}//end instance loop (particles in an event

// 		cout<< "leptons in the event are "<< lCounter<<endl;
// 		if (lCounter == 4) { 

		fillFlag = false;

		// If else if loops reconstructing the particles according to the type 4e,4mu, 2e2mu
		
		if (el.size() == 1 && mu.size() == 1 && antiel.size() == 1 && antimu.size() == 1){ //2e2m
			goodEventCounter++;


			lep1.SetPtEtaPhi( pT[el[0]], eta[el[0]]	, phi[el[0]]);			//set up of lepton four-vectors
			lep2.SetPtEtaPhi( pT[antiel[0]], eta[antiel[0]]	, phi[antiel[0]]);
			lep3.SetPtEtaPhi( pT[mu[0]], eta[mu[0]]	, phi[mu[0]]);
			lep4.SetPtEtaPhi( pT[antimu[0]], eta[antimu[0]]	, phi[antimu[0]]);

			Za = lep1 + lep2;
			Zb = lep3 + lep4;

			mZ1 = sqrt(pow(lep1.Mag()+lep2.Mag(),2)-Za.Mag2());	// reconstruct z masses 
			mZ2 = sqrt(pow(lep3.Mag()+lep4.Mag(),2)-Zb.Mag2());


			//select leading Z
			if(mZ1 > mZ2) { Z1.SetVectM( Za, mZ1); Z2.SetVectM(Zb,mZ2); lep_min1.SetPtEtaPhiE(lep1.Pt(),lep1.Eta(), lep1.Phi(),lep1.Mag()); lep_plus1.SetPtEtaPhiE(lep2.Pt(),lep2.Eta(), lep2.Phi(),lep2.Mag()); lep_min2.SetPtEtaPhiE(lep3.Pt(),lep3.Eta(), lep3.Phi(),lep3.Mag()); lep_plus2.SetPtEtaPhiE(lep4.Pt(),lep4.Eta(), lep4.Phi(),lep4.Mag());eexx++;}	//to set the highest mass the z
			else { Z2.SetVectM( Za, mZ1); Z1.SetVectM(Zb,mZ2); lep_min2.SetPtEtaPhiE(lep1.Pt(),lep1.Eta(), lep1.Phi(),lep1.Mag()); lep_plus2.SetPtEtaPhiE(lep2.Pt(),lep2.Eta(), lep2.Phi(),lep2.Mag()); lep_min1.SetPtEtaPhiE(lep3.Pt(),lep3.Eta(), lep3.Phi(),lep3.Mag()); lep_plus1.SetPtEtaPhiE(lep4.Pt(),lep4.Eta(), lep4.Phi(),lep4.Mag());xxee++;}


			

		fillFlag = true;
		}



		else if (el.size() == 2 && mu.size() == 0  && antiel.size() == 2 && antimu.size() == 0){ //4e
			goodEventCounter++;

			lep1.SetPtEtaPhi( pT[el[0]], eta[el[0]]	, phi[el[0]]);	
			lep2.SetPtEtaPhi( pT[antiel[0]], eta[antiel[0]]	, phi[antiel[0]]);
			lep3.SetPtEtaPhi( pT[el[1]], eta[el[1]]	, phi[el[1]]);	
			lep4.SetPtEtaPhi( pT[antiel[1]], eta[antiel[1]]	, phi[antiel[1]]);

			Za = lep1 + lep2;
			Zb = lep3 + lep4;
			Zc = lep1 + lep4;
			Zd = lep3 + lep2;

			double mZa = sqrt(pow(lep1.Mag()+lep2.Mag(),2)-Za.Mag2());
			double mZb = sqrt(pow(lep3.Mag()+lep4.Mag(),2)-Zb.Mag2());
			double mZc = sqrt(pow(lep1.Mag()+lep4.Mag(),2)-Zc.Mag2());
			double mZd = sqrt(pow(lep2.Mag()+lep3.Mag(),2)-Zd.Mag2());

			double s1a;
			double s1b;
			double s2a;
			double s2b;
			if ( pairing == 0){
			s1a = pow(mZa-vZmass,2) + pow(mZb-Zmass,2);
			s1b = pow(mZa-Zmass,2) + pow(mZb-vZmass,2);
			s2a = pow(mZc-vZmass,2) + pow(mZd-Zmass,2);
			s2b = pow(mZc-Zmass,2) + pow(mZd-vZmass,2);
			}
			else{
			s1a = fabs(mZb-Zmass);
			s1b = fabs(mZa-Zmass);
			s2a = fabs(mZd-Zmass);
			s2b = fabs(mZc-Zmass);
			}

			elSum[0] = s1a;
			elSum[1] = s1b;
			elSum[2] = s2a;
			elSum[3] = s2b;

			int min = TMath::LocMin(4, &elSum[0]);

			if( (min == 0 || min == 1) ){
				if(mZa > mZb) { Z1.SetVectM( Za, mZa); Z2.SetVectM(Zb,mZb); lep_min1.SetPtEtaPhiE(lep1.Pt(),lep1.Eta(), lep1.Phi(),lep1.Mag()); lep_plus1.SetPtEtaPhiE(lep2.Pt(),lep2.Eta(), lep2.Phi(),lep2.Mag()); lep_min2.SetPtEtaPhiE(lep3.Pt(),lep3.Eta(), lep3.Phi(),lep3.Mag()); lep_plus2.SetPtEtaPhiE(lep4.Pt(),lep4.Eta(), lep4.Phi(),lep4.Mag());}	//to set the highest mass the z
				else { Z2.SetVectM( Za, mZa); Z1.SetVectM(Zb,mZb); lep_min2.SetPtEtaPhiE(lep1.Pt(),lep1.Eta(), lep1.Phi(),lep1.Mag()); lep_plus2.SetPtEtaPhiE(lep2.Pt(),lep2.Eta(), lep2.Phi(),lep2.Mag()); lep_min1.SetPtEtaPhiE(lep3.Pt(),lep3.Eta(), lep3.Phi(),lep3.Mag()); lep_plus1.SetPtEtaPhiE(lep4.Pt(),lep4.Eta(), lep4.Phi(),lep4.Mag());}
				
			}
			else if( (min == 2 || min == 3) ){
				if(mZc > mZd) { Z1.SetVectM( Zc, mZc); Z2.SetVectM(Zd,mZd); lep_min1.SetPtEtaPhiE(lep1.Pt(),lep1.Eta(), lep1.Phi(),lep1.Mag()); lep_plus1.SetPtEtaPhiE(lep4.Pt(),lep4.Eta(), lep4.Phi(),lep4.Mag()); lep_min2.SetPtEtaPhiE(lep3.Pt(),lep3.Eta(), lep3.Phi(),lep3.Mag()); lep_plus2.SetPtEtaPhiE(lep2.Pt(),lep2.Eta(), lep2.Phi(),lep2.Mag());}	//to set the highest mass the z
				else { Z2.SetVectM( Zc, mZc); Z1.SetVectM(Zd,mZd); lep_min2.SetPtEtaPhiE(lep1.Pt(),lep1.Eta(), lep1.Phi(),lep1.Mag()); lep_plus2.SetPtEtaPhiE(lep4.Pt(),lep4.Eta(), lep4.Phi(),lep4.Mag()); lep_min1.SetPtEtaPhiE(lep3.Pt(),lep3.Eta(), lep3.Phi(),lep3.Mag()); lep_plus1.SetPtEtaPhiE(lep2.Pt(),lep2.Eta(), lep2.Phi(),lep2.Mag());}


			}
			eeee++;
		fillFlag = true;
		} 


		else if(el.size() == 0 && mu.size() == 2  && antiel.size() == 0 && antimu.size() == 2 )  { //4m
			goodEventCounter++;

			lep1.SetPtEtaPhi( pT[mu[0]], eta[mu[0]]	, phi[mu[0]]);	
			lep2.SetPtEtaPhi( pT[antimu[0]], eta[antimu[0]]	, phi[antimu[0]]);
			lep3.SetPtEtaPhi( pT[mu[1]], eta[mu[1]]	, phi[mu[1]]);	
			lep4.SetPtEtaPhi( pT[antimu[1]], eta[antimu[1]]	, phi[antimu[1]]);

			Za = lep1 + lep2;
			Zb = lep3 + lep4;
			Zc = lep1 + lep4;
			Zd = lep3 + lep2;

			double mZa = sqrt(pow(lep1.Mag()+lep2.Mag(),2)-Za.Mag2());
			double mZb = sqrt(pow(lep3.Mag()+lep4.Mag(),2)-Zb.Mag2());
			double mZc = sqrt(pow(lep1.Mag()+lep4.Mag(),2)-Zc.Mag2());
			double mZd = sqrt(pow(lep2.Mag()+lep3.Mag(),2)-Zd.Mag2());

			double s1a;
			double s1b;
			double s2a;
			double s2b;
			if ( pairing == 0){
			s1a = pow(mZa-vZmass,2) + pow(mZb-Zmass,2);
			s1b = pow(mZa-Zmass,2) + pow(mZb-vZmass,2);
			s2a = pow(mZc-vZmass,2) + pow(mZd-Zmass,2);
			s2b = pow(mZc-Zmass,2) + pow(mZd-vZmass,2);
			}
			else{
			s1a = fabs(mZb-Zmass);
			s1b = fabs(mZa-Zmass);
			s2a = fabs(mZd-Zmass);
			s2b = fabs(mZc-Zmass);
			}


			muSum[0] = s1a;
			muSum[1] = s1b;
			muSum[2] = s2a;
			muSum[3] = s2b;

			int min = TMath::LocMin(4, &muSum[0]);

			if( (min == 0 || min == 1) ){
				if(mZa > mZb) { Z1.SetVectM( Za, mZa); Z2.SetVectM(Zb,mZb); lep_min1.SetPtEtaPhiE(lep1.Pt(),lep1.Eta(), lep1.Phi(),lep1.Mag()); lep_plus1.SetPtEtaPhiE(lep2.Pt(),lep2.Eta(), lep2.Phi(),lep2.Mag()); lep_min2.SetPtEtaPhiE(lep3.Pt(),lep3.Eta(), lep3.Phi(),lep3.Mag()); lep_plus2.SetPtEtaPhiE(lep4.Pt(),lep4.Eta(), lep4.Phi(),lep4.Mag());}	//to set the highest mass the z
				else { Z2.SetVectM( Za, mZa); Z1.SetVectM(Zb,mZb); lep_min2.SetPtEtaPhiE(lep1.Pt(),lep1.Eta(), lep1.Phi(),lep1.Mag()); lep_plus2.SetPtEtaPhiE(lep2.Pt(),lep2.Eta(), lep2.Phi(),lep2.Mag()); lep_min1.SetPtEtaPhiE(lep3.Pt(),lep3.Eta(), lep3.Phi(),lep3.Mag()); lep_plus1.SetPtEtaPhiE(lep4.Pt(),lep4.Eta(), lep4.Phi(),lep4.Mag());}
				
			}
			else if( (min == 2 || min == 3) ){
				if(mZc > mZd) { Z1.SetVectM( Zc, mZc); Z2.SetVectM(Zd,mZd); lep_min1.SetPtEtaPhiE(lep1.Pt(),lep1.Eta(), lep1.Phi(),lep1.Mag()); lep_plus1.SetPtEtaPhiE(lep4.Pt(),lep4.Eta(), lep4.Phi(),lep4.Mag()); lep_min2.SetPtEtaPhiE(lep3.Pt(),lep3.Eta(), lep3.Phi(),lep3.Mag()); lep_plus2.SetPtEtaPhiE(lep2.Pt(),lep2.Eta(), lep2.Phi(),lep2.Mag());}	//to set the highest mass the z
				else { Z2.SetVectM( Zc, mZc); Z1.SetVectM(Zd,mZd); lep_min2.SetPtEtaPhiE(lep1.Pt(),lep1.Eta(), lep1.Phi(),lep1.Mag()); lep_plus2.SetPtEtaPhiE(lep4.Pt(),lep4.Eta(), lep4.Phi(),lep4.Mag()); lep_min1.SetPtEtaPhiE(lep3.Pt(),lep3.Eta(), lep3.Phi(),lep3.Mag()); lep_plus1.SetPtEtaPhiE(lep2.Pt(),lep2.Eta(), lep2.Phi(),lep2.Mag());}


			}
		xxxx++;
		fillFlag = true;
		}


		if ( fillFlag == true && goodEventCounter < 25001) {	//if it fullfills the specs then fill and find angles

			rec_H = Z1 + Z2;
			double Hmass = rec_H.M();
			tHrec = Hmass;
// 			cout<<tHrec<<endl;

			double Z1mass = Z1.M();
			tZ1m = Z1mass;
			double Z2mass = Z2.M();
			tZ2m = Z2mass;
			double ptlepp1 = lep_plus1.Pt();
			double ptlepm1 = lep_min1.Pt();
			double ptlepp2 = lep_plus2.Pt();
			double ptlepm2 = lep_min2.Pt();
			double dR1 = sqrt(pow(fabs(lep_min1.Eta() - lep_plus1.Eta()),2)+pow(fabs(lep_min1.DeltaPhi(lep_plus1)),2));
			double dR2 = sqrt(pow(fabs(lep_min2.Eta() - lep_plus2.Eta()),2)+pow(fabs(lep_min2.DeltaPhi(lep_plus2)),2));

// 			if ( /*Hmass<120 || Hmass>130 || */Z1mass < 49 || Z1mass>107 || Z2mass < 12 || Z2mass> 115 ){continue;}	//constrains		
	
			//filling the simple histogram values
			h_Z1_m -> Fill(Z1.M());
			h_Z1_E -> Fill(Z1.E());
			h_Z1_Pt -> Fill(Z1.Pt());
			h_Z1_eta -> Fill(Z1.Eta());
			h_Z1_phi -> Fill(Z1.Phi());
	
			h_Z2_m -> Fill(Z2.M());
			h_Z2_E -> Fill(Z2.E());
			h_Z2_Pt -> Fill(Z2.Pt());
			h_Z2_eta -> Fill(Z2.Eta());
			h_Z2_phi -> Fill(Z2.Phi());
	
	
			h_rec_H_m	-> Fill(Hmass);
			h_rec_H_E	-> Fill(rec_H.E());
			h_rec_H_Pt	-> Fill(rec_H.Pt());
			h_rec_H_eta	-> Fill(rec_H.Eta());
			h_rec_H_phi	-> Fill(rec_H.Phi());	

			h_lep_plus1_E	-> Fill(lep_plus1.E());
			h_lep_plus1_Pt	-> Fill(ptlepp1);
			h_lep_plus1_eta	-> Fill(lep_plus1.Eta());
			h_lep_plus1_phi	-> Fill(lep_plus1.Phi());

			h_lep_min1_E	-> Fill(lep_min1.E());
			h_lep_min1_Pt	-> Fill(ptlepm1);
			h_lep_min1_eta	-> Fill(lep_min1.Eta());
			h_lep_min1_phi	-> Fill(lep_min1.Phi());

			h_lep_plus2_E	-> Fill(lep_plus2.E());
			h_lep_plus2_Pt	-> Fill(ptlepp2);
			h_lep_plus2_eta	-> Fill(lep_plus2.Eta());
			h_lep_plus2_phi	-> Fill(lep_plus2.Phi());

			h_lep_min2_E	-> Fill(lep_min2.E());
			h_lep_min2_Pt	-> Fill(ptlepm2);
			h_lep_min2_eta	-> Fill(lep_min2.Eta());
			h_lep_min2_phi	-> Fill(lep_min2.Phi());	

		//reconstructing the two lepton pairs Lorentz vectors
		lpair1 = lep_plus1 + lep_min1;
		lpair2 = lep_plus2 + lep_min2;

		//constructing 3-vectors in the lab frame
		lep_plus1_lab 	= lep_plus1.Vect();
		lep_plus2_lab 	= lep_plus2.Vect();	//.Vect() gives 3 vector from 4vector
		lep_min1_lab 	= lep_min1.Vect();	
		lep_min2_lab 	= lep_min2.Vect();
		lpair1_lab 	= lep_plus1_lab.Cross(lep_min1_lab);	
		lpair2_lab 	= lep_plus2_lab.Cross(lep_min2_lab);

// 		cout << " pt of lepton pair1 on rest frame is: "<< lpair1.Perp()<<endl;


	   	//Filling up Histograms with angles defined in the lab frame
		h_angle_lab_pair1 -> Fill(lep_plus1_lab.Angle(lep_min1_lab));
		h_angle_lab_pair2 -> Fill(lep_plus2_lab.Angle(lep_min2_lab));


       		//Filling up histograms with variables from articles
       		h_angle_lab_deleta1	-> Fill(fabs(lep_min1.Eta() - lep_plus1.Eta()));
       		h_angle_lab_delphi1	-> Fill(fabs(lep_min1.DeltaPhi(lep_plus1)));
       		h_angle_lab_deleta2	-> Fill(fabs(lep_min2.Eta() - lep_plus2.Eta()));
       		h_angle_lab_delphi2	-> Fill(fabs(lep_min2.DeltaPhi(lep_plus2)));


	   	//Looking at the Higgs rest frame
	   	TVector3 boost_rH 	= -rec_H.BoostVector(); //NOTE the minus sign! WHY - sign???
	   	TVector3 boost_rZ1	= -Z1.BoostVector();
	   	TVector3 boost_rZ2	= -Z2.BoostVector();	
	   	Higgs_rest	= rec_H;
	   	Z1_rH		= Z1;
	   	Z2_rH		= Z2;
	   	lep_p1_rH	= lep_plus1;	//
	   	lep_m1_rH	= lep_min1;
	   	lep_p2_rH	= lep_plus2;
	   	lep_m2_rH	= lep_min2;
	   	lep_p1_rZ1	= lep_plus1;
	   	lep_m2_rZ2	= lep_min2;
	   	lep_p2_rZ2	= lep_plus2;
	   	lep_m1_rZ1	= lep_min1;

	   	//Boosting vectors to the Higgs rest frame
	   	Higgs_rest.Boost(boost_rH);
	   	Z1_rH.Boost(boost_rH);
	   	Z2_rH.Boost(boost_rH);
	   	lep_p1_rH.Boost(boost_rH);
	   	lep_m1_rH.Boost(boost_rH);
	   	lep_p2_rH.Boost(boost_rH);
	   	lep_m2_rH.Boost(boost_rH);

	   	//Boosting leptons to Z rest frames
	   	lep_p1_rZ1.Boost(boost_rZ1);
	   	lep_m1_rZ1.Boost(boost_rZ1);
	   	lep_p2_rZ2.Boost(boost_rZ2);
	   	lep_m2_rZ2.Boost(boost_rZ2);

	   	//Setting 3Vectors in Higgs rest frame
	   	Z3_1_rH		= Z1_rH.Vect();
	   	Z3_2_rH		= Z2_rH.Vect();
	   	lep3_plus1_rH 	= lep_p1_rH.Vect();
	   	lep3_min1_rH	= lep_m1_rH.Vect();
	   	lep3_plus2_rH 	= lep_p2_rH.Vect();
	   	lep3_min2_rH	= lep_m2_rH.Vect();
		TVector3 Z3_1plane_rH 	= lep3_plus1_rH.Cross(lep3_min1_rH);	//wrong?
	   	TVector3 Z3_2plane_rH 	= lep3_plus2_rH.Cross(lep3_min2_rH);

	   	//Setting 3Vectors in Z1/Z2 rest frame
	   	lep3_plus1_rZ1	= lep_p1_rZ1.Vect();
	   	lep3_plus2_rZ2	= lep_p2_rZ2.Vect();
	   	lep3_min1_rZ1	= lep_m1_rZ1.Vect();
	   	lep3_min2_rZ2	= lep_m2_rZ2.Vect();

	   	//Filling up histogram for the phi angle distribution

		//pairnoume ta monadiaia dianysmata twn kathetwn pediwn, prwta ypologizoume to metro tous, meta eswteriko ginomeno, meta tokso tou costheta tous
		double metro1 = sqrt((pow(Z3_1plane_rH.X(),2))+(pow(Z3_1plane_rH.Y(),2))+(pow(Z3_1plane_rH.Z(),2)));
		double metro2 = sqrt((pow(Z3_2plane_rH.X(),2))+(pow(Z3_2plane_rH.Y(),2))+(pow(Z3_2plane_rH.Z(),2)));
		TVector3 Z3_1plane_rH_un = Z3_1plane_rH.Unit();
		TVector3 Z3_2plane_rH_un = Z3_2plane_rH.Unit();

		TVector3 drtPlane = Z3_1plane_rH_un.Cross(Z3_2plane_rH_un);
		double phi = acos(-Z3_1plane_rH_un.Dot(Z3_2plane_rH_un))*(Z3_1_rH.Dot(skata))/fabs(Z3_1_rH.Dot(skata));

		h_angle_rH_phi	-> Fill( phi );
		tPhi = phi;		



		//****Phi one angle , same procedure as before. Now the plane is the first Z boson vector with beam axis, so they form a plane, phi1 is angle between this plane and the Z1 plane (apo to decay twn 2 leptoniwn)
		TVector3 niScatter_un = (beamAxis.Cross(Z3_1_rH)).Unit();
		TVector3 drtPlane2 = Z3_1plane_rH_un.Cross(niScatter_un);
		double phiOne = acos(Z3_1plane_rH_un.Dot(niScatter_un))*(Z3_1_rH.Dot(skata2))/fabs(Z3_1_rH.Dot(skata2));
		h_angle_rH_phiOne	-> Fill( phiOne );
		tPhi1 = phiOne;


	   	//Filling up histogram for theta* angle: Z1/Z2 with Higgs boost vector
	   	h_angle_rH_thetaZ2	-> Fill(Z3_2_rH.CosTheta());
		
		double cosThetaStar = Z3_1_rH.CosTheta();
		h_angle_rH_thetaZ1	-> Fill(cosThetaStar);
		tcosthetaStar = cosThetaStar;

		//  boosting the z to the other z frame
		TLorentzVector Z_1_rZ2 = Z1;
		Z_1_rZ2.Boost(boost_rZ2);
		TVector3 Z3_1_rZ2 = Z_1_rZ2.Vect();
		TLorentzVector Z_2_rZ1 = Z2;
		Z_2_rZ1.Boost(boost_rZ1);
		TVector3 Z3_2_rZ1 = Z_2_rZ1.Vect();
		double cosTheta1 = cos(lep3_min1_rZ1.Angle(-Z3_2_rZ1));
		double cosTheta2 = cos(lep3_min2_rZ2.Angle(-Z3_1_rZ2));
	   	h_angle_rZ1_lp1Z1	-> Fill(cos(lep3_plus1_rZ1.Angle(-Z3_2_rZ1)));	
	   	h_angle_rZ1_lm1Z1	-> Fill(cosTheta1);	// theta1
	   	h_angle_rZ2_lp2Z2	-> Fill(cos(lep3_plus2_rZ2.Angle(-Z3_1_rZ2)));	
	   	h_angle_rZ2_lm2Z2	-> Fill(cosTheta2);	// theta2
		tcostheta1 = cosTheta1;
		tcostheta2 = cosTheta2;	

       		h_angle_rH_delphi1	-> Fill(fabs(lep_p1_rH.DeltaPhi(lep_m1_rH)));
		h_angle_rH_delphi2	-> Fill(fabs(lep_p2_rH.DeltaPhi(lep_m2_rH)));

		h_mZ1mZ2		-> Fill(Z1.M(),Z2.M());
		h_mVsPtZ1		-> Fill(Z1.M(),Z1.Pt());

		h_delphi1VsPtZ1_lab	-> Fill(Z1.Pt(),fabs(lep_min1.DeltaPhi(lep_plus1)));
		h_delphi2VsPtZ2_lab	-> Fill(Z2.Pt(),fabs(lep_min2.DeltaPhi(lep_plus2)));

		if (eexx ==1){ttype = "eexx";}
		else if(xxee ==1){ttype = "xxee";}
		else if(eeee ==1){ttype = "eeee";}
		else if(xxxx ==1){ttype = "xxxx";}
		hists->Fill();
		histCounter++;
		
		hists->Close();
		}	//end if fill

		////////////// fill out the decay type

		
		
	// filling the TTree


	}//end entries loop (events)

	//some regular reports
	cout<<endl;
	cout<<" good events are "<<goodEventCounter<<endl;
	cout<<" we see % "<< (double) goodEventCounter/n <<endl;

	cout<<endl;
	cout<<" histogram fills are "<<histCounter<<endl;
// 	cout<<" we see % "<< (double) goodEventCounter/n <<endl;




}//end loop void