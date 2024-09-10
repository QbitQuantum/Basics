void GTIFFBuildOverviewMetadata( const char *pszResampling,
                                 GDALDataset *poBaseDS,
                                 CPLString &osMetadata )

{
    osMetadata = "<GDALMetadata>";

    if( pszResampling && STARTS_WITH_CI(pszResampling, "AVERAGE_BIT2") )
        osMetadata +=
            "<Item name=\"RESAMPLING\" sample=\"0\">"
            "AVERAGE_BIT2GRAYSCALE</Item>";

    if( poBaseDS->GetMetadataItem( "INTERNAL_MASK_FLAGS_1" ) )
    {
        for( int iBand = 0; iBand < 200; iBand++ )
        {
            CPLString osItem;
            CPLString osName;

            osName.Printf( "INTERNAL_MASK_FLAGS_%d", iBand + 1 );
            if( poBaseDS->GetMetadataItem( osName ) )
            {
                osItem.Printf( "<Item name=\"%s\">%s</Item>",
                               osName.c_str(),
                               poBaseDS->GetMetadataItem( osName ) );
                osMetadata += osItem;
            }
        }
    }

    const char* pszNoDataValues = poBaseDS->GetMetadataItem("NODATA_VALUES");
    if( pszNoDataValues )
    {
        CPLString osItem;
        osItem.Printf( "<Item name=\"NODATA_VALUES\">%s</Item>",
                       pszNoDataValues );
        osMetadata += osItem;
    }

    if( !EQUAL(osMetadata,"<GDALMetadata>") )
        osMetadata += "</GDALMetadata>";
    else
        osMetadata = "";
}