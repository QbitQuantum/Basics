Int_t Tprime::SetParameterPoints( std::string sbModelName,
                                  std::string bModelName ) {
    //
    // Fit the data with S+B model.
    // Make a snapshot of the S+B parameter point.
    // Profile with POI=0.
    // Make a snapshot of the B parameter point
    // (B model is the S+B model with POI=0
    //

    Double_t poi_value_for_b_model = 0.0;

    // get S+B model config from workspace
    RooStats::ModelConfig * pSbModel = (RooStats::ModelConfig *)pWs->obj(sbModelName.c_str());
    pSbModel->SetWorkspace(*pWs);

    // get parameter of interest set
    const RooArgSet * poi = pSbModel->GetParametersOfInterest();

    // get B model config from workspace
    RooStats::ModelConfig * pBModel = (RooStats::ModelConfig *)pWs->obj(bModelName.c_str());
    pBModel->SetWorkspace(*pWs);

    // make sure that data has been loaded
    if (!data) return -1;

    // find parameter point for global maximum with the S+B model,
    // with conditional MLEs for nuisance parameters
    // and save the parameter point snapshot in the Workspace
    RooAbsReal * nll = pSbModel->GetPdf()->createNLL(*data);
    RooAbsReal * profile = nll->createProfile(RooArgSet());
    profile->getVal(); // this will do fit and set POI and nuisance parameters to fitted values
    RooArgSet * poiAndNuisance = new RooArgSet();
    if(pSbModel->GetNuisanceParameters())
        poiAndNuisance->add(*pSbModel->GetNuisanceParameters());
    poiAndNuisance->add(*pSbModel->GetParametersOfInterest());
    pWs->defineSet("SPlusBModelParameters", *poiAndNuisance);
    pWs->saveSnapshot("SPlusBFitParameters",*poiAndNuisance);
    pSbModel->SetSnapshot(*poi);
    RooArgSet * sbModelFitParams = (RooArgSet *)poiAndNuisance->snapshot();
    cout << "\nWill save these parameter points that correspond to the fit to data" << endl;
    sbModelFitParams->Print("v");
    delete profile;
    delete nll;
    delete poiAndNuisance;
    delete sbModelFitParams;

    //

    // Find a parameter point for generating pseudo-data
    // with the background-only data.
    // Save the parameter point snapshot in the Workspace
    nll = pBModel->GetPdf()->createNLL(*data);
    profile = nll->createProfile(*poi);
    ((RooRealVar *)poi->first())->setVal(poi_value_for_b_model);
    profile->getVal(); // this will do fit and set nuisance parameters to profiled values
    poiAndNuisance = new RooArgSet();
    if(pBModel->GetNuisanceParameters())
        poiAndNuisance->add(*pBModel->GetNuisanceParameters());
    poiAndNuisance->add(*pBModel->GetParametersOfInterest());
    pWs->defineSet("parameterPointToGenerateData", *poiAndNuisance);
    pWs->saveSnapshot("parametersToGenerateData",*poiAndNuisance);
    pBModel->SetSnapshot(*poi);
    RooArgSet * paramsToGenerateData = (RooArgSet *)poiAndNuisance->snapshot();
    cout << "\nShould use these parameter points to generate pseudo data for bkg only" << endl;
    paramsToGenerateData->Print("v");
    delete profile;
    delete nll;
    delete poiAndNuisance;
    delete paramsToGenerateData;

    return 0;
}