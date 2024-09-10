PigsGUI::PigsGUI(const TGWindow *p) : TGMainFrame(p, fGUIsizeX, fGUIsizeY)  {
    // Creates the GUI
    if(fVerbose) std::cout<<__PRETTY_FUNCTION__ << std::endl;
    daq = 0; storage = 0; ev = 0;               // Initialize local variables
    year = month = day = hour = min = sec = 0;
    fAcqThread = 0;
    keepAcquiring  = kFALSE;
    useIntegration = kTRUE;
    const int32_t fHistColors[] = { kMagenta+1, kGreen+1, kBlue+1, kRed+1 };
    fAboutMsg = (char*)
"\n"
"\n"
"        _____  _____  ______ _______\n"
"       |_____]   |   |  ____ |______\n"
"       |       __|__ |_____| ______|\n"
"\n"
"\n"
" *** Position Indicating Gamma Sensor   ***\n"
"  * CAEN DT-5781 Data Acquisition System *\n"
"         Four Channel Version\n"
"\n"
"   by Ondrej Chvala <*****@*****.**>\n"
"        version 0.097, July 2015\n"
"   https://github.com/ondrejch/DAQ-DT5781\n"
"                 GNU/GPL";
    int32_t i = 0; // helper variable
    for (i=0; i<4; i++) {
        fScaleFactor[i] = 1.0;
        fNormAvgH[i] = 0;
    }
    fIntegralMin = 1;
    fIntegralMax = 16384;

    // *** Main GUI window ***
    fMainGUIFrame = new TGMainFrame(gClient->GetRoot(),10,10,kMainFrame | kVerticalFrame);
    #include "fpigsicon.xpm"
    TImage *tmpicon = TImage::Create();
    tmpicon->SetImageBuffer((char**)fpigsicon_xpm, TImage::kXpm);
    gVirtualX->SetIconPixmap(fMainGUIFrame->GetId(),tmpicon->GetPixmap());
    delete tmpicon;
    fMainGUIFrame->SetName("fMainGUIFrame");
    fMainGUIFrame->SetWindowName("F-PIGS");      // GUI window name
    fMainGUIFrame->SetLayoutBroken(kTRUE);
    ufont = gClient->GetFont("-*-*-bold-r-*-*-16-*-*-*-*-*-*-*");
    // ufont = gClient->GetFont("-*-helvetica-medium-r-normal-*-14-*-*-*-*-*-iso8859-1");
    // ufont = gClient->GetFont("-urw-nimbus sans l-bold-r-normal--0-0-0-0-p-0-iso8859-1");
    valTitle.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
    gClient->GetColorByName("#0000FF",valTitle.fForeground);
    gClient->GetColorByName("#e0e0e0",valTitle.fBackground);
    valTitle.fFillStyle = kFillSolid;
    valTitle.fFont = ufont->GetFontHandle();
    valTitle.fGraphicsExposures = kFALSE;
    uGC = gClient->GetGC(&valTitle, kTRUE);
    fMainTitle = new TGLabel(fMainGUIFrame,"Four-channel Position Identifying Gamma Sensor (F-PIGS)",
            uGC->GetGC(),ufont->GetFontStruct());
    fMainTitle->SetTextJustify(36);
    fMainTitle->SetMargins(0,0,0,0);
    fMainTitle->SetWrapLength(-1);
    fMainGUIFrame->AddFrame(fMainTitle, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fMainTitle->MoveResize(0,0,fGUIsizeX-4,32);
    fMainGUIFrame->Connect("CloseWindow()", "PigsGUI", this, "~PigsGUI()"); // call class destructor on alt+f4
    fMainGUIFrame->DontCallClose();

    // Buttons for main GUI
    fStartDAQ = new TGTextButton(fMainGUIFrame, "Start DAQ");     // start DAQ
    fStartDAQ->SetTextJustify(36);
    fStartDAQ->SetMargins(0,0,0,0);
    fStartDAQ->Resize(90,25);
    fMainGUIFrame->AddFrame(fStartDAQ, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fStartDAQ->MoveResize(50,fGUIsizeY-30,90,25);
    gClient->GetColorByName("green", fColor);
    fStartDAQ->ChangeBackground(fColor);
    fStartDAQ->SetState(kButtonDisabled);
    fStartDAQ->Connect("Clicked()","PigsGUI",this,"RunAcquisition()");

    fStopDAQ = new TGTextButton(fMainGUIFrame, "Stop DAQ");        // stop DAQ
    fStopDAQ->SetTextJustify(36);
    fStopDAQ->SetMargins(0,0,0,0);
    fStopDAQ->Resize(90,25);
    fMainGUIFrame->AddFrame(fStopDAQ, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fStopDAQ->MoveResize(fGUIsizeX-50-90,fGUIsizeY-30,90,25);
    gClient->GetColorByName("red", fColor);
    fStopDAQ->ChangeBackground(fColor);
    fStopDAQ->SetState(kButtonDisabled);
    fStopDAQ->Connect("Clicked()","PigsGUI",this,"StopAcquisition()");

    fExitDAQ = new TGTextButton(fMainGUIFrame, "Exit DAQ");        // exit DAQ
    fExitDAQ->SetTextJustify(36);
    fExitDAQ->SetMargins(0,0,0,0);
    fExitDAQ->Resize(90,25);
    fMainGUIFrame->AddFrame(fExitDAQ, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fExitDAQ->MoveResize(fGUIsizeX/2-45,fGUIsizeY-30,90,25);
    fExitDAQ->Connect("Clicked()","PigsGUI",this,"~PigsGUI()");

    // *** Tab widget ****
    fTabHolder = new TGTab(fMainGUIFrame,fGUIsizeX-4,fGUIsizeX-4);//,uGC->GetGC());

    // *** Container of "CurrentHistogram" ***
    fCurHistFrame = fTabHolder->AddTab("CurrentHistogram");
    fCurHistFrame->SetLayoutManager(new TGVerticalLayout(fCurHistFrame));
    // embedded canvas
    fLatestHistoCanvas = new TRootEmbeddedCanvas("CurrentHEC",fCurHistFrame,fGUIsizeX-10,fGUIsizeY-140);
    Int_t wfLatestHistoCanvas = fLatestHistoCanvas->GetCanvasWindowId();
    cCurrHCanvas = new TCanvas("cCurrHCanvas", 10, 10, wfLatestHistoCanvas);
    fLatestHistoCanvas->AdoptCanvas(cCurrHCanvas);
    cCurrHCanvas->Divide(2,2);
    fCurHistFrame->AddFrame(fLatestHistoCanvas, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fHCurrHProgressBar = new TGHProgressBar(fCurHistFrame,fGUIsizeX-5);
    fHCurrHProgressBar->SetFillType(TGProgressBar::kBlockFill);
    fHCurrHProgressBar->ChangeOptions(kSunkenFrame | kDoubleBorder | kOwnBackground);

    // will reflect user color changes
    gClient->GetColorByName("#ffffff",fColor);
    fHCurrHProgressBar->SetBackgroundColor(fColor);
    fHCurrHProgressBar->SetPosition(1);
    fCurHistFrame->AddFrame(fHCurrHProgressBar, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

    // *** Container of "History" ***
    fTabHisto = fTabHolder->AddTab("History");
    fTabHisto->SetLayoutManager(new TGVerticalLayout(fTabHisto));
    // embedded canvas
    fLastMeas = new TRootEmbeddedCanvas("HistoryHEC",fTabHisto,fGUIsizeX-10,fGUIsizeY-110);
    Int_t wfLastNspectra = fLastMeas->GetCanvasWindowId();
    cLastMeas = new TCanvas("cLastMeas", 10, 10, wfLastNspectra);
    fLastMeas->AdoptCanvas(cLastMeas);
    fMG = new TMultiGraph("fMG","");
    for (i=0; i<4; i++) {
        fGraph[i] = new TGraph();
        fGraph[i]->SetName(Form("gCh%d",i));
        fGraph[i]->SetDrawOption("AP");
        fGraph[i]->SetMarkerColor(fHistColors[i]);
        fGraph[i]->SetMarkerStyle(21);
        fGraph[i]->SetMarkerSize(2.0);
        fGraph[i]->SetLineWidth(0.5);
        fGraph[i]->SetLineColor(i+12);
        fGraph[i]->SetFillStyle(0);
        fMG->Add(fGraph[i]);
    }
    fTabHisto->AddFrame(fLastMeas, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

    // *** Container of "Average" ***
    fTabSum = fTabHolder->AddTab("Average");
    fTabSum->SetLayoutManager(new TGVerticalLayout(fTabSum));
    // embedded canvas
    fSumSpectra = new TRootEmbeddedCanvas("SumHEC",fTabSum,fGUIsizeX-10,fGUIsizeY-110);
    Int_t wfSumSpectra = fSumSpectra->GetCanvasWindowId();
    cSumSpectra = new TCanvas("cSumSpectra", 10, 10, wfSumSpectra);
    fSumSpectra->AdoptCanvas(cSumSpectra);
    cSumSpectra->Divide(2,2);
    for (i=1; i<5; i++) {
        cSumSpectra->GetPad(i)->SetLogx();
        cSumSpectra->GetPad(i)->SetLogy();
    }
    fTabSum->AddFrame(fSumSpectra, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

    // *** Container of "Arrow" ***
    fTabArrow = fTabHolder->AddTab("Arrow");
    fTabArrow->SetLayoutManager(new TGVerticalLayout(fTabArrow));
    fArrowECanvas = new TRootEmbeddedCanvas("ArrowHEC",fTabArrow,fGUIsizeX-10,fGUIsizeY-110);
    Int_t wfArrowECanvas = fArrowECanvas->GetCanvasWindowId();
    cArrowCanvas = new TCanvas("cArrowCanvas", 5, 5, wfArrowECanvas);
    // Draw compass circle
    TEllipse *el1 = new TEllipse(0.5,0.5,0.48,0.48);
    el1->SetFillColor(14);
    el1->SetFillStyle(1001);
    el1->SetLineColor(1);
    el1->SetLineWidth(6);
    el1->Draw();
    // Add bearing labels
    TText *north = new TText(0.5,0.9,"N");
    north->SetTextColor(2);
    north->SetTextSize(0.1);
    north->SetTextAlign(12);
    north->SetTextAlign(21);
    north->Draw();
    TText *south = new TText(0.5,0.04,"S");
    south->SetTextSize(0.1);
    south->SetTextAlign(12);
    south->SetTextAlign(21);
    south->Draw();
    TText *east = new TText(0.92,0.5,"E");
    east->SetTextSize(0.1);
    east->SetTextAlign(12);
    east->SetTextAlign(21);
    east->Draw();
    TText *west = new TText(0.08,0.5,"W");
    west->SetTextSize(0.1);
    west->SetTextAlign(12);
    west->SetTextAlign(21);
    west->Draw();
    // Draw initial arrow pointing North
    ar1 = new TArrow(0.5,0.3,0.5,0.7,0.3,"|>");
    ar1->SetAngle(30);
    ar1->SetLineWidth(5);
    ar1->SetFillColor(4);
    ar1->Draw();
    fArrowECanvas->AdoptCanvas(cArrowCanvas);
    fTabArrow->AddFrame(fArrowECanvas, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

    // *** Container of "Config" ***
    fTabConfig = fTabHolder->AddTab("Config");
    fTabConfig->SetLayoutManager(new TGVerticalLayout(fTabConfig));

    // Acquisition time settings
    fControlFrame = new TGGroupFrame(fTabConfig, "Acquisition time [sec]");
    fControlFrame->SetTitlePos(TGGroupFrame::kCenter);


    // Acquisition time entry
    fAcqTimeFrame = new TGCompositeFrame(fControlFrame, 200, 10, kHorizontalFrame); 
  
    fAcqTimeSlider = new TGHSlider(fAcqTimeFrame,300,kSlider1 | kScaleBoth,-1);
    //fAcqTimeSlider = new TGHSlider(fControlFrame,300,kSlider1 | kScaleBoth,-1);
    fAcqTimeSlider->Connect("PositionChanged(Int_t)", "PigsGUI", this, "SetAcquisitionLoopTimeSlider()");
    //fAcqTimeSlider->Connect("PositionChanged(Int_t)", "TGLabel", fAcqTimeLabel, "SetText(Int_t)");
    fAcqTimeSlider->SetRange(1,6000); // time in 100 ms increments => [0.1 - 600 sec]
    fAcqTimeSlider->SetPosition(fDefaultAcqTime*10); // 10 second acquire time by default


    fAcqTimeFrame->AddFrame(fAcqTimeSlider, new TGLayoutHints(kLHintsNormal, 5, 5, 5, 5));

    //fAcqTimeEntry = new TGNumberEntry(fControlFrame, (Double_t) fDefaultAcqTime ,5,-1, TGNumberFormat::kNESRealOne, TGNumberFormat::kNEAPositive,TGNumberFormat::kNELLimitMinMax, 0.1, 600);
    fAcqTimeEntry = new TGNumberEntry(fAcqTimeFrame, (Double_t) fDefaultAcqTime ,5,-1, TGNumberFormat::kNESRealOne, TGNumberFormat::kNEAPositive,TGNumberFormat::kNELLimitMinMax, 0.1, 600);
    fAcqTimeEntry->GetNumberEntry()->SetToolTipText("Time for one DAQ loop in seconds.");
    fAcqTimeEntry->GetNumberEntry()->Connect("TextChanged(char*)", "PigsGUI", this,
            "SetAcquisitionLoopTimeNumberEntry()");
    fAcqTimeEntry->GetNumberEntry()->Connect("ReturnPressed()", "PigsGUI", this,
            "SetAcquisitionLoopTimeNumberEntry()");
    
    fAcqTimeFrame->AddFrame(fAcqTimeEntry, new TGLayoutHints(kLHintsNormal, 5, 5, 5, 5));
    //fControlFrame->AddFrame(fAcqTimeEntry, new TGLayoutHints(kLHintsNormal, 5, 5, 5, 5));
    
    // Disable acquisition time adjustment until DAQ initialized
    fAcqTimeEntry->SetState(kFALSE);
    fAcqTimeSlider->SetState(kFALSE);
/*
    fAcqTimeLabelFrame = new TGCompositeFrame(fTabConfig, 100, 10, kHorizontalFrame); 
    fAcqTimeLabelText = new TGLabel(fAcqTimeLabelFrame,"Acquire time:",
            uGC->GetGC(),ufont->GetFontStruct());
    fAcqTimeLabelText->SetTextJustify(kTextLeft);
    fAcqTimeLabelText->SetWrapLength(-1);
    fAcqTimeLabel = new TGLabel(fAcqTimeLabelFrame,"    ",
            uGC->GetGC(),ufont->GetFontStruct());
    fAcqTimeLabel->SetTextColor(0x0066ff);
    fAcqTimeLabel->SetTextJustify(kTextCenterX);
    fAcqTimeLabel->SetWrapLength(-1);
    fAcqTimeLabel->SetMinWidth(3);
    fAcqTimeLabelFrame->AddFrame(fAcqTimeLabelText, new TGLayoutHints(kLHintsLeft, 10, 5, 10, 10));
    fAcqTimeLabelFrame->AddFrame(fAcqTimeLabel, new TGLayoutHints(kLHintsRight, 0, 10, 10, 10 ));
  */ 
    fControlFrame->AddFrame(fAcqTimeFrame, new TGLayoutHints(kLHintsTop, 10, 10, 5, 5));
   // fControlFrame->AddFrame(fAcqTimeLabelFrame, new TGLayoutHints(kLHintsBottom, 10, 10, 5, 5));
    fTabConfig->AddFrame(fControlFrame, new TGLayoutHints(kLHintsNormal, 10, 10, 10, 10));    

    // Scale Factor setting
    fScalerFrame = new TGGroupFrame(fTabConfig, "Channel gain compensation");
    fScalerFrame->SetTitlePos(TGGroupFrame::kCenter);
    for (i=0; i<4; i++){
        fScalerInput[i] = new PigsScalerInput(fScalerFrame, Form("ch %d scaling", i));
        fScalerInput[i]->GetEntry()->Connect("TextChanged(char*)", "PigsGUI", this,
                Form("SetGainScalerCh%d()",i));
        fScalerInput[i]->GetEntry()->SetToolTipText(
                "Channel gain is a multiplicative factor used in detector response calculation.");
        fScalerFrame->AddFrame(fScalerInput[i], new TGLayoutHints(kLHintsNormal, 0, 0, 2, 2));
    }
    fTabConfig->AddFrame(fScalerFrame, new TGLayoutHints(kLHintsNormal, 10, 10, 10, 10));
    // Integration Limits
    fIntLimFrame = new TGGroupFrame(fTabConfig, "ADC window for integration");
    fIntLimFrame->SetTitlePos(TGGroupFrame::kCenter);
    fUseIntegration = new TGCheckButton(fIntLimFrame, "Energy integration On/Off");
    fUseIntegration->SetOn(kFALSE);         // Start with regular counts
    fUseIntegration->SetToolTipText("If enabled, the detector response is calculated by integrating "
            "the energy deposited in ADC bins within the limits specidied below.\n"
            "If disabled, the hit count is used as a detector response.");
    fUseIntegration->Connect("Toggled(Bool_t)", "PigsGUI", this, "ToggleUseIntegration()");
    fIntLimFrame->AddFrame(fUseIntegration, new TGLayoutHints(kLHintsNormal, 0, 0, 2, 2));
    fIntLimInputMin = new PigsIntLimInput(fIntLimFrame, "Lower limit");
    fIntLimInputMin->GetEntry()->SetIntNumber(fIntegralMin);
    fIntLimInputMin->GetEntry()->Connect("TextChanged(char*)", "PigsGUI", this, "SetIntegralLimitMin()");
    fIntLimFrame->AddFrame(fIntLimInputMin, new TGLayoutHints(kLHintsNormal, 0, 0, 2, 2));
    fIntLimInputMax = new PigsIntLimInput(fIntLimFrame, "Upper limit");
    fIntLimInputMax->GetEntry()->SetIntNumber(fIntegralMax);
    fIntLimInputMax->GetEntry()->Connect("TextChanged(char*)", "PigsGUI", this, "SetIntegralLimitMax()");
    fIntLimFrame->AddFrame(fIntLimInputMax, new TGLayoutHints(kLHintsNormal, 0, 0, 2, 2));
    fTabConfig->AddFrame(fIntLimFrame, new TGLayoutHints(kLHintsNormal, 10, 10, 10, 10));
    this->ToggleUseIntegration();           // Updates the integration entries' status

    // *** Container of "DT5781" ***
    fTabDT5781 = fTabHolder->AddTab("DT5781");
    fTabDT5781->SetLayoutManager(new TGVerticalLayout(fTabDT5781));
    gClient->GetColorByName("white", fColor);
    fDTinfo = new TGTextView(fTabDT5781,fGUIsizeX-120,fGUIsizeY-150,"DAQ not initialized.",kSunkenFrame,fColor);
    fTabDT5781->AddFrame(fDTinfo, new TGLayoutHints(kLHintsNormal));
    fDTinfo->MoveResize(10,50,fGUIsizeX-120,fGUIsizeY-150);
    fInitDAQ = new TGTextButton(fTabDT5781, "Init DAQ");            // button InitDAQ
    fInitDAQ->SetTextJustify(36);
    fInitDAQ->SetMargins(0,0,0,0);
    fInitDAQ->Resize(90,25);
    fMainGUIFrame->AddFrame(fInitDAQ, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    gClient->GetColorByName("light blue", fColor);
    fInitDAQ->ChangeBackground(fColor);
    fInitDAQ->MoveResize(fGUIsizeX-50-60,50,90,25);
    fInitDAQ->Connect("Clicked()","PigsGUI",this,"InitDAQ()");
    fDisconnectDAQ = new TGTextButton(fTabDT5781, "Disconnect DAQ");  // buttons DisconnectDAQ
    fDisconnectDAQ->SetTextJustify(36);
    fDisconnectDAQ->SetMargins(0,0,0,0);
    fDisconnectDAQ->Resize(90,25);
    fMainGUIFrame->AddFrame(fDisconnectDAQ, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    gClient->GetColorByName("light blue", fColor);
    fDisconnectDAQ->MoveResize(fGUIsizeX-50-60,150,90,25);
    fDisconnectDAQ->ChangeBackground(fColor);
    fDisconnectDAQ->Connect("Clicked()","PigsGUI",this,"DisconnectDAQ()");

    // *** Container of "About" ***
    fTabAbout = fTabHolder->AddTab("About");
    fTabAbout->SetLayoutManager(new TGVerticalLayout(fTabAbout));
    ufont = gClient->GetFont("-*-fixed-medium-r-*-*-15-*-*-*-*-*-*-*");
    fAboutText = new TGTextView(fTabAbout,1,1,"SPIGS",kSunkenFrame);
    fAboutText->SetFont(ufont->GetFontStruct());
    fTabAbout->AddFrame(fAboutText, new TGLayoutHints(kLHintsNormal));
    fAboutText->LoadBuffer(fAboutMsg);

    //-------------------------------------------------------------------------

    // Change to the starting tab
    fTabHolder->SetTab("DT5781");

    // Display the GUI
    fTabHolder->Resize(fTabHolder->GetDefaultSize());
    fMainGUIFrame->AddFrame(fTabHolder, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
    fTabHolder->MoveResize(0,32,fGUIsizeX-2,fGUIsizeY-80);

    fMainGUIFrame->SetMWMHints(kMWMDecorAll, kMWMFuncAll, kMWMInputModeless);
    fMainGUIFrame->MapSubwindows();
    fMainGUIFrame->Resize(fMainGUIFrame->GetDefaultSize());
    fMainGUIFrame->MapWindow();
    fMainGUIFrame->Resize(fGUIsizeX,fGUIsizeY);

    static const int32_t tmpw = 410;        // Constants for About window placement
    static const int32_t tmph = 260;
    fAboutText->MoveResize((fGUIsizeX-tmpw)/2,(fGUIsizeY-tmph)/3,tmpw,tmph);
}