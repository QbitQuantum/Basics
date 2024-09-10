TCanvas * MediPixAlgo::DrawInSeparateWindow(vector<TH2 *> g , MSG::Level vl){

	if(g.empty()) {
		Log << vl << "Nothing to draw ... return NULL pointer" << endreq;
		return 0x0;
	}
	TString cname; // take the cname from the first histo
	if(vl == MSG::DEBUG) {
		vector<TH2 *>::iterator i = g.begin();
		Log << vl << "Attempting to draw in a separate canvas the following objects : " << endreq;
		for( ; i != g.end() ; i++){
			if(!cname.Length()) {cname = (*i)->GetName();}
			Log << vl << (*i)->GetName() << " with " << (*i)->GetEntries() << " entries "<< endreq;
		}
	}
	///////////////////////////////////////////////////////////////////
	TCanvas * c11 = new TCanvas("TH2","TH2");
	int ngraphs = (int)g.size();
	int xdiv = floor( TMath::Sqrt(ngraphs) );
	int ydiv = ceil( (double)ngraphs/(double)xdiv );
	c11->Divide(xdiv, ydiv);

	vector<TH2 *>::iterator itr = g.begin();
	int cntr2 = 0;
	double posx = 0.;
	double posy = 0.;
	for ( ; itr != g.end(); itr++) {

		c11->cd(cntr2+1);
		(*itr)->Draw("colz");
		//(*itr)->SetT
		(*itr)->GetXaxis()->SetLabelSize(0.05);
		(*itr)->GetYaxis()->SetLabelSize(0.05);

		posx = (*itr)->GetBinCenter( 1 );
		posy = (*itr)->GetMaximum() * 0.9;

		TLatex l1;
		l1.SetTextSize(0.05);
		l1.DrawLatex(posx, posy, (*itr)->GetName() );

		cntr2++;
	}
	return c11;
}