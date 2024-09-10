void runMET()
{
    gROOT->Reset();
    gSystem->Load("libPhysics.so");

    //TProof::Open("[email protected]:21002");
    //TProof::Open("lite://");

    TChain *c = new TChain("hcalTupleTree/tree","");
    //AddToChain(c, "inputMET.txt");
    AddToChain(c, "inputSingleMuon.txt");
    //AddToChain(c, "inputHPD.txt");
    //AddToChain(c, "inputNoBPTX_2015C.txt");
    //AddToChain(c, "inputTestSingleMuon.txt");
    //AddToChain(c, "inputTestNoBPTX_2015C.txt");
    //c->SetProof();
    c->Process("MET.C+g");
    //
}