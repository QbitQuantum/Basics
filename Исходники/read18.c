void read18() {
    ifstream in;
    in.open("/Users/Yuichi/root/macros/mytext18.txt");
    
    Float_t a,b,c,d,e,k,g,h,i,j;
    Int_t nlines = 0;
    TFile *f = new TFile("read18.root","RECREATE");
    TNtuple *ntuple = new TNtuple("ntuple","data from reading18 file","a:b:c:d:e:k:g:h:i:j");
    
    while (1) {
        in >> a >> b >> c >> d >> e >> k >> g >> h >> i >> j;
        if (!in.good()) break;
        if (nlines < 100) printf("a=%8f, b=%8f, c=%8f, d=%8f, e=%8f, k=%8f, g=%8f, h=%8f, i=%8f, j=%8f\n",a,b,c,d,e,k,g,h,i,j);
        ntuple->Fill(a,b,c,d,e,k,g,h,i,j);
        nlines++;
    }
    printf(" found %d points\n",nlines);
    ntuple->Scan("a:b:c:d:e:k:g:h:i:j");
    
    in.close();
    
    f->Write();
}