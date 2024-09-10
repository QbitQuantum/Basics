int RampCorrellation_single(std::string file_name, TGraphErrors &graph, TGraphErrors &graph2, vector<double> &vec_errors)
{

	TTree *t = new TTree();
	const std::string file_path = "/home/jlab/github/MagCloak_Analysis/calibration/data-calib/DATA_MegaVIEW/";
//	std::string file_name = "DataFile_2016-12-08_06-59-11.csv";
	std::string file = file_path+file_name;

	t->ReadFile(file.c_str());
//	t->Print();

	TCanvas *c = new TCanvas();
	t->Draw("TMath::Abs(B1/B2):time");
	TGraph *gh = (TGraph*)c->GetListOfPrimitives()->FindObject("Graph");
	double ratio_mean = gh->GetMean(2);
	double ratio_std = gh->GetRMS(2);

	t->Draw("Bnom:time");
	TGraph *gh1 = (TGraph*)c->GetListOfPrimitives()->FindObject("Graph");
	double nom_mean = gh1->GetMean(2);
	double nom_std = 0;

//	cout << "At " << nom_mean << " mT, B1/B2 is: " << ratio_mean << " +/- " << ratio_std << endl;
	
	c->Close();

	int n = graph.GetN();
	graph.SetPoint(n,nom_mean,ratio_mean);
	graph.SetPointError(n,nom_std,ratio_std);

//-------------------------------------------------------------------------------

	TCanvas *c2 = new TCanvas();
	t->Draw("B3:time");
	TGraph *gh2 = (TGraph*)c2->GetListOfPrimitives()->FindObject("Graph");
	double B3_mean = -1*(gh2->GetMean(2));
	double B3_std = gh2->GetRMS(2);
	
	int n2 = graph2.GetN();
	graph2.SetPoint(n2, nom_mean, B3_mean);
	graph2.SetPointError(n2, nom_std, B3_std);
	
	c2->Close();

	if(nom_mean < 500) vec_errors.push_back(B3_std);

	return 0;
}