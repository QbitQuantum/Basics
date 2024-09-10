CFbsBitmap* AknBitmapMirrorUtils::CreateBitmapOptimizedL(CFbsBitmap* aSourceBitmap, TInt aMirrorDirection)
    {
    // Check if displaymode is optimized, fallback to non-optimized version if not.
    TBool fallback = ETrue;
    TDisplayMode displayMode = aSourceBitmap->DisplayMode();
    switch( displayMode )
        {
        case EGray256:
        case EColor256:
        case EColor4K:
        case EColor64K:
            fallback = EFalse;
            break;
        default:
            fallback = ETrue;
        }

    // Check if mirroring mode is supported, fallback to non-optimized version if not.
	if ((aMirrorDirection != EAknVerticalMirroring) && (aMirrorDirection != EAknHorizontalMirroring))
		{
		fallback = ETrue;	
		}

    if( fallback )
		return CreateBitmapL(aSourceBitmap, aMirrorDirection);
    
	// Prepare destination bitmap
    User::LeaveIfNull(aSourceBitmap);
    CFbsBitmap* destinationBitmap = new (ELeave) CFbsBitmap();
    CleanupStack::PushL(destinationBitmap);   

    TSize sourceBitmapSize = aSourceBitmap->SizeInPixels();            
    TRect sourceRect = TRect(TPoint(0,0), sourceBitmapSize);
    TSize destinationBitmapSize(sourceRect.Width(), sourceRect.Height()); 

    User::LeaveIfError(destinationBitmap->Create(destinationBitmapSize, aSourceBitmap->DisplayMode()));

	// Check source, if rom bitmap or compressed then create uncompressed ram bitmap
    TBool srcTemporary = EFalse;
    if( aSourceBitmap->IsRomBitmap() )
        {
        srcTemporary = ETrue;
        }
        
    // Heap lock for FBServ large chunk to prevent background
    // compression of aSrcBitmap after if IsCompressedInRAM returns EFalse
    aSourceBitmap->LockHeapLC( ETrue ); // fbsheaplock
    TBool fbsHeapLock = ETrue;        
        
    if( aSourceBitmap->IsCompressedInRAM() )
        {
        srcTemporary = ETrue;
        }
    if( aSourceBitmap->ExtendedBitmapType() != KNullUid  )
        {
        srcTemporary = ETrue;
        }

    CFbsBitmap* realSource = aSourceBitmap;
    if( srcTemporary )
        {
        CleanupStack::PopAndDestroy(); // fbsheaplock
        fbsHeapLock = EFalse;
        
        realSource = new (ELeave) CFbsBitmap();
        CleanupStack::PushL( realSource );
        User::LeaveIfError( realSource->Create( sourceBitmapSize, aSourceBitmap->DisplayMode() ) );
        CFbsBitmapDevice* dev = CFbsBitmapDevice::NewL( realSource );
        CleanupStack::PushL( dev );
        CFbsBitGc* gc = NULL;
        User::LeaveIfError( dev->CreateContext( gc ) );
        CleanupStack::PushL( gc );
        gc->BitBlt( TPoint(0,0), aSourceBitmap );
        CleanupStack::PopAndDestroy(2); // dev, gc
        }

	// Heap lock for FBServ large chunk is only needed with large bitmaps.
    if (!fbsHeapLock)
    	{
	    if ( realSource->IsLargeBitmap() || destinationBitmap->IsLargeBitmap() )
	        {
	        destinationBitmap->LockHeapLC( ETrue ); // fbsheaplock
	        }
	    else
	        {
	        CleanupStack::PushL( (TAny*)NULL );
	        }
    	}

    TUint32* srcAddress = realSource->DataAddress();
    TUint32* trgAddress = destinationBitmap->DataAddress();

    if ( displayMode == EColor4K || displayMode == EColor64K )
        {
        TInt srcScanLen16 = CFbsBitmap::ScanLineLength(sourceBitmapSize.iWidth, displayMode) / 2;
        TInt trgScanLen16 = CFbsBitmap::ScanLineLength(destinationBitmapSize.iWidth, displayMode) / 2;
        TInt srcScanLen32 = CFbsBitmap::ScanLineLength(sourceBitmapSize.iWidth, displayMode) / 4;
        TInt trgScanLen32 = CFbsBitmap::ScanLineLength(destinationBitmapSize.iWidth, displayMode) / 4;

	    switch (aMirrorDirection)
	        {
	        case EAknVerticalMirroring:
	            {
		        TUint32* trgAddress32 = trgAddress;
	            TUint32* srcAddress32 = srcAddress;            	
           		TInt trgPos = 0;
            	for ( TInt yPos=destinationBitmapSize.iHeight-1; yPos >= 0; yPos-- )
            		{
		            srcAddress32 = srcAddress + srcScanLen32*yPos;
            		trgAddress32 = trgAddress + trgScanLen32*trgPos;            			
            		memcpy(trgAddress32, srcAddress32, srcScanLen32*4);
            		trgPos++;
            		}
	            break;
	            }
	        case EAknHorizontalMirroring:
	            {
		        TUint16* trgAddress16 = reinterpret_cast<TUint16*>(trgAddress);
	            TUint16* srcAddress16 = reinterpret_cast<TUint16*>(srcAddress);            	
           		TInt xTrgPos = 0;
            	for ( TInt yPos=destinationBitmapSize.iHeight-1; yPos >= 0; yPos-- )
            		{
	           		xTrgPos = 0;            		            		
	            	for ( TInt xPos=destinationBitmapSize.iWidth-1; xPos >= 0; xPos-- )
	            		{
						trgAddress16[xTrgPos] = srcAddress16[xPos];
						xTrgPos++;
	            		}
            		srcAddress16 += srcScanLen16;
	            	trgAddress16 += trgScanLen16;	            		
            		}
	            
	            break;
	            }
	        default:
	            {
	            break;
	            }
	        }
        }
	else if( (displayMode==EGray256) || (displayMode==EColor256) )
        {
        TInt srcScanLen8 = CFbsBitmap::ScanLineLength(sourceBitmapSize.iWidth, displayMode);
        TInt trgScanLen8 = CFbsBitmap::ScanLineLength(destinationBitmapSize.iWidth, displayMode);
        TInt srcScanLen32 = CFbsBitmap::ScanLineLength(sourceBitmapSize.iWidth, displayMode) / 4;
        TInt trgScanLen32 = CFbsBitmap::ScanLineLength(destinationBitmapSize.iWidth, displayMode) / 4;
                
	    switch (aMirrorDirection)
	        {
	        case EAknVerticalMirroring:
	            {
		        TUint32* trgAddress32 = trgAddress;
	            TUint32* srcAddress32 = srcAddress;            	
           		TInt trgPos = 0;
            	for ( TInt yPos=destinationBitmapSize.iHeight-1; yPos >= 0; yPos-- )
            		{
		            srcAddress32 = srcAddress + srcScanLen32*yPos;
            		trgAddress32 = trgAddress + trgScanLen32*trgPos;            			
            		memcpy(trgAddress32, srcAddress32, srcScanLen32*4);
            		trgPos++;
            		}
	            break;
	            }
	        case EAknHorizontalMirroring:
	            {
		        TUint8* trgAddress8 = reinterpret_cast<TUint8*>(trgAddress);
	            TUint8* srcAddress8 = reinterpret_cast<TUint8*>(srcAddress);            	
           		TInt xTrgPos = 0;
            	for ( TInt yPos=destinationBitmapSize.iHeight-1; yPos >= 0; yPos-- )
            		{
	           		xTrgPos = 0;            		            		
	            	for ( TInt xPos=destinationBitmapSize.iWidth-1; xPos >= 0; xPos-- )
	            		{
						trgAddress8[xTrgPos] = srcAddress8[xPos];
						xTrgPos++;
	            		}
            		srcAddress8 += srcScanLen8;
	            	trgAddress8 += trgScanLen8;	            			            
            		}
	            break;
	            }
	        default:
	            {
	            break;
	            }        	            
	        }
        }

	CleanupStack::PopAndDestroy(); // fbsheaplock

    if( srcTemporary )
        {
        CleanupStack::PopAndDestroy(); // realSource
        }

    CleanupStack::Pop(); // destinationBitmap
    return destinationBitmap;   
    }