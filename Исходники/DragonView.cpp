BBitmap *DragonView::_MakeNoneImage( void )
{
	// Draw an "empty" bitmap to represent "no image"; we'll use one
	// that tells the user what to do.
	BBitmap *bitmap = new BBitmap( BRect( 0, 0, 319, 199 ),
								   BScreen().ColorSpace(),
								   true );
	BView *view = new BView( bitmap->Bounds(),
							 "not a bitmap",
							 B_FOLLOW_ALL_SIDES, 0 );
	bitmap->AddChild( view );

	DragonApp *app = dynamic_cast<DragonApp *>( be_app );
	
	rgb_color White = { 255, 255, 255, 0 };
	rgb_color Black = { 0, 0, 0, 0 };
	
	bitmap->Lock();

	view->SetLowColor( White );
	view->SetViewColor( White );
	view->SetHighColor( Black );
	view->SetDrawingMode( B_OP_OVER );
	view->FillRect( view->Bounds(), B_SOLID_LOW );

	// Excercise for the reader here:  Read the old newsletter articles
	// about how to use the font metrics to find out how large a font is,
	// then center to font in the window dynamically no matter what font
	// settings the user has.

	view->SetFont( be_plain_font );
	view->MovePenTo( 5, 100 );
	view->DrawString( app->rsrc_strings->FindString( RSRC_Drop_an_image ) );
	view->Sync();
	
	bitmap->Unlock();

	return bitmap;
}