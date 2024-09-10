////////////////////////////////////////////////////////////////////////
// Calculates theta and phi in HX frame
////////////////////////////////////////////////////////////////////////
pair<double, double> GetAngles_HX( TLorentzVector a,  TLorentzVector b) {
	TLorentzVector c = a+b;                   // JPsi momentum in lab frame
	TVector3 bv = c.BoostVector();
	TLorentzVector p1(0., 0.,  1380., 1380.); // beam momentum in lab frame
	TLorentzVector p2(0., 0., -1380., 1380.); // beam momentum in lab frame
	p1.Boost(-bv);
	p2.Boost(-bv);
	TVector3 beam1 = p1.Vect().Unit();        // beam direction in JPsi rest frame
	TVector3 beam2 = p2.Vect().Unit();        // beam direction in JPsi rest frame

	TVector3 Z = c.Vect().Unit();             // JPsi direction in lab frame
	TVector3 Y = beam1.Cross( beam2 ).Unit(); // the production plane normal
	TVector3 X = Y.Cross(Z).Unit();           // completes the right-handed coordinate

	a.Boost(-bv);                             // muon+ momentum in JPsi rest frame
	TVector3 mu(a.Vect().Dot(X), a.Vect().Dot(Y), a.Vect().Dot(Z)); // transform to new coordinate
	pair<double, double> angles;
	angles.first = mu.Theta();
	angles.second = mu.Phi()>0. ? mu.Phi() : mu.Phi()+2.*TMath::Pi();
	return angles;
}