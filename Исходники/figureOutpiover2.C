void figureOutpiover2(int ptBin, double ptCutLo, double ptCutHi, int massBin, double mCutLo, double mCutHi, int etaBin, double etaCutLo, double etaCutHi) {

    //OPTIONS AND CUTS------------
    bool useBlueBeam = false;
    bool useYellowBeam = true;
    double PI = 3.14159265359;


    if (useBlueBeam && useYellowBeam) {
        cout << "using both beams" << endl;
    }
    if (useBlueBeam && !useYellowBeam) {
        cout << "using blue beam" << endl;
    }
    if (!useBlueBeam && useYellowBeam) {
        cout << "using yellow beam" << endl;
    }


    //PION PAIR CUTS:
    /*
     double ptCutLo = 4;
     double ptCutHi = 10;
     double mCutLo = .4;
     double mCutHi = 1;
     double etaCutLo = -1.4;
     double etaCutHi = 1.4;
     //*/
    //double phiCutLo = -.5;
    //double phiCutHi = .5;

    //----------------------------


    //LOAD LIBS
    cout << "\n";
    gROOT->Macro("StRoot/LoadLibs.C");
    gSystem->Load("pionPair");
    cout << " loading of pionPair library done" << endl;


    //SET UP INPUT FILE
    //TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/all2012dataAll.root");
    //TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOutputWithinRad/allWithRadcut.root");
    TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOutAllDataTry1/allDataTry1.root");





    //SET UP TREE TO RECEIVE INPUT
    pionPair* pair1 = new pionPair();
    TTree* pairTree = infile->Get("pionPairTree");
    pairTree->SetBranchAddress("pionPair", &pair1);


    //SET UP HISTOGRAMS

    //event variable histograms
    TH1D* hInvarM    = new TH1D("invarM","invarM",80,0,2);
    TH1D* hEtaTot	   = new TH1D("etaTot","etaTot",60,-1.5,1.5);
    TH1D* hPhiR      = new TH1D("hPhiR","hPhiR",60,-4,4);
    TH1D* hPhiS      = new TH1D("hPhiS","hPhiS",60,-4,4);
    TH1D* hPhiSR     = new TH1D("hPhiSR","hPhiSR",60,-4,4);
    TH1D* hTheta     = new TH1D("hTheta","hTheta",30,-0.85,4);
    TH1D* hCosTheta  = new TH1D("hCosTheta","hCosTheta",80,-1,1);
    TH1D* hZ         = new TH1D("hZ","hZ",80,0,1);
    TH1D* hPtot      = new TH1D("hPtot","hPtot",80,0,20);
    TH1D* hPtTOT     = new TH1D("hPt","hPt",80,0,15);

    //histos for asym analysis
    double histMin = -PI;
    double histMax =  PI;
    const int binNumber = 16;

    TH1D * hNumberUp   = new TH1D("hNumberUp","hNumberUp",binNumber,histMin,histMax);
    TH1D * hNumberDown = new TH1D("hNumberDown","hNumberDown",binNumber,histMin,histMax);

    TH1D * hDiff  = new TH1D("hNumberSum","hNumberSum",binNumber,histMin,histMax);
    TH1D * hAut = new TH1D("Aut","Aut",binNumber,histMin,histMax);


    //BEAM POLARIZATION

    ifstream polFile;
    polFile.open("/star/u/klandry/ucladisk/2012IFF/BeamPolarization2012.txt");


    map<int, double> polarizationOfFill_Y;
    map<int, double> polErrOfFill_Y;

    map<int, double> polarizationOfFill_B;
    map<int, double> polErrOfFill_B;



    int    fill;
    int    beamE;
    int    startT;
    string plusminus;

    double pAvrgBlue;
    double pErrAvrgBlue;

    double pInitialBlue;
    double pErrInitialBlue;
    double dPdTBlue;
    double dPdTErrBlue;

    double pAvrgYellow;
    double pErrAvrgYellow;

    double pInitialYellow;
    double pErrInitialYellow;
    double dPdTYellow;
    double dPdTErrYellow;

    string header;

    for (int i=0; i<19; i++) {
        polFile >> header;
    }

    while (!polFile.eof())
    {

        polFile >> fill;
        polFile >> beamE;
        polFile >> startT;

        polFile >> pAvrgBlue;
        polFile >> plusminus;
        polFile >> pErrAvrgBlue;

        polFile >> pInitialBlue;
        polFile >> plusminus;
        polFile >> pErrInitialBlue;

        polFile >> dPdTBlue;
        polFile >> plusminus;
        polFile >> dPdTErrBlue;

        polFile >> pAvrgYellow;
        polFile >> plusminus;
        polFile >> pErrAvrgYellow;

        polFile >> pInitialYellow;
        polFile >> plusminus;
        polFile >> pErrInitialYellow;

        polFile >> dPdTYellow;
        polFile >> plusminus;
        polFile >> dPdTErrYellow;


        polarizationOfFill_B[fill] = pAvrgBlue/100.;
        polErrOfFill_B[fill] = pErrAvrgBlue/100.;

        polarizationOfFill_Y[fill] = pAvrgYellow/100.;
        polErrOfFill_Y[fill] = pErrAvrgYellow/100.;



    }

    double avgPolOfBinUp[binNumber];
    double polOfBinSumUp[binNumber];

    double avgPerrorOfBinUp[binNumber];
    double pErrorOfBinUp[binNumber];

    double avgPolOfBinDown[binNumber];
    double polOfBinSumDown[binNumber];

    double avgPerrorOfBinDown[binNumber];
    double pErrorOfBinDown[binNumber];

    for (int i=0; i<binNumber; i++)
    {
        avgPolOfBinUp[i] = 0;
        polOfBinSumUp[i] = 0;

        avgPerrorOfBinUp[i] = 0;
        pErrorOfBinUp[i] = 0;

        avgPolOfBinDown[i] = 0;
        polOfBinSumDown[i] = 0;

        avgPerrorOfBinDown[i] = 0;
        pErrorOfBinDown[i] = 0;

    }


    //   ======================================================================
    //============================================================================
    //START ANALYSIS==============================================================
    //============================================================================
    //   ======================================================================

    cout << pairTree->GetEntries() << endl;

    cout << "\n";
    cout << "<----STARTING ANALYSIS---->" << endl;
    cout << "\n";


    double blueFillNo;
    double yellowFillNo;

    int bin;

    TLorentzVector sum;
    TLorentzVector sumY;
    TLorentzVector sumB;

    TRandom3 r;


    int totalPairsFinal = 0;


    for (int iPair = 0; iPair < pairTree->GetEntries(); iPair++)
    {
        if (iPair%10000 == 0) {
            cout << "processing pair number " << iPair << endl;
        }
        //cout << "processing pair number " << iPair << endl;


        //if (iPair == 80000){break;}

        pairTree->GetEntry(iPair);




        if (pair1->withinRadius(0.05, 0.3))
        {

            bool triggerFired = false;
            bool fromKaon = false;

            StTriggerId trigId = pair1->triggerIds();


            if (trigId.isTrigger(370601) || trigId.isTrigger(370611) || trigId.isTrigger(370621))
            {
                triggerFired = true;
            }

            if (trigId.isTrigger(370501) || trigId.isTrigger(370511) || trigId.isTrigger(370522) || trigId.isTrigger(370531))
            {
                triggerFired = true;
            }


            if (pair1->invarientMass() > .4921 && pair1->invarientMass() < .4990)
            {
                fromKaon = true;
            }



            if (triggerFired)
            {


                blueFillNo   = pair1->runInfo().beamFillNumber(1); //1 = blue beam
                yellowFillNo = pair1->runInfo().beamFillNumber(0); //0 = yellow beam

                //cout << blueFillNo << "  " << yellowFillNo << endl;


                if (polarizationOfFill_B[blueFillNo] == 0 || polarizationOfFill_Y[yellowFillNo] == 0)
                {
                    continue;
                }


                hInvarM->Fill(pair1->invarientMass());

                TVector3 spinVec;


                sum = pair1->piPlusLV() + pair1->piMinusLV();
                sumB = sum; //blue beam.


                //yellow beam must rotate around y axis by pi so the eta cut can be the same for both beams.
                sumY = sum;
                sumY.RotateY(PI);


                double randomSpin = r.Uniform(0, 1);

                int randomSpinBit;

                if (randomSpin >=0 && randomSpin <0.25)  {
                    randomSpinBit = 5;
                }
                if (randomSpin >=0.25 && randomSpin <0.5) {
                    randomSpinBit = 6;
                }
                if (randomSpin >=0.5 && randomSpin <0.75) {
                    randomSpinBit = 9;
                }
                if (randomSpin >=0.75 && randomSpin <1.0) {
                    randomSpinBit = 10;
                }


                //CHECK CUTS
                if (sumB.Pt() > ptCutLo && sumB.Pt() < ptCutHi && sumB.M() > mCutLo && sumB.M() < mCutHi && sumB.Eta() > etaCutLo && sumB.Eta() < etaCutHi && useBlueBeam == true)
                {

                    //BLUE BEAM SPIN UP: spin bin 9 and 10
                    if (pair1->spinBit() == 9 || pair1->spinBit() == 10)
                    {
                        bin = hNumberUp->FindBin(pair1->phiSR('b'));
                        //hNumberUp->Fill(pair1->phiSR('b'));



                        polOfBinSumUp[bin] += polarizationOfFill_B[blueFillNo];
                        pErrorOfBinUp[bin] += polErrOfFill_B[blueFillNo];
                    }

                    //BLUE BEAM SPIN DOWN: spin bin 5 and 6
                    if (pair1->spinBit() == 5 || pair1->spinBit() == 6)
                    {
                        bin = hNumberDown->FindBin(pair1->phiSR('b'));
                        hNumberDown->Fill(pair1->phiSR('b'));

                        polOfBinSumDown[bin] += polarizationOfFill_B[blueFillNo];
                        pErrorOfBinDown[bin] += polErrOfFill_B[blueFillNo];
                    }

                }//end blue cuts

                TVector3 Pa;
                Pa.SetXYZ(0, 0, 1);   //blue is unpolarized beam

                TVector3 Pb;
                Pb.SetXYZ(0, 0, -1);  //yellow is polarized beam


                if (sumY.Pt()>ptCutLo && sumY.Pt() < ptCutHi && sumY.M() > mCutLo && sumY.M() < mCutHi && sumY.Eta() > etaCutLo && sumY.Eta() < etaCutHi && useYellowBeam == true)
                {

                    //YELLOW BEAM SPIN UP: spin bin 6 and 10
                    //if (pair1->spinBit() == 6 || pair1->spinBit() == 10)
                    if (randomSpinBit == 6 || randomSpinBit == 10)

                    {

                        totalPairsFinal++;


                        spinVec.SetXYZ(0, 1, 0);

                        TVector3 Ph = pair1->piPlusLV().Vect() + pair1->piMinusLV().Vect();
                        TVector3 Rh  = pair1->piPlusLV().Vect() - pair1->piMinusLV().Vect();


                        double cosPhi_S = -Pb.Unit().Cross(Ph).Unit() * Pb.Unit().Cross(spinVec).Unit();

                        double cosPhi_R = Ph.Unit().Cross(Pb).Unit() * Ph.Unit().Cross(Rh).Unit();

                        double sinPhi_S = Ph.Cross(spinVec) * Pb.Unit() / (Pb.Unit().Cross(Ph).Mag() * Pb.Unit().Cross(spinVec).Mag());

                        double sinPhi_R = Pb.Cross(Rh) * Ph.Unit() / (Ph.Unit().Cross(Pb).Mag() * Ph.Unit().Cross(Rh).Mag());



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

                        //cout <<  "phisr = " << phi_S_R << endl;



                        bin = hNumberUp->FindBin(phi_S_R);
                        hNumberUp->Fill(phi_S_R);

                        polOfBinSumUp[bin] += polarizationOfFill_Y[yellowFillNo];
                        pErrorOfBinUp[bin] += polErrOfFill_Y[yellowFillNo];
                    }
                    //YELLOW BEAM SPIN DOWN: spin bit 5 and 9
                    if (randomSpinBit == 5 || randomSpinBit == 9)
                    {

                        totalPairsFinal++;

                        spinVec.SetXYZ(0, -1, 0);

                        TVector3 Ph = pair1->piPlusLV().Vect() + pair1->piMinusLV().Vect();
                        TVector3 Rh  = pair1->piPlusLV().Vect() - pair1->piMinusLV().Vect();


                        double cosPhi_S = -Pb.Unit().Cross(Ph).Unit() * Pb.Unit().Cross(spinVec).Unit();

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

                        //	cout <<  "phisr = " << phi_S_R << endl;


                        bin = hNumberDown->FindBin(phi_S_R);
                        hNumberDown->Fill(phi_S_R);

                        polOfBinSumDown[bin] += polarizationOfFill_Y[yellowFillNo];
                        pErrorOfBinDown[bin] += polErrOfFill_Y[yellowFillNo];
                    }
                }//end yellow cuts





            }//end triger check
        }//end radius check
    }//end pairTree loop


    //CALCULATE ASYMMETRY BIN BY BIN
    cout << "\n";
    cout << "<----CALCULATING ASYMMETRY---->" << endl;
    cout << "\n";
    //*
    for (int ibin=1; ibin<=binNumber; ibin++)
    {

        if (ibin <= binNumber*0.5)
        {
            double nUp   = hNumberUp->GetBinContent(ibin);
            double nUpPi = hNumberUp->GetBinContent(ibin+binNumber*0.5);

            double nDown   = hNumberDown->GetBinContent(ibin);
            double nDownPi = hNumberDown->GetBinContent(ibin+binNumber*0.5);


            cout << nUp << "  " << nUpPi << "  " << nDown << "  " << nDownPi << "  "  << endl;

            int binIndexPi = ibin+binNumber*0.5;

            double avgPolA = (polOfBinSumUp[ibin]+polOfBinSumDown[binIndexPi])/(nUp+nDownPi);
            double avgPolB = (polOfBinSumUp[binIndexPi]+polOfBinSumDown[ibin])/(nUpPi+nDown);

            double realAvgPol = (polOfBinSumUp[ibin]+polOfBinSumDown[binIndexPi]+polOfBinSumUp[binIndexPi]+polOfBinSumDown[ibin])/(nUp+nUpPi+nDown+nDownPi);

        }
        else
        {
            double nUp   = hNumberUp->GetBinContent(ibin);
            double nUpPi = hNumberUp->GetBinContent(ibin-binNumber*0.5);

            double nDown   = hNumberDown->GetBinContent(ibin);
            double nDownPi = hNumberDown->GetBinContent(ibin-binNumber*0.5);

            int binIndexPi = ibin-binNumber*0.5;

            cout << nUp << "  " << nUpPi << "  " << nDown << "  " << nDownPi << "  "  << endl;


            double avgPolA = (polOfBinSumUp[ibin]+polOfBinSumDown[binIndexPi])/(nUp+nDownPi);
            double avgPolB = (polOfBinSumUp[binIndexPi]+polOfBinSumDown[ibin])/(nUpPi+nDown);

            double realAvgPol = (polOfBinSumUp[ibin]+polOfBinSumDown[binIndexPi]+polOfBinSumUp[binIndexPi]+polOfBinSumDown[ibin])/(nUp+nUpPi+nDown+nDownPi);

            double realAvgPolE = (pErrorOfBinUp[ibin]+pErrorOfBinDown[binIndexPi]+pErrorOfBinUp[binIndexPi]+pErrorOfBinDown[ibin])/(nUp+nUpPi+nDown+nDownPi);

        }


        cout << avgPolA << "   " << avgPolB << endl;




        hDiff->SetBinContent(ibin, sqrt(nUp*nDownPi) - sqrt(nDown*nUpPi));

        //hAut->SetBinContent(ibin, (1/avgPolA * sqrt(nUp*nDownPi) - 1/avgPolB * sqrt(nDown*nUpPi)) / (sqrt(nUp*nDownPi) + sqrt(nDown*nUpPi))    );


        hAut->SetBinContent(ibin, 1/realAvgPol * (sqrt(nUp*nDownPi) - sqrt(nDown*nUpPi)) / (sqrt(nUp*nDownPi) + sqrt(nDown*nUpPi))    );




        //error
        if (realAvgPol*pow(sqrt(nUp*nDownPi)+sqrt(nDown*nUpPi), 2) != 0)
        {

            double a = sqrt(nUp*nDownPi);
            double b = sqrt(nUpPi*nDown);


            double firstTerm = realAvgPol**2 * (nUpPi*nDown*(nUp+nDownPi) + nDownPi*nUp*(nUpPi+nDown));

            //double secondTerm = ((nUp*nDownPi)**2 +(nUpPi*nDown)**2 - 2*nUp*nDown*nUpPi*nDownPi)*realAvgPolE**2;

            double secondTerm = 0;


            double binError = 1/realAvgPol**2 * 1/(a+b)**2 * sqrt(firstTerm + secondTerm);


        }
        else
        {
            double binError = 0.01;
            cout << "bin " << ibin << " Has problem with error" << endl;
        }

        hAut->SetBinError(ibin, binError);

    }//end Asym calc

    //*/

    //DRAW HISTOGRAMS

    hInvarM->Draw();

    TCanvas* cNup = new TCanvas();
    hNumberUp->Draw();

    TCanvas* cNdown = new TCanvas();
    hNumberDown->Draw();

    TCanvas* cAut = new TCanvas();
    cAut->SetName("cAut");

    TF1* fitFunc = new TF1("fitFunc","[0]*sin(x)+[1]",-PI,PI);
    //hAut->Fit("fitFunc","R");
    hAut->Draw();

    hAut->GetXaxis()->SetTitle("#phi_{S} - #phi_{R}");

    char title[150];
    sprintf(title, "%.1f < P_{T}^{#pi^{+}#pi^{-}} < %.1f  %.1f < M_{inv}^{#pi^{+}#pi^{-}} < %.1f  %.1f < #eta^{#pi^{+}#pi^{-}} < %.1f", ptCutLo, ptCutHi, mCutLo, mCutHi, etaCutLo, etaCutHi);

    hAut->SetTitle(title);





    //SAVE CANVAS


    stringstream pt;
    stringstream eta;
    stringstream mass;

    string part1 = "_ptBin";
    string part2 = "_massBin";
    string part3 = "_etaBin";

    string ptBinStr;
    string etaBinStr;
    string massBinStr;


    pt << ptBin;

    eta << etaBin;

    mass << massBin;

    if (ptBin == 9) {
        ptBinStr = "All";
    }
    else {
        ptBinStr = pt.str();
    }

    if (massBin == 9) {
        massBinStr = "All";
    }
    else {
        massBinStr = mass.str();
    }

    if (etaBin == 9) {
        etaBinStr = "All";
    }
    else {
        etaBinStr = eta.str();
    }

    cout << "total pairs " << totalPairsFinal << endl;

    string outFileName = "./resultsTesting/piover2issue"+part1+ptBinStr+part2+massBinStr+part3+etaBinStr+".root";
    TFile* outFile = new TFile(outFileName.c_str(),"Recreate");


    cout << "---WRITING FILE---" << endl;
    //cAut->SaveAs(outFileName.c_str());
    hAut->Write();
    hNumberUp->Write();
    hNumberDown->Write();

    cout << "---END---" << endl;
}