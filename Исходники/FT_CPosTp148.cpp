 // ---------------------------------------------------------
// CPosTp148::PrintParsedDataFromEncoderL
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CPosTp148::PrintParsedDataFromEncoderL(
    const TDesC& aFile, 
    const TDesC8&  aBuffer, 
    TInt aExpectedStatusCode,
    const TDesC8& aMimeType)
    {
    iLog->Log(_L("===== PrintParsedDataFromEncoderL ======="));
    
    iLandmarkParser = CPosLandmarkParser::NewL(aMimeType);

    if (aFile != KNullDesC)
        {
        TFileName file( aFile );
        iLog->Log(_L("FILE (%S)"), &file );
        TraceL(_L("----->Using FILE<-------"));
        TraceL(file);
        iLandmarkParser->SetInputFileL(file);
        }
    else
        {
        iLog->Log(_L("BUFFER (size %d)"), aBuffer.Size() );
        TraceL(_L("----->Using BUFFER<-------"));
        iLandmarkParser->SetInputBuffer(aBuffer);
        }

    iOperation = iLandmarkParser->ParseContentL();
    TRequestStatus status = KPosLmOperationNotComplete;
    TReal32 progress;
    TInt number = 0;

    RArray<TPosLmItemId> array;
    CleanupClosePushL(array);

    while (status == KPosLmOperationNotComplete)
        {
        iLog->Log(_L("--- Parsing ---------------------------"));
        TraceL(_L("------------------------------"));
        iOperation->NextStep(status, progress);

        // Wait for NextStep to complete
        User::WaitForRequest(status);
        if (status != KPosLmOperationNotComplete && status != KErrNone)
            {
            iLog->Log(_L("Parsing Complete"));
            
            HBufC* buffer = HBufC::NewLC( 128);
            TPtr buf = buffer->Des();
                       
            buf.Format(_L("\tStatus %d"), status.Int());
            iLog->Log(buf);
            TraceL(buf);
            
            CleanupStack::PopAndDestroy( buffer );
            buffer = NULL;              
            }
        else
            {
            iLog->Log(_L("Parsing element"));
            
            if ( iLandmarkParser->NumOfParsedLandmarks() )
                {
                // Get last parsed landmark
                CPosLandmark* lm = iLandmarkParser->LandmarkLC();
                TPtrC lmName;
                TPtrC catName;
                lm->GetLandmarkName(lmName);
                lm->GetCategoriesL(array);
                //iLog->Log(lmName);
                for (TInt i=0;i<array.Count();i++)
                    {                    
                    CPosLandmarkCategory* category = iLandmarkParser->LandmarkCategoryLC( array[i] );
                    category->GetCategoryName( catName );
                     
                    HBufC* buffer = HBufC::NewLC( 128 + catName.Length());
                    TPtr buf = buffer->Des();
                                            
                    if ( category->GlobalCategory()) 
                        {
                        buf.Append(_L("\tGlobal category: "));    
                        }
                    else 
                        {
                        buf.Append(_L("\tLocal category: "));    
                        }                        
                                        
                    buf.Append( catName );
                    iLog->Log( buf );
                    TraceL( buf );

                    CleanupStack::PopAndDestroy( buffer );
                    buffer = NULL;
                                       
                    CleanupStack::PopAndDestroy(category);
                    }
                    
               	PrintLandmarkFieldsWithDescriptionL(*lm, ETrue);	
               
                
                number++;
                CleanupStack::PopAndDestroy(lm);
                }
            }
        }

    iLog->Log(_L("--- Parsing end ---------------------------"));
    TraceL(_L("------------------------------"));
    CleanupStack::PopAndDestroy(&array);

    if (status.Int() != aExpectedStatusCode)
        {
        HBufC* buffer = HBufC::NewLC( 128 );
        TPtr buf = buffer->Des();
                    
        buf.Format(_L("\tERROR: Wrong status returned, was %d, should be %d"), status.Int(), aExpectedStatusCode);
        iLog->Log( buf );
        iErrorsFound++;
        
        CleanupStack::PopAndDestroy( buffer );
        buffer = NULL;        
        }

    TUint32 nr = iLandmarkParser->NumOfParsedLandmarks();
    
    HBufC* buffer = HBufC::NewLC( 256 );
    TPtr buf = buffer->Des();
    
    buf.Format(_L("\tNr of Parsed landmarks %d, should be %d"), nr, number);
    iLog->Log(buf);
    TraceL(buf);

    CleanupStack::PopAndDestroy( buffer );
    buffer = NULL;
    
    if (nr != (TUint32)number)
        {
        iLog->Log(_L("\tERROR: Wrong number of landmarks parsed returned!"));
        iErrorsFound++;
        }

    TPosLmCollectionDataId lmId = iLandmarkParser->FirstCollectionDataId();

    iLog->Log(_L("--- CollectionData ---"));
    TraceL(_L("--- CollectionData ---"));

    if (lmId != EPosLmCollDataNone)
        {
        TPtrC first = iLandmarkParser->CollectionData(lmId);
        
        HBufC* buffer = HBufC::NewLC( first.Length() + 256 );
        TPtr buf = buffer->Des();
            
        buf.Zero();
        buf.Format(_L("\t(1)Collection Id: %d CollectionData: "), lmId);
        buf.Append(first);
        iLog->Log(buf);
        TraceL(buf);
        
        CleanupStack::PopAndDestroy( buffer );
        buffer = NULL;      
        
        }
    else 
        {
        iLog->Log(_L("\tNo collection data found 1"));    
        }

    while (lmId != EPosLmCollDataNone)
        {
        lmId = iLandmarkParser->NextCollectionDataId(lmId);
        if (lmId != EPosLmCollDataNone)
        {
            TPtrC first = iLandmarkParser->CollectionData(lmId);
            
            HBufC* buffer = HBufC::NewLC( first.Length() + 256 );
            TPtr buf = buffer->Des();         
            
            buf.Zero();
            buf.Format(_L("\t(2)Collection Id: %d CollectionData: "), lmId);
            buf.Append(first);
            iLog->Log(buf);
            TraceL(buf);
            
            CleanupStack::PopAndDestroy( buffer );
            buffer = NULL;              
        }
        else 
            {
            iLog->Log(_L("\tNo collection data found 2"));   
            }
        }

    iLog->Log(_L("--- CollectionData ---"));
    TraceL(_L("--- CollectionData ---"));

    delete iOperation;
    iOperation = NULL;
    delete iLandmarkParser;
    iLandmarkParser = NULL;
    iLog->Log(_L("====== PrintParsedDataFromEncoderL Done ========\n"));
    }