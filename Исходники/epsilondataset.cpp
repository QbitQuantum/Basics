void GDALRegister_EPSILON()

{
    if( !GDAL_CHECK_VERSION( "EPSILON driver" ) )
        return;

    if( GDALGetDriverByName( "EPSILON" ) != NULL )
        return;

    GDALDriver *poDriver = new GDALDriver();

    poDriver->SetDescription( "EPSILON" );
    poDriver->SetMetadataItem( GDAL_DCAP_RASTER, "YES" );

    poDriver->SetMetadataItem( GDAL_DMD_LONGNAME, "Epsilon wavelets" );
    poDriver->SetMetadataItem( GDAL_DMD_HELPTOPIC, "frmt_epsilon.html" );
    poDriver->SetMetadataItem( GDAL_DMD_CREATIONDATATYPES, "Byte" );

    CPLString osMethods;
    char** papszFBID = eps_get_fb_info(EPS_FB_ID);
    char** papszFBIDIter = papszFBID;
    while(papszFBIDIter && *papszFBIDIter)
    {
        osMethods += "       <Value>";
        osMethods += *papszFBIDIter;
        osMethods += "</Value>\n";
        papszFBIDIter ++;
    }
    eps_free_fb_info(papszFBID);

    CPLString osOptionList;
    osOptionList.Printf(
"<CreationOptionList>"
"   <Option name='TARGET' type='int' description='target size reduction as a percentage of the original (0-100)' default='75'/>"
"   <Option name='FILTER' type='string-select' description='Filter ID' default='daub97lift'>"
"%s"
"   </Option>"
"   <Option name='BLOCKXSIZE' type='int' description='Tile Width. Between 32 and 1024' default='256'/>"
"   <Option name='BLOCKYSIZE' type='int' description='Tile Height. Between 32 and 1024' default='256'/>"
"   <Option name='MODE' type='string-select' default='OTLPF'>"
"       <Value>NORMAL</Value>"
"       <Value>OTLPF</Value>"
"   </Option>"
"   <Option name='RGB_RESAMPLE' type='boolean' description='if RGB must be resampled to 4:2:0' default='YES'/>"
"   <Option name='RASTERLITE_OUTPUT' type='boolean' description='if Rasterlite header and footers must be inserted' default='FALSE'/>"
"</CreationOptionList>", osMethods.c_str()  );

    poDriver->SetMetadataItem( GDAL_DMD_CREATIONOPTIONLIST,
                               osOptionList.c_str() );

    poDriver->pfnOpen = EpsilonDataset::Open;
    poDriver->pfnIdentify = EpsilonDataset::Identify;
    poDriver->pfnCreateCopy = EpsilonDatasetCreateCopy;

    poDriver->SetMetadataItem( GDAL_DCAP_VIRTUALIO, "YES" );

    GetGDALDriverManager()->RegisterDriver( poDriver );
}