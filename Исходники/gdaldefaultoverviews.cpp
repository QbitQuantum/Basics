CPLErr
GDALDefaultOverviews::BuildOverviewsSubDataset(
    const char * pszPhysicalFile,
    const char * pszResampling,
    int nOverviews, int * panOverviewList,
    int nBands, int * panBandList,
    GDALProgressFunc pfnProgress, void * pProgressData)

{
    if( osOvrFilename.length() == 0 && nOverviews > 0 )
    {
        VSIStatBufL sStatBuf;

        int iSequence = 0;  // Used after for.
        for( iSequence = 0; iSequence < 100; iSequence++ )
        {
            osOvrFilename.Printf( "%s_%d.ovr", pszPhysicalFile, iSequence );
            if( VSIStatExL( osOvrFilename, &sStatBuf,
                            VSI_STAT_EXISTS_FLAG ) != 0 )
            {
                CPLString osAdjustedOvrFilename;

                if( poDS->GetMOFlags() & GMO_PAM_CLASS )
                {
                    osAdjustedOvrFilename.Printf(
                        ":::BASE:::%s_%d.ovr",
                        CPLGetFilename(pszPhysicalFile),
                        iSequence );
                }
                else
                {
                    osAdjustedOvrFilename = osOvrFilename;
                }

                poDS->SetMetadataItem( "OVERVIEW_FILE",
                                       osAdjustedOvrFilename,
                                       "OVERVIEWS" );
                break;
            }
        }

        if( iSequence == 100 )
            osOvrFilename = "";
    }

    return BuildOverviews( NULL, pszResampling, nOverviews, panOverviewList,
                           nBands, panBandList, pfnProgress, pProgressData );
}