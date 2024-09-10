/**
* Places the dialog items according to the current visible window position.
* When hiding items, uses SetExtent() instead of just SetPosition() in order to call
* SizeChanged() of the moved item. For example, this is needed for the editor to
* change its cursor accordingly.
*
* @param aRect Rectangle of the form window
* @param aTop Number of items above the window
* @param aMiddle Number of items inside the window
* @param aBottom Number of items below the window
*
* Parameter value equal to -1 means that the parameter is not defined and will be
* calculated automatically. Normally, either the top number or the bottom one
* is only defined. If @a aTop is defined, the items will be placed from top downwards, leaving
* @a aTop items above the window. If @a aBottom is defined, the items will be placed from bottom
* upwards, leaving @a aBottom items below the window.
*
* This function panics, if neither @a aTop nor @a aBottom are defined.
*
* The function first checks if the provided @a aTop and @a aBottom are consistent with
* the item sizes and the given window rectangle. If they are not, they will be
* corrected. Usually, @a aTop and @a aBottom come out of sync with the item sizes
* after the dynamic layout change.
*/
void CEikCapCArray::SetRect(const TRect& aRect, TInt aTop, TInt /*aMiddle*/, TInt aBottom)
{
    TAknLayoutRect formtLayoutRect;
    formtLayoutRect.LayoutRect(aRect, AknLayoutScalable_Avkon::listscroll_form_pane().LayoutLine());
    formtLayoutRect.LayoutRect(formtLayoutRect.Rect(), AknLayoutScalable_Avkon::list_form_gen_pane().LayoutLine());
    TRect formRect = formtLayoutRect.Rect();

    CEikCapCArrayExtension *extension_or_null = ExtensionOrNull();
    if (extension_or_null)
    {
        extension_or_null->iRect = formRect;
    }

    // controls need to be placed in real locations if physics is enabled
    if ( Count() > 0 )
    {
        CEikCaptionedControl* control = (*this)[0];

        if ( control->DialogPage()->IsForm() )
        {
            SetRealRect( aRect, aTop, aBottom );
            return;
        }
    }

    TBool topDefined = EFalse;   // top or bottom number defined?
    if( aTop > -1 )
    {
        topDefined = ETrue;
    }
    else if( aBottom > -1 )
    {
        topDefined = EFalse;
    }
    else    // aBottom == aTop == -1
    {
        User::Panic( _L("CEikCapCArray::SetRect(): Neither top nor bottom items number defined"), EAknPanicInvalidValue );
    }
    const TInt count = Count();
    const TInt rectHeight = aRect.Height();
    /**
    * Special invisible points are used for placing the items that are
    * outside the window. CCoeControl's invisible flag cannot be used,
    * as it is controlled by third-party applications.
    */
    const TPoint topInvisPoint( -10000, -10000 );
    const TPoint bottomInvisPoint( 10000, 10000 );

    CEikCaptionedControl *firstCapCC = count > 0 ? (*this)[0] : NULL;
    if( firstCapCC && firstCapCC->iIsFormControl )  // Forms
    {
        CEikCaptionedControl *selectedLine( NULL );
        if( firstCapCC->DialogPage())
            selectedLine = firstCapCC->DialogPage()->CurrentLine();

        // Check height of items and the input parameters aTop and aBottom.
        TInt rest = 0;  // number of the rest items without aTop or aBottom
        TInt index = 0;
        if( topDefined )
        {
            rest = count - aTop;
            index = aTop;
        }
        else
        {
            rest = count - aBottom;
            index = rest - 1;
        }
        TInt height = 0;
        for( TInt ii = 0; ii < rest; ii++ )
        {
            CEikCaptionedControl* line = (*this)[index];
            height += line->MinimumSize().iHeight;  // Use MinimumSize() here as a protection from dynamic layout change
            if( height >= rectHeight )
                break;  // Input params are OK
            topDefined? index++ : index--;
        }
        /**
        * If the window contains too few items inside and there are still items outside,
        * correct the input parameters @a aTop and @a aBottom to fill up the window.
        */
        if( height < rectHeight )
        {
            if( topDefined && aTop > 0 )    // For top-down placement and there are items above the window
            {
                // Calculate height of controls above the window also
                for( TInt ii = 0; ii < aTop; ii++ )
                {
                    CEikCaptionedControl* line = (*this)[ii];
                    height += line->MinimumSize().iHeight;
                    if( height >= rectHeight )  // All items don't fit to the window anyway
                    {
                        topDefined = EFalse;   // Reverse direction to bottom-up
                        aBottom = 0;
                        break;
                    }
                }
                if( height < rectHeight )  // All items fit to the window
                {
                    aTop = 0; // Just place them from the first item
                }
            }
            else if( !topDefined )  // For bottom-up placement
            {
                topDefined = ETrue;   // Reverse direction to top-down
                aTop = 0;
            }
        }

        // Hiding items that are explicitly defined to be outside the window
        TInt start;
        TInt end;
        TPoint invisPoint;    // current invisible point, depends on placement direction
        if( topDefined )
        {
            start = 0;
            end = aTop;
            invisPoint = topInvisPoint;
        }
        else
        {
            start = count - aBottom;
            end = count;
            invisPoint = bottomInvisPoint;
        }
        for( TInt ii = start; ii < end; ii++ )
        {
            CEikCaptionedControl* line = (*this)[ii];
            line->SetPosition( invisPoint );
        }

        // Setting rects for the rest of the items
        if( topDefined )
        {
            rest = count - aTop;
            invisPoint = bottomInvisPoint;
            index = aTop;
        }
        else
        {
            rest = count - aBottom;
            invisPoint = topInvisPoint;
            index = rest - 1;
        }
        TInt reservedHeight = 0; // in pixels
        TBool insideWindow = ETrue; // The current item is still inside the window
        TInt topY = 0;


        for( TInt ii = 0; ii < rest; ii++ )
        {
            CEikCaptionedControl* line = (*this)[index];
            TSize lineSize( line->Size() );
            if( insideWindow )
            {
                ResetHides( line );
                if( topDefined )
                {   // Top-down placement
                    topY = aRect.iTl.iY + reservedHeight;
                }
                else
                {   // Bottom-up placement
                    topY = aRect.iBr.iY - reservedHeight - lineSize.iHeight;
                }
                line->SetExtent( TPoint( formRect.iTl.iX, topY ), lineSize );
                AknsUtils::RegisterControlPosition( line );
                AknsUtils::RegisterControlPosition( line->iCaption );
                AknsUtils::RegisterControlPosition( line->iControl );
                AknsUtils::RegisterControlPosition( line->iTrailer );
                AknsUtils::RegisterControlPosition( line->iBitmap );
                reservedHeight += lineSize.iHeight;
                /**
                * The control at a window edge is considered as partially-visible.
                * Its subcontrols must be checked for visibility individually.
                */
                if( reservedHeight > rectHeight )
                {
                    TInt visibleSubctrls = HideLines( line, aRect );    // Check how many subcontrols stayed visible
                    insideWindow = EFalse;
                    /**
                    * For the bottom-up placement:
                    * if the window contains only an empty "partially-visible" control and a
                    * a selected popup field, make the popup to hang at the top alone.
                    */
                    if( !topDefined && index < count - 1 ) // bottom-up and not last
                    {
                        CEikCaptionedControl* lineBelow = (*this)[index+1];
                        if( visibleSubctrls == 0 && ii == 1 &&
                                IsPopupField( lineBelow ) && lineBelow == selectedLine )
                        {
                            TRect popupRect( lineBelow->Rect() );
                            TInt diff = aRect.iTl.iY - popupRect.iTl.iY; // negative
                            popupRect.Move( 0, diff );
                            lineBelow->SetRect( popupRect );
                        }
                    }
                }
            }
            else
            {
                line->SetPosition( invisPoint );
            }
            topDefined? index++ : index--;
        }
    }
    else    // Dialogs other than forms:
    {
        TRect rect=aRect;
        const TInt fullWidth=rect.iBr.iX-rect.iTl.iX;
        const TInt count=Count();
        const TInt topMargin=iDensePacking ? KAknNoTopMargin : KAknTopMargin;
        const TInt verticalSpacing=iDensePacking ? KVerticalSpacingSquash : KVerticalSpacing;
        rect.iTl.iY+=topMargin;
        TInt deltaHeight=0;
        for (TInt ii=0; ii<count; ++ii)
        {
            CEikCaptionedControl* line=(*this)[ii];
            TSize thisSize=line->MinimumSize();
            TInt thisDeltaHeight=thisSize.iHeight+verticalSpacing;
            if (deltaHeight<thisDeltaHeight)
                deltaHeight=thisDeltaHeight;
            if (!(line->iCaptionWidth))
                thisSize.iWidth=fullWidth;
            else
            {
                CEikCapCArrayExtension *ext = ExtensionOrNull();
                TInt deltaWidth = 0;
                if (ext)
                    deltaWidth = ext->iCaptionWidth-line->iCaptionWidth;
                thisSize.iWidth+=deltaWidth;
                if (ext)
                    line->iCaptionWidth=ext->iCaptionWidth;
                else
                    line->iCaptionWidth = 0;
                line->iMinSize.iWidth+=deltaWidth;
            }
            line->iFullWidth=fullWidth;
            line->SetExtent(rect.iTl,thisSize);
            if (!(line->LatentGroupLineFollows()))
            {
                rect.iTl.iY+=deltaHeight;
                deltaHeight=0;
            }
        }
    }
}