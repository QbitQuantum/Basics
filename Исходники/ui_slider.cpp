void Slider::Draw( int relx, int rely ){
	int x, y;

	x = GetX() + relx;
	y = GetY() + rely;

	int markerx_pix = ValToPixel( val );
	
	// Draw slider background
	left->Draw( x, y );
	background->DrawTiled( x + left->GetWidth(), y, w - left->GetWidth() - right->GetWidth(), background->GetHeight() );
	right->Draw( x + w - right->GetWidth(), y );

	// Draw the Bar
	bar->DrawTiled( x + left->GetWidth(),
	                y + background->GetHalfHeight() - bar->GetHalfHeight(),
	                markerx_pix, bar->GetHeight() );

	// Draw marker
	handle->Draw( x + markerx_pix - handle->GetHalfWidth(),
	              y + background->GetHalfHeight() - handle->GetHalfHeight() );

	// Render the value indicator
	char value[20] = {0};
	snprintf(value, 20, "%.2f", this->val);
	UI::font->Render( x + markerx_pix, y - 3, value, Font::CENTER, Font::BOTTOM );

	UI::font->RenderTight( x + GetW() + 5, y, name );

	Widget::Draw(relx, rely);
}