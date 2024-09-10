void PushButton::setTheme( Theme& t, const string prefix )
{
  beginUpdate();
	Widget::setTheme( t, prefix );
	setReleasedBorder( t.getBorder( prefix+"pushbutton_released" ) );
  setPressedBorder( t.getBorder( prefix+"pushbutton_pressed" ) );
  setFont( t.getFont( prefix+"pushbutton" ) );
  setFontColor( t.getColor( prefix+"pushbutton_font" ) );
  setImage( t.getImage( prefix+"pushbutton" ) );
	setCursor( t.getCursor( prefix+"pushbutton" ) );
  endUpdate();
}