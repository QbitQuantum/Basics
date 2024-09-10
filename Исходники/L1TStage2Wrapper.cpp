bool L1TStage2Wrapper::fillParameters(const string& parameterFile)
/*****************************************************************/
{
    TEnv params;
    int status = params.ReadFile(parameterFile.c_str(),EEnvLevel(0));
    if(status!=0) 
    {
        cout<<"[ERROR] Cannot read parameter file "<<parameterFile<<"\n"; 
        return false;
    }
    // towers
    m_params.setTowerLsbH       (params.GetValue("towerLsbH"        , 0.5));
    m_params.setTowerLsbE       (params.GetValue("towerLsbE"        , 0.5));
    m_params.setTowerLsbSum     (params.GetValue("towerLsbSum"      , 0.5));
    m_params.setTowerNBitsH     (params.GetValue("towerNBitsH"      , 8));
    m_params.setTowerNBitsE     (params.GetValue("towerNBitsE"      , 8));
    m_params.setTowerNBitsSum   (params.GetValue("towerNBitsSum"    , 9));
    m_params.setTowerNBitsRatio (params.GetValue("towerNBitsRatio"  , 3));
    m_params.setTowerEncoding   (params.GetValue("towerEncoding"    , false));

    // EG
    m_params.setEgLsb                (params.GetValue("egLsb"                      , 0.5));
    m_params.setEgSeedThreshold      (params.GetValue("egSeedThreshold"            , 2.));
    m_params.setEgNeighbourThreshold (params.GetValue("egNeighbourThreshold"       , 1.));
    m_params.setEgHcalThreshold      (params.GetValue("egHcalThreshold"            , 1.));
    m_params.setEgMaxHcalEt          (params.GetValue("egMaxHcalEt"                , 0.));
    m_params.setEgEtToRemoveHECut    (params.GetValue("egEtToRemoveHECut"          , 128.));
    m_params.setEgPUSType            (params.GetValue("egPUSType"               , "None"));

    stringstream egTrimmingLUTFile;
    egTrimmingLUTFile << getenv("CMSSW_BASE") << "/src/" << params.GetValue("egTrimmingLUTFile", "L1Trigger/L1TCalorimeter/data/egTrimmingLUT.txt");
    std::ifstream egTrimmingLUTStream(egTrimmingLUTFile.str());
    if(!egTrimmingLUTStream.is_open())
    {
        cout<<"[ERROR] Cannot open " << egTrimmingLUTFile.str()<<"\n";
        return false;
    }
    std::shared_ptr<l1t::LUT> egTrimmingLUT( new l1t::LUT(egTrimmingLUTStream) );
    m_params.setEgTrimmingLUT(egTrimmingLUT);

    stringstream egCompressShapesLUTFile;
    egCompressShapesLUTFile << getenv("CMSSW_BASE") << "/src/" << params.GetValue("egCompressShapesLUTFile", "L1Trigger/L1TCalorimeter/data/egCompressShapesLUT.txt");
    std::ifstream egCompressShapesLUTStream(egCompressShapesLUTFile.str());
    if(!egCompressShapesLUTStream.is_open())
    {
        cout<<"[ERROR] Cannot open " << egCompressShapesLUTFile.str()<<"\n";
        return false;
    }
    std::shared_ptr<l1t::LUT> egCompressShapesLUT( new l1t::LUT(egCompressShapesLUTStream) );
    m_params.setEgCompressShapesLUT(egCompressShapesLUT);

    stringstream egMaxHOverELUTFile;
    egMaxHOverELUTFile << getenv("CMSSW_BASE") << "/src/" << params.GetValue("egMaxHOverELUTFile", "L1Trigger/L1TCalorimeter/data/egMaxHOverELUT.txt");
    std::ifstream egMaxHOverELUTStream(egMaxHOverELUTFile.str());
    if(!egMaxHOverELUTStream.is_open())
    {
        cout<<"[ERROR] Cannot open " << egMaxHOverELUTFile.str()<<"\n";
        return false;
    }
    std::shared_ptr<l1t::LUT> egMaxHOverELUT( new l1t::LUT(egMaxHOverELUTStream) );
    m_params.setEgMaxHOverELUT(egMaxHOverELUT);

    stringstream egShapeIdLUTFile;
    egShapeIdLUTFile << getenv("CMSSW_BASE") << "/src/" << params.GetValue("egShapeIdLUTFile", "L1Trigger/L1TCalorimeter/data/egShapeIdLUT.txt");
    std::ifstream egShapeIdLUTStream(egShapeIdLUTFile.str());
    if(!egShapeIdLUTStream.is_open())
    {
        cout<<"[ERROR] Cannot open " << egShapeIdLUTFile.str()<<"\n";
        return false;
    }
    std::shared_ptr<l1t::LUT> egShapeIdLUT( new l1t::LUT(egShapeIdLUTStream) );
    m_params.setEgShapeIdLUT(egShapeIdLUT);

    stringstream egIsoLUTFile;
    egIsoLUTFile << getenv("CMSSW_BASE") << "/src/" << params.GetValue("egIsoLUTFile", "L1Trigger/L1TCalorimeter/data/egIsoLUT_PU40bx25.txt");
    std::ifstream egIsoLUTStream(egIsoLUTFile.str());
    if(!egIsoLUTStream.is_open())
    {
        cout<<"[ERROR] Cannot open " << egIsoLUTFile.str()<<"\n";
        return false;
    }
    std::shared_ptr<l1t::LUT> egIsoLUT( new l1t::LUT(egIsoLUTStream) );
    m_params.setEgIsolationLUT(egIsoLUT);

    m_params.setEgIsoAreaNrTowersEta       (params.GetValue("egIsoAreaNrTowersEta"       , 2));
    m_params.setEgIsoAreaNrTowersPhi       (params.GetValue("egIsoAreaNrTowersPhi"       , 4));
    m_params.setEgIsoVetoNrTowersPhi       (params.GetValue("egIsoVetoNrTowersPhi"       , 3));
    //m_params.setEgIsoPUEstTowerGranularity (params.GetValue("egIsoPUEstTowerGranularity" , 1));
    //m_params.setEgIsoMaxEtaAbsForTowerSum  (params.GetValue("egIsoMaxEtaAbsForTowerSum"  , 4));
    //m_params.setEgIsoMaxEtaAbsForIsoSum    (params.GetValue("egIsoMaxEtaAbsForIsoSum"    , 27));
    std::vector<double> egPUSParams(3);
    egPUSParams[0] = params.GetValue("egPUSParams.0" , 1.);
    egPUSParams[1] = params.GetValue("egPUSParams.1" , 4.);
    egPUSParams[2] = params.GetValue("egPUSParams.2" , 27.);
    m_params.setEgPUSParams(egPUSParams);

    stringstream egCalibrationLUTFile;
    egCalibrationLUTFile << getenv("CMSSW_BASE") << "/src/" << params.GetValue("egCalibrationLUTFile", "L1Trigger/L1TCalorimeter/data/egCalibrationLUT.txt");
    std::ifstream egCalibrationLUTStream(egCalibrationLUTFile.str());
    if(!egCalibrationLUTStream.is_open())
    {
        cout<<"[ERROR] Cannot open " << egCalibrationLUTFile.str()<<"\n";
        return false;
    }
    std::shared_ptr<l1t::LUT> egCalibrationLUT( new l1t::LUT(egCalibrationLUTStream) );
    m_params.setEgCalibrationLUT(egCalibrationLUT);

    // Tau
    m_params.setTauLsb                (params.GetValue("tauLsb"                        , 0.5));
    m_params.setTauSeedThreshold      (params.GetValue("tauSeedThreshold"              , 0.));
    m_params.setTauNeighbourThreshold (params.GetValue("tauNeighbourThreshold"         , 0.));
    m_params.setTauIsoPUSType         (params.GetValue("tauIsoPUSType"                 , "None"));

    m_params.setTauIsoAreaNrTowersEta       (params.GetValue("tauIsoAreaNrTowersEta"       , 2));
    m_params.setTauIsoAreaNrTowersPhi       (params.GetValue("tauIsoAreaNrTowersPhi"       , 4));
    m_params.setTauIsoVetoNrTowersPhi       (params.GetValue("tauIsoVetoNrTowersPhi"       , 2));

    std::vector<double> tauPUSParams(3);
    tauPUSParams[0] = params.GetValue("tauPUSParams.0" , 1.);
    tauPUSParams[1] = params.GetValue("tauPUSParams.1" , 4.);
    tauPUSParams[2] = params.GetValue("tauPUSParams.2" , 27.);
    m_params.setTauPUSParams(tauPUSParams);

    stringstream tauIsoLUTFile;
    tauIsoLUTFile << getenv("CMSSW_BASE") << "/src/" << params.GetValue("tauIsoLUTFile", "L1Trigger/L1TCalorimeter/data/tauIsoLUT.txt");
    std::ifstream tauIsoLUTStream(tauIsoLUTFile.str());
    if(!tauIsoLUTStream.is_open())
    {
        cout<<"[ERROR] Cannot open " << tauIsoLUTFile.str()<<"\n";
        return false;
    }
    std::shared_ptr<l1t::LUT> tauIsoLUT( new l1t::LUT(tauIsoLUTStream) );
    m_params.setTauIsolationLUT(tauIsoLUT);

    stringstream tauCalibrationLUTFile;
    tauCalibrationLUTFile<< getenv("CMSSW_BASE") << "/src/" << params.GetValue("tauCalibrationLUTFile", "L1Trigger/L1TCalorimeter/data/tauCalibrationLUT.txt");
    std::ifstream tauCalibrationLUTStream(tauCalibrationLUTFile.str());
    if(!tauCalibrationLUTStream.is_open())
    {
        cout<<"[ERROR] Cannot open " << tauCalibrationLUTFile.str()<<"\n";
        return false;
    }
    std::shared_ptr<l1t::LUT> tauCalibrationLUT( new l1t::LUT(tauCalibrationLUTStream) );
    m_params.setTauCalibrationLUT(tauCalibrationLUT);


    return true;
}