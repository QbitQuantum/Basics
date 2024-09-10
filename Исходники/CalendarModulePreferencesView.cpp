/*!	
 *	\brief			Create box for selection of the weekend days
 *	\note			Additionally, select the color for weekends and weekdays
 *	\param[in]	frame	Enclosing rectangle.
 *	\param[in]	id		Reference to name of the selected Calendar module.
 *	\returns		Pointer to all-set-up BBox. Or NULL in case of error.
 */
BBox*	CalendarModulePreferencesView::CreateWeekendSelectionBox( BRect frame,
															  const BString &id )
{
	/*!	\par	Notes on implementation:
	 *			It's not all that straightforward - to create this selection box.
	 *			The problem is that number of days in week is dependent on the
	 *			Calendar Module, therefore the frame rectangle must be divided
	 *			properly. We should take into account the possibility that there's
	 *			not enough place for all days in the submitted frame.
	 *
	 *	\par	
	 *			The solution will be as follows:
	 *			Let number of days in week be N. I create two columns and 
	 *			several rows (the number depends on N). Days in week will be
	 *			proceeded in the order <em>as Calendar Module supplies them</em>.
	 *			The days occupy both columns, and are located in rows
	 *			[0, (ceiling of (N/2)) ). Days returned from CalendarModule are
	 *			placed as follows: days from 0 to (ceiling of (N/2)-1) in the left
	 *			column, days from (ceiling of (N/2)-1) to (N-1) in right column.
	 *
	 *	\par	
	 *			There will be an empty cell in the right column, if number
	 *			of days in week is odd, (which is usually the case).
	 */
	frame.InsetBySelf( 5, 0 );
	BMessage* 	toSend = NULL;
	BCheckBox* 	dayCheckBox = NULL;
	BString		tempString;
	BLayoutItem*	layoutItem = NULL;
	CalendarModulePreferences* prefs = NULL;
	CalendarModule*	calModule = NULL;
	int height = 0;		//!< this is used to resize the BBox to proper size
	
	calModule = utl_FindCalendarModule( id );
	if ( calModule == NULL ) {
		/* Error */
		utl_Deb = new DebuggerPrintout( "Did not succeed to find the calendar module." );
		return NULL;
	}
	// Get the data on days of week
	uint32 daysInWeek = ( uint32 )( calModule->GetDaysInWeek() );
	map<uint32, DoubleNames> weekdayNames = calModule->GetWeekdayNames();

	
	/* Obtain the current Calendar Module preferences */
	prefs = pref_GetPreferencesForCalendarModule( id );
	if ( !prefs ) {
		utl_Deb = new DebuggerPrintout( "Did not succeed to find the preferences for the calendar module." );
		return NULL;
	}
	
	// At this point, "pref" points to current preferences of this calendar module.
	
	BList* weekends = prefs->GetWeekends();		// Get info on currently selected weekends
	
	// Prepare the item to be returned
	BBox*	enclosingBox = new BBox( frame, "Weekend selector" );
	if ( !enclosingBox )
	{
		/* Panic! */
		exit(1);
	}
	enclosingBox->SetLabel( "Select the non-working days (weekends)" );

	// Prepare the layout to be used
	BGridLayout* layout = new BGridLayout();
	if ( !layout)
	{
		/* Panic! */
		exit(1);
	}	
	enclosingBox->SetLayout( layout );
	layout->SetInsets( 10, 15, 10, 5 );
	layout->SetVerticalSpacing( 1 );
	
	/* indexX is 0 for left column or 1 for right column.
	 * indexY is 0 for topmost row, 1 for second from top row, etc.
	 * Max value for indexY = (ceiling of (N/2)).
	 */
	int indexX = 0, indexY = 0;
	
	for (uint32 day = prefs->GetFirstDayOfWeek(), i = 0; i < ( uint32 )daysInWeek; ++i )
	{
		/* Creating the message to be sent */
		toSend = new BMessage( kCalendarModuleWeekendDaySelected );
		if ( !toSend )
		{
			/* Panic! */
			exit(1);
		}
		toSend->AddInt32( "Weekday const", day );
		toSend->AddString( "Calendar module", id );

		/* Set the name of the checkbox.
		 * This is used to identify if the checkbox was checked or unchecked.
		 */
		tempString.SetTo( "Weekday" );
		tempString << day;
		
		/* Creating the checkbox */
		dayCheckBox = new BCheckBox( BRect(0, 0, 1, 1),
									 tempString.String(),
									 weekdayNames[ day ].longName.String(),
									 toSend );
		if (!dayCheckBox)
		{
			// Panic!
			exit(1);
		}
		dayCheckBox->ResizeToPreferred();
		
		// Check if the checkbox should be checked
		if ( weekends->HasItem( ( void* )day ) ) {
			dayCheckBox->SetValue( 1 );
		} else {
			dayCheckBox->SetValue( 0 );
		}
		
		/* Adding the item to the BBox */
		layoutItem = layout->AddView( dayCheckBox, indexX, indexY );
		if ( layoutItem )
		{
			layoutItem->SetExplicitAlignment( BAlignment( B_ALIGN_LEFT, B_ALIGN_TOP ) );
//			layoutItem->SetExplicitMaxSize( BSize( (int )dayCheckBox->Bounds().Width(), (int )dayCheckBox->Bounds().Height() ) );
			layout->SetMaxRowHeight( indexY, (int )dayCheckBox->Bounds().Height() + 10 );
			layout->SetRowWeight( indexY, 0 );
		}
		
		/* Advancing to the next cell in grid */
		// If arrived to the last item in the first column, advancing to second
		// The +1 is needed because i starts from 0, but days are starting from 1
		if ( ( i + 1 ) == ( unsigned int )( ( daysInWeek + 1 ) / 2 ) )
		{
			indexX = 1;	
			indexY = 0;
		}
		else 	// Staying in the same column, but advancing down
		{
			++indexY;	
		}
		
		/* Advancing to the next day */
		( day == daysInWeek ) ? day = kSunday : ++day;
		
	}	// <-- end of "for (all days in week)"
	
	// Resizing the BBox to the correct size.
	// Note: dayCheckBox is surely not NULL; if it were, we would exit earlier.
	height =(int )( ( dayCheckBox->Bounds().Height() + 5           ) * ( int )( ( daysInWeek + 1 ) / 2 ) - 5 );
	// Formula:	    ( ^height of one checkbox^       + ^separator^ ) * ( ^number of days in column^      ) - ^one unneeded extra separator^
	
	enclosingBox->ResizeTo( enclosingBox->Bounds().Width() - 10, ( int )height );
//	layout->SetExplicitMaxSize( BSize( enclosingBox->Bounds().Width() - 5, ( int )height + 25 ) );
	
	return enclosingBox;
}