int YLD::Execute()
{
    CheckInputData();
    initialOutputs();

    struct tm timeinfo;
    LocalTime(m_date, &timeinfo);
    timeinfo.tm_mon = 0;
    timeinfo.tm_mday = 0;
    timeinfo.tm_hour = 0;
    timeinfo.tm_min = 0;
    timeinfo.tm_sec = 0;
    timeinfo.tm_isdst = false;
    time_t tYear = mktime(&timeinfo);

    time_t harvestDate = tYear + m_harvestDate;

#pragma omp parallel for
    for (int i = 0; i < m_nCells; i++)
    {
        if (m_date > harvestDate && !m_harvested)
        {
            m_harvested = true;
            m_common->m_classification = (int) (m_classification[i]);
            //Harvest index
            //float harvestIndex = 0.0f;// potential harvest index for a given day
            //float totalPlantET = 0.0f;//actual ET simulated during life of plant
            //float totalPlantPET = 0.0f;//potential ET simulated during life of plant
            ////get total ET and PET(see grow.f Line 289-292) from zhiqiang
            if (m_frPHU[i] > 0.5 && m_frPHU[i] < m_frDeclineLAI[i])
            {
                m_totalPlantET[i] += m_totalWaterUptake[i] + m_soilET[i];
                m_totalPlantPET[i] += m_PET[i];
            }
            // water deficiency factor
            m_wur[i] = 100.0f;
            if (m_totalPlantPET[i] > 10)
                m_wur[i] *= m_totalPlantET[i] / m_totalPlantPET[i];

            //get optimal harvest index, p309 5:2.4.1
            m_HI[i] = m_HiOpt[i] * 100.0f * m_frPHU[i] / (100.0f * m_frPHU[i] + exp(11.1f - 10.0f * m_frPHU[i]));
            m_Hiact[i] = m_HI[i] - m_HiMin[i] * (m_wur[i] / (m_wur[i] + exp(6.13f - 0.0883f * m_wur[i]))) + m_HiMin[i];

            m_HI[i] = min(m_HI[i], m_Hiact[i]);
            //float yield = 0.0f;
            if (m_HiOpt[i] > 1.001)
                m_yield[i] = m_biomass[i] * (1.0f - 1.0f / (1.0f + m_HI[i]));
            else
                m_yield[i] = m_biomassAG[i] * m_HI[i];
            m_yield[i] = max(0.0f, m_yield[i]);
            m_harvestEfficiency[i] = 0.5f; //harvestEfficiency read from database
            //IsGrain should read from database
            if (m_common->IsGrain())//grain harvest, no residue, see harvgrainop.f
            {
                m_yield[i] *= m_harvestEfficiency[i];
                m_yieldN[i] = max(0.0f, min(m_yield[i] * m_frNyld[i], 0.85f * m_biomassN[i]));
                m_yieldP[i] = max(0.0f, min(m_yield[i] * m_frPyld[i], 0.85f * m_biomassP[i]));

                m_biomass[i] -= m_yield[i];
            }
            else //biomass harvest, has residue, residue redistribute to soil layer, see harvestop.f
            {
                //divide yield to two parts:clip and yield
                m_clip[i] = m_yield[i] * (1 - m_harvestEfficiency[i]);
                m_yield[i] -= m_clip[i];
                m_clip[i] = max(0.0f, m_clip[i]);
                m_yield[i] = max(0.0f, m_yield[i]);

                //harvest index override  read from database
                //get N&P in clip and yield[i]
                m_yieldN[i] = max(0.0f, min(m_yield[i] * m_frNyld[i], 0.8f * (m_biomassN[i])));
                m_yieldP[i] = max(0.0f, min(m_yield[i] * m_frPyld[i], 0.8f * (m_biomassP[i])));
                m_clipN[i] = max(0.0f, min(m_clip[i] * m_frNyld[i], m_biomassN[i] -
                                                                    m_yieldN[i])); //N in clip residual,needed by nitrient cycling module
                m_clipP[i] = max(0.0f, min(m_clip[i] * m_frPyld[i], m_biomassP[i] -
                                                                    m_yieldP[i])); //P in clip residual,needed by nitrient cycling module
                //reset LAI, frPHU and root fraction
                m_removeFraction[i] = 1.0f; //the fraction of remove part to aboveground part
                if (m_biomass[i] - m_biomassRoot[i] > 1.0e-6)
                    m_removeFraction[i] = (m_yield[i] + m_clip[i]) / (m_biomass[i] - m_biomassRoot[i]);
                m_removeFraction[i] = min(1.0f, m_removeFraction[i]);

                //root part
                m_rootFraction[i] = m_biomassRoot[i] / m_biomass[i];
                m_rootLeft[i] = (m_biomass[i] - m_biomassRoot[i]) * (1 - m_removeFraction[i]) * m_rootFraction[i] /
                                (1.0f - m_rootFraction[i]);
                m_rootRemove[i] = m_biomassRoot[i] - m_rootLeft[i];  //removed root as residual
                m_rootRemoveFraction[i] = 0.0f;
                if (m_biomassRoot[i] > 1.0e-6) m_rootRemoveFraction[i] = m_rootRemove[i] / (m_biomassRoot[i]);
                m_rootRemoveN[i] = m_rootRemoveFraction[i] * (m_biomassN[i]);
                m_rootRemoveP[i] = m_rootRemoveFraction[i] * (m_biomassP[i]);

                //remove aboveground and root biomass from total biomass
                //change the LAI and growth step
                if (m_biomass[i] > 0.001)
                {
                    m_LAI[i] *= 1.0f - m_removeFraction[i];
                    if (m_frPHU[i] < 0.999)
                        m_frPHU[i] *= 1.0f - m_removeFraction[i];

                    m_biomass[i] -= m_yield[i] + m_clip[i] + m_rootRemove[i];
                    m_biomassN[i] -= m_yieldN[i] + m_clipN[i] + m_rootRemoveN[i];
                    m_biomassP[i] -= m_yieldP[i] + m_clipP[i] + m_rootRemoveP[i];

                    m_biomass[i] = min(0.0f, m_biomass[i]);
                    m_biomassN[i] = min(0.0f, m_biomassP[i]);
                    m_biomassP[i] = min(0.0f, m_biomassP[i]);

                    m_biomassRoot[i] = m_biomass[i] * (0.4f - 0.2f * m_frPHU[i]);
                }
                else
                {
                    m_biomass[i] = 0.0f;
                    m_biomassN[i] = 0.0f;
                    m_biomassP[i] = 0.0f;
                    m_biomassRoot[i] = 0.0f;

                    m_LAI[i] = 0.0f;
                    m_frPHU[i] = 0.0f;
                }
            }
        }
    }

    //m_lastSWE = m_swe;
    return 0;
}