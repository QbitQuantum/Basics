double massbal_getQualError()
//
//  Input:   none
//  Output:  none
//  Purpose: computes water quality routing mass balance error.
//
{
    int    j, p;
    double maxQualError = 0.0;
    double finalStorage;
    double totalInflow;
    double totalOutflow;
    double cf;

    // --- analyze each pollutant
    for (p = 0; p < Nobjects[POLLUT]; p++)
    {
        // --- get final mass stored in nodes and links
        finalStorage = 0.0;
        for (j = 0; j < Nobjects[NODE]; j++)
        {
            finalStorage += Node[j].newVolume * Node[j].newQual[p];
        }
        for (j = 0; j < Nobjects[LINK]; j++)
        {
            finalStorage += Link[j].newVolume * Link[j].newQual[p];
        }
        QualTotals[p].finalStorage = finalStorage;

        // --- compute % difference between total inflow and outflow
        totalInflow  = QualTotals[p].dwInflow +
                       QualTotals[p].wwInflow +
                       QualTotals[p].gwInflow +
                       QualTotals[p].iiInflow +
                       QualTotals[p].exInflow +
                       QualTotals[p].initStorage;
        totalOutflow = QualTotals[p].outflow +
                       QualTotals[p].pumpedVol +
                       finalStorage;
        QualTotals[p].internalOutflow = 0.0;
        if ( fabs(totalInflow - totalOutflow) < 0.001 )
        {
            QualTotals[p].internalOutflow = TINY;
        }
        else if ( totalInflow > 0.0 )
        {
            QualTotals[p].internalOutflow = 100.0 * (1.0 - totalOutflow / totalInflow);
        }
        else if ( totalOutflow > 0.0 )
        {
            QualTotals[p].internalOutflow = 100.0 * (totalInflow / totalOutflow - 1.0);
        }

        // --- update max. error among all pollutants
        if ( fabs(QualTotals[p].internalOutflow) > fabs(maxQualError) )
        {
            maxQualError = QualTotals[p].internalOutflow;
        }

        // --- convert totals to reporting units (lbs, kg, or Log(Count))
        cf = LperFT3;
        if ( Pollut[p].units == COUNT )
        {
            QualTotals[p].dwInflow     = LOG10(cf * QualTotals[p].dwInflow);
            QualTotals[p].wwInflow     = LOG10(cf * QualTotals[p].wwInflow);
            QualTotals[p].gwInflow     = LOG10(cf * QualTotals[p].gwInflow);
            QualTotals[p].iiInflow     = LOG10(cf * QualTotals[p].iiInflow);
            QualTotals[p].exInflow     = LOG10(cf * QualTotals[p].exInflow);
            QualTotals[p].outflow      = LOG10(cf * QualTotals[p].outflow);
            QualTotals[p].pumpedVol    = LOG10(cf * QualTotals[p].pumpedVol);
            QualTotals[p].initStorage  = LOG10(cf * QualTotals[p].initStorage);
            QualTotals[p].finalStorage = LOG10(cf * QualTotals[p].finalStorage);
        }
        else
        {
            cf = cf * UCF(MASS);
            if ( Pollut[p].units == UG ) cf /= 1000.0;
            QualTotals[p].dwInflow     *= cf;
            QualTotals[p].wwInflow     *= cf; 
            QualTotals[p].gwInflow     *= cf; 
            QualTotals[p].iiInflow     *= cf; 
            QualTotals[p].exInflow     *= cf; 
            QualTotals[p].outflow      *= cf; 
            QualTotals[p].pumpedVol    *= cf; 
            QualTotals[p].initStorage  *= cf; 
            QualTotals[p].finalStorage *= cf; 
        }
    }
    QualError = maxQualError;
    return maxQualError;
}