void THTMLLandaus::addLandauDiamondTable(vector<Float_t> vecHistoMeans, vector<Float_t> vecHistoMaxs, vector<Float_t> vecHistoGaus, vector<Float_t> vecHistoLandau)
{
	stringstream sectionContent;
	vector<vector<string> > tableContent;
	tableContent.resize(vecHistoMeans.size()+1);
	tableContent.at(0).push_back("ClusterSize");
	tableContent.at(0).push_back("Mean");
	tableContent.at(0).push_back("MaxPos");
	tableContent.at(0).push_back("GausPos");
	tableContent.at(0).push_back("LandauMP");
	tableContent.at(0).push_back("Landau/Gaus");
	tableContent.at(0).push_back("Landau/Max");
	for(UInt_t i=0;i<vecHistoMeans.size()&&i<vecHistoMaxs.size()&&i<vecHistoGaus.size()&&i<vecHistoLandau.size();i++){
		Float_t fraction = vecHistoLandau.at(i)/vecHistoGaus.at(i);
		tableContent.at(i+1).push_back((i==0?"AllClusters":this->floatToString(i+1)));
		tableContent.at(i+1).push_back(this->floatToString(vecHistoMeans.at(i)));
		tableContent.at(i+1).push_back(this->floatToString(vecHistoMaxs.at(i)));
		tableContent.at(i+1).push_back(this->floatToString(vecHistoGaus.at(i)));
		tableContent.at(i+1).push_back(this->floatToString(vecHistoLandau.at(i)));
		tableContent.at(i+1).push_back(this->floatToString(fraction));
		fraction = vecHistoLandau.at(i)/vecHistoMaxs.at(i);
		tableContent.at(i+1).push_back(this->floatToString(fraction));
	}
	sectionContent<<"<p>\n";
	sectionContent<<createTable(tableContent)<<endl;
	sectionContent<<"<p>";
	this->addSection("Landau Fit CrossCheck Table",sectionContent.str());
}