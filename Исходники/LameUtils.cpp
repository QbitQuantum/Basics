std::vector<double> getStateVariableInitialValues(const std::string& lameMaterialModelName,
        const Teuchos::ParameterList& lameMaterialParameters) {

    Teuchos::RCP<LameMaterial> materialModel = constructLameMaterialModel(lameMaterialModelName, lameMaterialParameters);

    int numStateVariables = materialModel->getNumStateVars();

    // Allocate workset space
    std::vector<double> strainRate(6);   // symmetric tensor5
    std::vector<double> spin(3);         // skew-symmetric tensor
    std::vector<double> leftStretch(6);  // symmetric tensor
    std::vector<double> rotation(9);     // full tensor
    std::vector<double> stressOld(6);    // symmetric tensor
    std::vector<double> stressNew(6);    // symmetric tensor
    std::vector<double> stateOld(numStateVariables);  // a single double for each state variable
    std::vector<double> stateNew(numStateVariables);  // a single double for each state variable

    // \todo Set up scratch space for material models using getNumScratchVars() and setScratchPtr().

    // Create the matParams structure, which is passed to LAME
    Teuchos::RCP<LameMatParams> matp = Teuchos::rcp(new LameMatParams());
    matp->nelements = 1;
    matp->dt = 0.0;
    matp->time = 0.0;
    matp->strain_rate = &strainRate[0];
    matp->spin = &spin[0];
    matp->left_stretch = &leftStretch[0];
    matp->rotation = &rotation[0];
    matp->state_old = &stateOld[0];
    matp->state_new = &stateNew[0];
    matp->stress_old = &stressOld[0];
    matp->stress_new = &stressNew[0];

    LameMatProps props;
    parameterListToMatProps(lameMaterialParameters, props);

    // todo Check with Bill to see if props can be a null pointer (meaning no changes to the material properties).

    materialModel->initialize(matp.get(), &props);

    return stateOld;
}