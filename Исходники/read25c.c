void read25cn() {
    ifstream in;
    in.open("/Users/Yuichi/root/macros/mytext25c.txt");    //Check
    
    Float_t dRm,dRmbar,dRb,dRbbar;      //Values
    Int_t nlines = 0;
    TFile *f = new TFile("read25c.root","RECREATE");    //Output name
    TNtuple *ntuple = new TNtuple("ntuple","data from read25c file","dRm:dRmbar:dRb:dRbbar");    //Values
    
    while (1) {
        in >> dRm >> dRmbar >> dRb >> dRbbar;   //input
        if (!in.good()) break;
        if (nlines < 100) printf("dRm=%8f, dRmbar=%8f, dRb=%8f, dRbbar=%8f\n",dRm,dRmbar,dRb,dRbbar);  //Values
        ntuple->Fill(dRm,dRmbar,dRb,dRbbar);       //Fill values
        nlines++;
    }
    printf(" found %d points\n",nlines);
    ntuple->Scan("dRm:dRmbar:dRb:dRbbar");  //Scan Values
    
    in.close();
    
    f->Write();
    f->Close();
}