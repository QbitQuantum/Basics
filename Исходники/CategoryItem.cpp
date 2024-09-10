/*!
 *	\brief		Constructor.
 *	\details	Constructor from pointer to category.
 *	\param[in]	categoryIn	The category
 *	\param[in]	message		The message to be sent
 */
CategoryMenuItem::CategoryMenuItem( const Category *categoryIn,
									BMessage* message )
	:
	BMenuItem( "", message ),
	icon( NULL )
{
	if ( !categoryIn )
	{
		/* Received NULL instead of category - can't continue. */
		return;
	}
	BMenuItem::SetLabel( ( categoryIn->categoryName ).String() );
	currentColor = categoryIn->categoryColor;
	this->icon = CreateIcon( categoryIn->categoryColor, NULL );
	if ( !this->icon )
	{
		/* Panic! */
		exit(1);
	}	
}	// <-- end of constructor from pointer to Category.