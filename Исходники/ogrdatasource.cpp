OGRLayer *OGRDataSource::CopyLayer( OGRLayer *poSrcLayer, 
                                    const char *pszNewName, 
                                    char **papszOptions )

{
    OGRFeatureDefn *poSrcDefn = poSrcLayer->GetLayerDefn();
    OGRLayer *poDstLayer = NULL;

/* -------------------------------------------------------------------- */
/*      Create the layer.                                               */
/* -------------------------------------------------------------------- */
    if( !TestCapability( ODsCCreateLayer ) )
    {
        CPLError( CE_Failure, CPLE_NotSupported, 
                  "This datasource does not support creation of layers." );
        return NULL;
    }

    CPLErrorReset();
    poDstLayer = CreateLayer( pszNewName, poSrcLayer->GetSpatialRef(),
                              poSrcDefn->GetGeomType(), papszOptions );
    
    if( poDstLayer == NULL )
        return NULL;

/* -------------------------------------------------------------------- */
/*      Add fields.  Default to copy all field.                         */
/*      If only a subset of all fields requested, then output only      */
/*      the selected fields, and in the order that they were            */
/*      selected.                                                       */
/* -------------------------------------------------------------------- */
    int         iField;
    
    for( iField = 0; iField < poSrcDefn->GetFieldCount(); iField++ )
        poDstLayer->CreateField( poSrcDefn->GetFieldDefn(iField) );

/* -------------------------------------------------------------------- */
/*      Check if the destination layer supports transactions and set a  */
/*      default number of features in a single transaction.             */
/* -------------------------------------------------------------------- */
    int nGroupTransactions = 0;
    if( poDstLayer->TestCapability( OLCTransactions ) )
        nGroupTransactions = 128;

/* -------------------------------------------------------------------- */
/*      Transfer features.                                              */
/* -------------------------------------------------------------------- */
    OGRFeature  *poFeature;

    poSrcLayer->ResetReading();

    if( nGroupTransactions <= 0 )
    {
      while( TRUE )
      {
        OGRFeature      *poDstFeature = NULL;

        poFeature = poSrcLayer->GetNextFeature();
        
        if( poFeature == NULL )
            break;

        CPLErrorReset();
        poDstFeature = OGRFeature::CreateFeature( poDstLayer->GetLayerDefn() );

        if( poDstFeature->SetFrom( poFeature, TRUE ) != OGRERR_NONE )
        {
            delete poFeature;
            CPLError( CE_Failure, CPLE_AppDefined,
                      "Unable to translate feature %ld from layer %s.\n",
                      poFeature->GetFID(), poSrcDefn->GetName() );
            return poDstLayer;
        }

        poDstFeature->SetFID( poFeature->GetFID() );

        OGRFeature::DestroyFeature( poFeature );

        CPLErrorReset();
        if( poDstLayer->CreateFeature( poDstFeature ) != OGRERR_NONE )
        {
            OGRFeature::DestroyFeature( poDstFeature );
            return poDstLayer;
        }

        OGRFeature::DestroyFeature( poDstFeature );
      }
    }
    else
    {
      int i, bStopTransfer = FALSE, bStopTransaction = FALSE;
      int nFeatCount = 0; // Number of features in the temporary array
      int nFeaturesToAdd = 0;
      while( !bStopTransfer )
      {
        OGRFeature **papoDstFeature =
            (OGRFeature **)CPLCalloc(sizeof(OGRFeature *), nGroupTransactions);

/* -------------------------------------------------------------------- */
/*      Fill the array with features                                    */
/* -------------------------------------------------------------------- */
        for( nFeatCount = 0; nFeatCount < nGroupTransactions; nFeatCount++ )
        {
            poFeature = poSrcLayer->GetNextFeature();

            if( poFeature == NULL )
            {
                bStopTransfer = 1;
                break;
            }

            CPLErrorReset();
            papoDstFeature[nFeatCount] =
                        OGRFeature::CreateFeature( poDstLayer->GetLayerDefn() );

            if( papoDstFeature[nFeatCount]->SetFrom( poFeature, TRUE ) != OGRERR_NONE )
            {
                OGRFeature::DestroyFeature( poFeature );
                CPLError( CE_Failure, CPLE_AppDefined,
                          "Unable to translate feature %ld from layer %s.\n",
                          poFeature->GetFID(), poSrcDefn->GetName() );
                bStopTransfer = TRUE;
                break;
            }

            papoDstFeature[nFeatCount]->SetFID( poFeature->GetFID() );

            OGRFeature::DestroyFeature( poFeature );
        }
        nFeaturesToAdd = nFeatCount;

        CPLErrorReset();
        bStopTransaction = FALSE;
        while( !bStopTransaction )
        {
            bStopTransaction = TRUE;
            poDstLayer->StartTransaction();
            for( i = 0; i < nFeaturesToAdd; i++ )
            {
                if( poDstLayer->CreateFeature( papoDstFeature[i] ) != OGRERR_NONE )
                {
                    nFeaturesToAdd = i;
                    bStopTransfer = TRUE;
                    bStopTransaction = FALSE;
                }
            }
            if( bStopTransaction )
                poDstLayer->CommitTransaction();
            else
                poDstLayer->RollbackTransaction();
        }

        for( i = 0; i < nFeatCount; i++ )
            OGRFeature::DestroyFeature( papoDstFeature[i] );
      }
    }
    return poDstLayer;
}