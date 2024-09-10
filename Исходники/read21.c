void read21n() {
    ifstream in;
    in.open("/Users/Yuichi/root/macros/mytext21.txt");    //Check
    
    Float_t hm,zm;      //Values
    Int_t nlines = 0;
    TFile *f = new TFile("read21.root","RECREATE");    //Output name
    TNtuple *ntuple = new TNtuple("ntuple","data from read20_3 file","hm:zm");    //Values
    
    while (1) {
        in >> hm >> zm;   //input
        if (!in.good()) break;
        if (nlines < 100) printf("hm=%8f, zm=%8f\n",hm,zm);  //Values
        ntuple->Fill(hm,zm);       //Fill values
        nlines++;
    }
    printf(" found %d points\n",nlines);
    ntuple->Scan("hm:zm");  //Scan Values
    
    in.close();
    
    f->Write();
    f->Close();
}