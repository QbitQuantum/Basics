/** 
 * Handle global resource changes, such as scalable UI or skin events (override)
 */
void CNPRListBox::HandleResourceChange( TInt aType )
	{
	CCoeControl::HandleResourceChange( aType );
	SetRect( iAvkonViewAppUi->View( TUid::Uid( ENPRListBoxViewId ) )->ClientRect() );
	}