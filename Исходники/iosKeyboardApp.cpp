// manually build a string of numerical digits, filtering out everything else
void iosKeyboardApp::processNumerical( const KeyEvent &event )
{
	if( event.getCode() == KeyEvent::KEY_BACKSPACE && ! mNumericalTextView.mText.empty() )
		mNumericalTextView.mText.pop_back();
	else if( isdigit( event.getChar() ) ) {
		mNumericalTextView.mText.push_back( event.getChar() );
		Rectf fitRect = mNumericalTextView.getTextBounds();
		TextBox tbox = TextBox().font( mFont ).text( mNumericalTextView.mText ).size( TextBox::GROW, TextBox::GROW );
		vec2 size = tbox.measure();

		if( size.x > fitRect.getWidth() ) {
			console() << "OVERFLOW" << endl;
			mNumericalTextView.mText.pop_back();
		}
	}
}