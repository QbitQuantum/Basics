CPLErr RasterliteDataset::CleanOverviewLevel(int nOvrFactor)
{
    CPLString osSQL;
    
    if (nLevel != 0)
        return CE_Failure;
    
/* -------------------------------------------------------------------- */
/*      Find the index of the overview matching the overview factor     */
/* -------------------------------------------------------------------- */
    int iLev;
    for(iLev=1;iLev<nResolutions;iLev++)
    {
        if (fabs(padfXResolutions[0] * nOvrFactor - padfXResolutions[iLev]) < 1e-15 &&
            fabs(padfYResolutions[0] * nOvrFactor - padfYResolutions[iLev]) < 1e-15)
            break;
    }
    
    if (iLev == nResolutions)
        return CE_None;
        
/* -------------------------------------------------------------------- */
/*      Now clean existing overviews at that resolution                 */
/* -------------------------------------------------------------------- */

    osSQL.Printf("BEGIN");
    OGR_DS_ExecuteSQL(hDS, osSQL.c_str(), NULL, NULL);
    
    CPLString osResolutionCond;
    osResolutionCond.Printf(
                 "pixel_x_size >= %.15f AND pixel_x_size <= %.15f AND "
                 "pixel_y_size >= %.15f AND pixel_y_size <= %.15f",
                 padfXResolutions[iLev] - 1e-15, padfXResolutions[iLev] + 1e-15,
                 padfYResolutions[iLev] - 1e-15, padfYResolutions[iLev] + 1e-15);
    
    osSQL.Printf("DELETE FROM \"%s_rasters\" WHERE id "
                 "IN(SELECT id FROM \"%s_metadata\" WHERE %s)",
                  osTableName.c_str(), osTableName.c_str(),
                  osResolutionCond.c_str());
    OGR_DS_ExecuteSQL(hDS, osSQL.c_str(), NULL, NULL);

    osSQL.Printf("DELETE FROM \"%s_metadata\" WHERE %s",
                  osTableName.c_str(), osResolutionCond.c_str());
    OGR_DS_ExecuteSQL(hDS, osSQL.c_str(), NULL, NULL);
    
    OGRLayerH hRasterPyramidsLyr = OGR_DS_GetLayerByName(hDS, "raster_pyramids");
    if (hRasterPyramidsLyr)
    {
        osSQL.Printf("DELETE FROM raster_pyramids WHERE table_prefix = '%s' AND %s",
                      osTableName.c_str(), osResolutionCond.c_str());
        OGR_DS_ExecuteSQL(hDS, osSQL.c_str(), NULL, NULL);
    }
    
    osSQL.Printf("COMMIT");
    OGR_DS_ExecuteSQL(hDS, osSQL.c_str(), NULL, NULL);
    
    return CE_None;
}