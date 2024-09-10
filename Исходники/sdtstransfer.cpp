int SDTSTransfer::GetBounds( double *pdfMinX, double *pdfMinY,
                             double *pdfMaxX, double *pdfMaxY )

{
    int         bFirst = TRUE;
    
    for( int iLayer = 0; iLayer < GetLayerCount(); iLayer++ )
    {
        if( GetLayerType( iLayer ) == SLTPoint )
        {
            SDTSPointReader     *poLayer;
            SDTSRawPoint    *poPoint;
        
            poLayer = (SDTSPointReader *) GetLayerIndexedReader( iLayer );
            if( poLayer == NULL )
                continue;
            
            poLayer->Rewind();
            while( (poPoint = (SDTSRawPoint*) poLayer->GetNextFeature()) )
            {
                if( bFirst )
                {
                    *pdfMinX = *pdfMaxX = poPoint->dfX;
                    *pdfMinY = *pdfMaxY = poPoint->dfY;
                    bFirst = FALSE;
                }
                else
                {
                    *pdfMinX = MIN(*pdfMinX,poPoint->dfX);
                    *pdfMaxX = MAX(*pdfMaxX,poPoint->dfX);
                    *pdfMinY = MIN(*pdfMinY,poPoint->dfY);
                    *pdfMaxY = MAX(*pdfMaxY,poPoint->dfY);
                }
                
                if( !poLayer->IsIndexed() )
                    delete poPoint;
            }
        }
        
        else if( GetLayerType( iLayer ) == SLTRaster )
        {
            SDTSRasterReader    *poRL;
            double              adfGeoTransform[6];
            double              dfMinX, dfMaxX, dfMinY, dfMaxY;

            poRL = GetLayerRasterReader( iLayer );
            if( poRL == NULL )
                continue;

            poRL->GetTransform( adfGeoTransform );

            dfMinX = adfGeoTransform[0];
            dfMaxY = adfGeoTransform[3];
            dfMaxX = adfGeoTransform[0] + poRL->GetXSize()*adfGeoTransform[1];
            dfMinY = adfGeoTransform[3] + poRL->GetYSize()*adfGeoTransform[5];

            if( bFirst )
            {
                *pdfMinX = dfMinX;
                *pdfMaxX = dfMaxX;
                *pdfMinY = dfMinY;
                *pdfMaxY = dfMaxY;
                bFirst = FALSE;
            }
            else
            {
                *pdfMinX = MIN(dfMinX,*pdfMinX);
                *pdfMaxX = MAX(dfMaxX,*pdfMaxX);
                *pdfMinY = MIN(dfMinY,*pdfMinY);
                *pdfMaxY = MAX(dfMaxY,*pdfMaxY);
            }

            delete poRL;
        }
    }

    return !bFirst;
}