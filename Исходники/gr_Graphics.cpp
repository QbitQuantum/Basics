bool GR_Graphics::itemize(UT_TextIterator & text, GR_Itemization & I)
{
	UT_return_val_if_fail(text.getStatus() == UTIter_OK, false);
	
	I.clear();
	UT_uint32 iCurOffset = 0, iLastOffset = 0;
	UT_uint32 iPosStart = text.getPosition();

	// the main loop that will span the whole text of the iterator
	while(text.getStatus() == UTIter_OK)
	{
		UT_BidiCharType iPrevType, iLastStrongType = UT_BIDI_UNSET, iType;
		
		UT_UCS4Char c = text.getChar();
		
		UT_return_val_if_fail(text.getStatus() == UTIter_OK, false);

		iType = UT_bidiGetCharType(c);
#if 0
		// this branch of code breaks at all direction bounaries
		// it is disabled because doing that causes bug 8099
		iCurOffset = iLastOffset = text.getPosition();
		++text;
		
		// this loop will cover a single homogenous item
		while(text.getStatus() == UTIter_OK)
		{
			iPrevType = iType;

			c = text.getChar();
			UT_return_val_if_fail(text.getStatus() == UTIter_OK, false);

			// remember the offset
			iLastOffset = text.getPosition();
			
			iType = UT_bidiGetCharType(c);
			if(iType != iPrevType)
			{
				break;
			}

			++text;
		}
#else
		//we have to break the text into chunks that each will go into a
		//separate run in a manner that will ensure that the text will
		//be correctly processed later. The most obvious way is to
		//break every time we encounter a change of directional
		//properties. Unfortunately that means breaking at each white
		//space, which adds a huge amount of processing due to
		//allocating and deleting runs when loading a
		//document. The following code tries to catch out the obvious
		//cases when the span can remain intact. Tomas, Jan 28, 2003

		// remember where we are ...
		iCurOffset = iLastOffset = text.getPosition();
		++text;

		UT_BidiCharType iNextType;
		
		// this loop will cover a single homogenous item
		while(text.getStatus() == UTIter_OK)
		{
			iPrevType = iType;
			if(UT_BIDI_IS_STRONG(iType))
				iLastStrongType = iType;
			
			c = text.getChar();
			UT_return_val_if_fail(text.getStatus() == UTIter_OK, false);

			// remember the offset
			iLastOffset = text.getPosition();
			++text;
			
			iType = UT_bidiGetCharType(c);
			if(iType != iPrevType)
			{
				// potential direction boundary see if we can ignore
				// it
				bool bIgnore = false;
#if 0
				// this assumption is not true; for instance in the
				// sequence ") " the parenthesis and the space can
				// resolve to different directions
				// 
				// I am leaving it here so that I do not add it one
				// day again (Tomas, Apr 10, 2003)
				
				if(UT_BIDI_IS_NEUTRAL(iPrevType) && UT_BIDI_IS_NEUTRAL(iType))
				{
					// two neutral characters in a row will have the same
					// direction
					xxx_UT_DEBUGMSG(("GR_Graphics::itemize: ntrl->ntrl (c=0x%04x)\n",c));
					bIgnore = true;
				}
				else
#endif
				if(UT_BIDI_IS_STRONG(iPrevType) && UT_BIDI_IS_NEUTRAL(iType))
				{
					// we can ignore a neutral character following a
					// strong one if it is followed by a strong
					// character of identical type to the previous one
					xxx_UT_DEBUGMSG(("GR_Graphics::itemize: strong->ntrl (c=0x%04x)\n",c));
					
					// take a peek at what follows
					UT_uint32 iOldPos = text.getPosition();
					
					while(text.getStatus() == UTIter_OK)
					{
						UT_UCS4Char c2 = text.getChar();
						UT_return_val_if_fail(text.getStatus() == UTIter_OK, false);

						++text;
						
						iNextType = UT_bidiGetCharType(c2);
						xxx_UT_DEBUGMSG(("GR_Graphics::itemize: iNextType 0x%04x\n", iNextType));
						
						if(iNextType == iPrevType)
						{
							bIgnore = true;
							break;
						}

						// if the next character is strong, we cannot
						// ignore the boundary
						if(UT_BIDI_IS_STRONG(iNextType))
							break;
					}

					// restore position
					text.setPosition(iOldPos);
				}
				else if(UT_BIDI_IS_NEUTRAL(iPrevType) && UT_BIDI_IS_STRONG(iType))
				{
					// a neutral character followed by a strong one -- we
					// can ignore it, if the neutral character was
					// preceeded by a strong character of the same
					// type
					if(iType == iLastStrongType)
					{
						bIgnore = true;
					}
					xxx_UT_DEBUGMSG(("GR_Graphics::itemize: ntrl->strong (c=0x%04x)\n",c));
				}
				else
				{
					// in all other cases we will split
					xxx_UT_DEBUGMSG(("GR_Graphics::itemize: other (c=0x%04x)\n",pSpan[i]));
				}

				xxx_UT_DEBUGMSG(("GR_Graphics::itemize: bIgnore %d\n",static_cast<UT_uint32>(bIgnore)));
				if(!bIgnore)
					break;
			}
			
		}
#endif
		
		I.addItem(iCurOffset - iPosStart, new GR_XPItem(GRScriptType_Undefined));
	}

	// add an extra record of type Void to allow for calculation of
	// length of the last item
	// iLastOffset is the offset of the last valid character; the Void
	// offset is one beyond that
	I.addItem(iLastOffset - iPosStart + 1, new GR_XPItem(GRScriptType_Void));
	return true;
}