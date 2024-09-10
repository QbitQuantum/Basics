int MPTreeDrawer (TString detName, int structId, int layerRing, int stripReadoutMode=0)
{
    setTDRStyle();

    DetName.push_back("BPIX");
    DetName.push_back("FPIX");
    DetName.push_back("TIB");
    DetName.push_back("TOB");

    for(unsigned int i=0; i<DetName.size(); i++) {
        if(DetName.at(i)!=detName) continue;
        DetIndex=i;
        break;
    }
    if(DetIndex<0) {
        printf("Wrong detector name. Possible names are:");
        for(unsigned int i=0; i<DetName.size(); i++) printf("%s ",DetName.at(i).Data());
            printf("\nStopping...");
        return 1;
    }
    VLayer = structId;
    LayerRing = layerRing;
    StripReadMode = stripReadoutMode;

    if(nLayers[DetIndex]==1) { LayerRing=0; VLayer=0; }


    logFile = fopen ( "log.txt","w" );

    runsFile = fopen ( "runs.txt","w" );

    TFile *file = new TFile ( inputFileName );

    TString moduleType="";
    TString readoutMode="";
    if ( DetIndex<2 ) {
        moduleType="Pixel";

    } else {
        moduleType="Strip";
        readoutMode = (StripReadMode==0?"_peak":"_deconvolution");

    }
    TString TreeBaseDir("Si"+moduleType+calibrationType+"Calibration"+readoutMode+"_result_");

    std::vector<int> iovs;
    std::vector<int> iovs_;
    double totLumi=0.0;
    int nIOVs;

// Finding the IOV borders from the directory names in each ROOT file
    TList *list = file->GetListOfKeys();
    int nKeys = list->GetSize();
    for ( int keyNum=0; keyNum<nKeys; keyNum++ ) {
        TKey* key = ( TKey* ) list->At ( keyNum );
        TString str ( key->GetName() );
        if ( !str.BeginsWith ( TreeBaseDir ) ) {
            continue;
        }
        str.ReplaceAll ( TreeBaseDir,"" );
        int run = str.Atoi();
// Putting run number to the list of IOVs of the file
        iovs.push_back ( run );
        iovs_.push_back ( run );
    }
    nIOVs=iovs.size();
    if(nIOVs<1) {
        printf("No trees found with name: %s...\nExiting...\n",TreeBaseDir.Data());
        return -1;
    }
// Changing the run number if it is 1
    if ( iovs_[0]==1 && nIOVs>2 ) {
        iovs_[0]=2*iovs[1]-iovs[2];
    }
    iovs_[0]=190000;	// Setting the first run of the first IOV to a custom value
    iovs_.push_back(209091);	// Setting the last run of the last IOV to a custom value


    // Direct values from the tree
    UInt_t detId;
    Float_t value;
    // Struct of additional values from the tree
    struct treeStr{
        Float_t delta;
        Float_t error;
        UInt_t paramIndex;
    };
    Float_t error=0.f;
    treeStr treeStruct;
    std::vector<TGraphErrors*> graphLA;
    std::vector<TGraphErrors*> graphLAinput;
    int nDetParts=-1;
    bool isOldFormat = false;

    // Looping over entries in each iov tree
    for ( int iov=0; iov<nIOVs+1; iov++ ) {
        char treeName[300];
        sprintf ( treeName,"%s%d",TreeBaseDir.Data(),iovs[iov] );
    // Reading tree for input tree
        if(iov==nIOVs) {
            TString TreeBaseDirIn = TreeBaseDir;
            TreeBaseDirIn.ReplaceAll("_result_","_input");
            sprintf ( treeName,"%s",TreeBaseDirIn.Data());
        }
        TTree *tree = 0;
        tree = ( TTree* ) ( TDirectoryFile* ) file->Get ( treeName );
        Long64_t nEntries = tree->GetEntries();

        int runNr = (iov<nIOVs)?iovs.at(iov):555;
        if(tree) printf ( "Got Tree %d\twith name: %s for IOV: %d - %lld entries\n",iov,treeName,runNr,nEntries );

        fprintf(runsFile,"%d\n",iovs_.at(iov));
        if(iov>=nIOVs-nPointsToSkip && iov<nIOVs) continue;

        tree->SetBranchAddress ( "detId",&detId );
        tree->SetBranchAddress ( "value",&value );
        if(tree->GetBranch("error")) isOldFormat = true;
        if(isOldFormat) tree->SetBranchAddress ( "error",&error ); else
        tree->SetBranchAddress ( "treeStruct",&treeStruct );


        double iovWidth=-1.f;
        if(iovWidthIsFixed || runNr==555) iovWidth = fixedIOVwidth[DetIndex]; 
        else {
    // Getting more precise value of luminosity (calculation started from the first IOV run)
            iovWidth = lumisInIOV(iovs_.at(0),iovs_.at(iov+1)) - lumisInIOV(iovs_.at(0),iovs_.at(iov));
            if(iovWidth<0.0) {
    // Getting less precise value of luminosity (calculation started from this IOV run)
                iovWidth = lumisInIOV(iovs_.at(iov),iovs_.at(iov+1));
                printf("Less precise estimation of luminosity for IOV: %d (%d-%d)\n",iov+1,iovs_.at(iov),iovs_.at(iov+1));
            }
        }
        if(iovWidth<0 && iov<nIOVs) {
            printf("   ERROR!!! Luminosity for IOV %d with runs: %d - %d not found. Skipping.\n",iov,iovs_.at(iov),iovs_.at(iov+1));
            continue;
        }
        iovWidth*=lumiScale;                           // Correcting luminosity to the real (lumiCalc provides slightly larger value)
        if(!iovWidthIsFixed) iovWidth/=1000.0;         // Converting from /pb to /fb
        totLumi+=iovWidth;                             // Updating total luminosity of all IOVs


        for ( Long64_t entry=0; entry<nEntries; entry++ ) {
        //             printf("  Entry %lld\n",entry);
            tree->GetEntry ( entry );
            if(!isOldFormat) error = treeStruct.error;
            int histoId=histoIdx ( detId );
            // fprintf ( logFile,"  entry: %lld\thistoId: %d\tvalue: %.3f\terror: %.3f\n",entry,histoId,value,error );
            if ( histoId<0 ) {
                continue;
            }
            while(histoId>=(int)graphLA.size() && iov<nIOVs) {
                TGraphErrors* graph = new TGraphErrors ( nIOVs-nPointsToSkip );
                graphLA.push_back(graph);
            }
            while(histoId>=(int)graphLAinput.size() && iov>=nIOVs) {
        //printf("0. histoId: %d size: %d\n",histoId,(int)graphLAinput.size());
                TGraphErrors* graph = new TGraphErrors ( 1 );
                graphLAinput.push_back(graph);
            }
            if ( DetIndex==0 || DetIndex==2 || DetIndex==3 ) {
                if(iov<nIOVs) {
                    graphLA.at(histoId)->SetPoint ( iov, totLumi - 0.5*iovWidth, value*3.81 );	// BPIX, TIB, TOB
                    graphLA.at(histoId)->SetPointError ( iov,0.f,error*3.81 );
                } else {    // For line of input LA value
                //printf("1. histoId: %d size: %d\n",histoId,(int)graphLAinput.size());
                    Double_t centerY;
                    Double_t centerX;
                    graphLA.at(histoId)->GetPoint(graphLA.at(histoId)->GetN()/2,centerX,centerY);
                    graphLAinput.at(histoId)->SetPoint ( 0, centerX, value*3.81 );	// BPIX, TIB, TOB
                    graphLAinput.at(histoId)->SetPointError ( 0,centerX*2.5,error*3.81 );
                }
            } else if ( DetIndex==1 ) {
                if(iov<nIOVs) {
                    graphLA.at(histoId)->SetPoint ( iov, totLumi + 0.5*iovWidth, value* ( -1.3 ) );	// FPIX
                    graphLA.at(histoId)->SetPointError ( iov,0.f,error*1.3 );
                } else {    // For line of input LA value
                    Double_t centerY;
                    Double_t centerX;
                    graphLA.at(histoId)->GetPoint(graphLA.at(histoId)->GetN()/2,centerX,centerY);
                    graphLAinput.at(histoId)->SetPoint ( 0, centerX + 0.5*iovWidth, value* ( -1.3 ) );	// FPIX
                    graphLAinput.at(histoId)->SetPointError ( 0,centerX*2.5,error*1.3 );
                }
            }
        }	  // End of loop over entries
    }	// End of loop over IOVs
    nDetParts=graphLA.size();
    printf("Found %d different substructures\n",nDetParts);
    // if(LayerRing==0) nRings[DetIndex]=nDetParts;        // Updating the number of rings to draw
    if(nDetParts<1) {
        fclose(logFile);
        fclose(runsFile);
        return 1;
    }

    float minY_ = minY_det[DetIndex];
    float maxY_ = maxY_det[DetIndex];

    if(minY!=0.f || maxY!=0.f) {
        minY_ = minY;
        maxY_ = maxY;
    }

    if(autoScaleY) {
        minY_=999.9;
        maxY_=-999.9;
    }
    fprintf ( logFile,"File: %s\n",inputFileName.Data() );
    for ( int i=0; i<nDetParts; i++ ) {
    // fprintf ( logFile,"ID: %d Values: ",i );
        for ( int j=0; j<graphLA.at(i)->GetN(); j++ ) {
    // Updating min and max values of LA for axis of the plot
            Double_t val;
            Double_t null;
            graphLA.at(i)->GetPoint ( j,null,val );
            fprintf(logFile,"detPart: %d\tiov %d\tRun: %d\tValue: %.3f\n",i+1,j+1,iovs.at(j),val);
            if ( val<minY_ && autoScaleY && val!=0.0) {
                minY_=val;
            }
            if ( val>maxY_ && autoScaleY && val!=0.0) {
                maxY_=val;
            }
    // fprintf ( logFile," %.3f",val );
        }
    // fprintf ( logFile,"\n" );
    }	// End of loop over Detector parts

    if(autoScaleY) {
        minY_= ( minY_>0 ) ?minY_*0.98:minY_*1.02;
        maxY_= ( maxY_>0 ) ?maxY_*1.05:maxY_*0.95;
    }

    //Drawing canvas
    //    TCanvas *c1 = new TCanvas ( "c1","Canvas1",1000,600 );
    TCanvas *c1 = new TCanvas ( "c1","Canvas1");
    // Drawing empty histogram
    TString Y_title;
    if(calibrationType=="LorentzAngle") Y_title = "tan(#theta_{LA}^{shift}) "; else
    if(calibrationType=="Backplane") Y_title = "#DeltaW_{BP}^{shift} "; else
    Y_title = "??? ";
    drawEmptyHisto ( 0.0,totLumi,"2012 Integrated Luminosity [fb^{-1}]",minY_,maxY_,Y_title,"empty1" );
    // Drawing each graph for input values
    if(drawInput) {
        for ( int i=0; i<nDetParts; i++ ) {
            setGraphStyle ( graphLAinput.at(i),i,1 );
            graphLAinput.at(i)->SetMarkerStyle(0);
            graphLAinput.at(i)->Draw( "Lsame" );
        }
    }
    // Drawing each graph for output values
    for ( int i=0; i<nDetParts; i++ ) {
        setGraphStyle ( graphLA.at(i),i,0 );
        graphLA.at(i)->Draw ( "Psame" );
    }

    TString structName = ( LayerRing==0 ) ?"L":"R";
    TString structNameFull = ( LayerRing==0 ) ?"Layer":"Ring";

    //Drawing legend pane
    TLegend *leg;
    leg = new TLegend ( 0.7,0.77,0.98,0.95,NULL,"brNDC" );
        
    int nCols = (nDetParts>3)?2:1;

    for(int i=0; i<=nDetParts/2; i++) {
        int i2=0;
        TString legName_("");
        if(LayerRing==1) {
            i2 = i+nDetParts/2;
            legName_+="Layer";
        }
        if(LayerRing==0) {
            i2 = nDetParts-1-i;
            legName_+="Ring";
        }
        if(nDetParts<4) {
            i2 = i*2+1;
            i = i2-1;
        }
        char legName[100];
        if(i<nDetParts/2) {
            sprintf(legName,"%s %d",legName_.Data(),i+1);
            leg->AddEntry( graphLA.at(i),legName,"p" );
            sprintf(legName,"%s %d",legName_.Data(),i2+1);
            leg->AddEntry( graphLA.at(i2),legName,"p" );
            if(i==nDetParts/2-1 && nDetParts%2==0) break;
        } else {
            sprintf(legName,"%s %d",legName_.Data(),i+1);
            leg->AddEntry( graphLA.at(i),legName,"p" );
        }
    }
    setLegendStyle ( leg,nCols,nDetParts);


    if ( drawLegend ) {
        leg->Draw();
    }

    //    // Drawing CMS Preliminary label
    //    TLatex *TextCMS = new TLatex(0.2,0.89,"CMS Preliminary 2012");
    //    TextCMS->SetTextColor(1);
    //    TextCMS->SetNDC();
    //    TextCMS->SetTextFont(62);
    //    TextCMS->Draw();

    char Data_[150];
    sprintf(Data_,"%s %s %d",DetName.at(DetIndex).Data(),structNameFull.Data(),VLayer);
    TLatex *TextData = new TLatex(0.2,0.89,Data_);
    TextData->SetTextColor(1);
    TextData->SetNDC();
    TextData->SetTextFont(62);
    TextData->Draw();

    char savePath[150];

    gROOT->ProcessLine(".mkdir -p "+outputPath);
    sprintf ( savePath,"%s/%s_%s_%s%d%s",outputPath.Data(),calibrationType.Data(),DetName.at(DetIndex).Data(),structName.Data(),VLayer, readoutMode.Data() );
    c1->Print( TString ( savePath ) +=".eps" );
    //    c1->SaveAs ( TString ( savePath ) +=".pdf" );
    //    c1->SaveAs ( TString ( savePath ) +=".C" );
    //    c1->SaveAs ( TString ( savePath ) +=".root" );

    fclose ( logFile );

    fclose ( runsFile );

    return 0;
}