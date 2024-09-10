void CellLine::setParametrization(const string parametrization_type)
{
    if(parametrization_type == "LQ_noDt" && isLQ_noDtLoaded)
        selectedParametrization = &CellLine::parametrization_LQ_noDt;
    
    else if(parametrization_type == "LQ_noDt_T" && isLQ_noDt_TLoaded)
        selectedParametrizationT = &CellLine::parametrization_LQ_noDt_T;
    
    else if(parametrization_type == "LQ" && isLQloaded)
        selectedParametrization = &CellLine::parametrization_LQ;
    
    else if((parametrization_type == "LQ2" || parametrization_type == "LQ2_interpolated_readfile") && isLQ2loaded)
    {
        selectedParametrization = &CellLine::parametrization_LQ2;
        selectedDamageEnhancement = &CellLine::interpolatedDamageEnhancement;
        selectedEtaGeneration = &CellLine::readDamageEnhancement;
        needEtaGenerated = true;
    }
    
    else if(parametrization_type == "LQ3" && isLQ3loaded)
    {
        selectedParametrization = &CellLine::parametrization_LQ3;
        selectedDamageEnhancement = &CellLine::interpolatedDamageEnhancement;
        selectedEtaGeneration = &CellLine::readDamageEnhancement;
        needEtaGenerated = true;
    }
    
    else if(parametrization_type == "LQ2_interpolated_analytic" && isLQ2loaded)
    {
        selectedParametrization = &CellLine::parametrization_LQ2;
        selectedDamageEnhancement = &CellLine::interpolatedDamageEnhancement;
        selectedEtaGeneration = &CellLine::analyticDamageEnhancement;
        needEtaGenerated = true;
    }
    
    else if(parametrization_type == "LQ2_interpolated_MC" && isLQ2loaded)
    {
        selectedParametrization = &CellLine::parametrization_LQ2;
        selectedDamageEnhancement = &CellLine::interpolatedDamageEnhancement;
        selectedEtaGeneration = &CellLine::damageEnhancement;
        needEtaGenerated = true;
    }
    
    else if(parametrization_type == "LQ2_punctual_analytic" && isLQ2loaded)
    {
        selectedParametrization = &CellLine::parametrization_LQ2;
        selectedDamageEnhancement = &CellLine::analyticDamageEnhancement;
    }
    
    else if(parametrization_type == "LQ2_punctual_MC" && isLQ2loaded)
    {
        selectedParametrization = &CellLine::parametrization_LQ2;
        selectedDamageEnhancement = &CellLine::damageEnhancement;
    }
    
    else
    {
        cerr << "CellLine: The selected X-ray parametrization is not provided or has not been loaded." << endl;
        exit(1);
    }

    //clog << "Selected " << parametrization_type << " parametrization for X-rays." << endl;

    if(needEtaGenerated)
    {
        cout << "Generating damage enhancement... ";
        double d = 100;
        int etaCounter = 0;
        int points = 200;
        do {
            doseForEta[etaCounter] = d;
            etaPre[etaCounter] = (*this.*selectedEtaGeneration)(d);
            etaCounter++;
            d = pow( double(10), 2 + etaCounter * (4 + log10(5))/(points - 1) );
        } while( d <= 5e6 );
        needEtaGenerated = false;
        cout << "done." << endl
             << endl << flush;
    }
}