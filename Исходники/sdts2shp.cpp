static void WriteAttributeDBF( const char * pszShapefile,
                               SDTSTransfer * poTransfer,
                               const char * pszMODN )

{
    SDTSAttrReader      *poAttrReader;

/* -------------------------------------------------------------------- */
/*      Fetch a reference to the indexed Pointgon reader.                */
/* -------------------------------------------------------------------- */
    poAttrReader = (SDTSAttrReader *) 
        poTransfer->GetLayerIndexedReader( poTransfer->FindLayer( pszMODN ) );
    
    if( poAttrReader == NULL )
    {
        fprintf( stderr, "Failed to open %s.\n",
                 poTransfer->GetCATD()->GetModuleFilePath( pszMODN ) );
        return;
    }

    poAttrReader->Rewind();

/* -------------------------------------------------------------------- */
/*      Create the database file, and our basic set of attributes.      */
/* -------------------------------------------------------------------- */
    DBFHandle   hDBF;
    char        szDBFFilename[1024];

    sprintf( szDBFFilename, "%s.dbf", pszShapefile );

    hDBF = DBFCreate( szDBFFilename );
    if( hDBF == NULL )
    {
        fprintf( stderr, "Unable to create shapefile .dbf for `%s'\n",
                 pszShapefile );
        return;
    }

    DBFAddField( hDBF, "SDTSRecId", FTInteger, 8, 0 );

/* -------------------------------------------------------------------- */
/*      Prepare the schema.                                             */
/* -------------------------------------------------------------------- */
    char        **papszMODNList = CSLAddString( NULL, pszMODN );

    AddPrimaryAttrToDBFSchema( hDBF, poTransfer, papszMODNList );

    CSLDestroy( papszMODNList );
    
/* ==================================================================== */
/*      Process all the records in the module.                          */
/* ==================================================================== */
    SDTSAttrRecord *poRecord;
    int         iRecord = 0;

    while((poRecord = (SDTSAttrRecord*)poAttrReader->GetNextFeature()) != NULL)
    {
        DBFWriteIntegerAttribute( hDBF, iRecord, 0,
                                  poRecord->oModId.nRecord );

        WriteAttrRecordToDBF( hDBF, iRecord, poTransfer, poRecord->poATTR );

        if( !poAttrReader->IsIndexed() )
            delete poRecord;
        
        iRecord++;
    }

/* -------------------------------------------------------------------- */
/*      Close, and cleanup.                                             */
/* -------------------------------------------------------------------- */
    DBFClose( hDBF );
}    