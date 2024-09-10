static Boolean DoDITLTextButton( short message, DITLItem *theItem, short keyPress )
{
Boolean	done;
TextButtGraphicsPriv * state;

	done = false;
	switch ( message )
	{
		case kInitDITLElement:
			theItem->refCon = 0;
			state = NewMemory ( false, sizeof(TextButtGraphicsPriv) );
			if ( state )
			{
				theItem->refCon = (long) state;
				state->textSprite = 0;
				state->buttReference = nil;
				state->animatorProc = nil;
				state->buttonID = 0;
				state->currentFrame = 0;
				state->toKeepDictCached = nil;
			}
			break;
			
		case kRenderDITLElement:
			RenderDITLTextButton( theItem );		
			break;
				
		case kSelectDITLElement:
			SelectDITLTextButton( theItem );
			break;
			
		case kDeselectDITLElement:
			DeselectDITLTextButton( theItem );
			break;
			
		case kClickDITLElement:
			done = ClickDITLTextButton( theItem, keyPress );
			break;
			
		case kCloseDITLElement:
			state = (TextButtGraphicsPriv *) theItem->refCon;
			if ( state )
			{
				if (state->animatorProc)
				{
					RemoveTimeRequest( state->animatorProc );
					state->animatorProc = nil;
				}

				if ( state->textSprite )
				{
					DisposeSprite ( state->textSprite );
				}
				
				if ( state->buttReference )
				{
					DisposeGraphicReference ( state->buttReference );	
				}
				
				if ( state->toKeepDictCached )
				{
					Decompressor dec = CreateDecompressor(
						GetDBButtonFrame( state->buttonID, kAnimationFrames ), 0, 0 );

					ReleaseDecompressorCache( dec, state->toKeepDictCached );
					DisposeDecompressor( dec );
				}
				
				DisposeMemory (state );
			}
			break;
			
		default:
			ERROR_MESG( "Got an illegal selector in DoDITLTextButton" );
			
	}
		
	return done;
}