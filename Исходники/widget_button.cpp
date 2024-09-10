void TextButton::draw(Canvas& can) {
	SDL_Rect contentBounds;
	contentBounds.x = style->outlineSz;
	contentBounds.y = style->outlineSz;
	contentBounds.w = bounds.w - (style->outlineSz * 2);
	contentBounds.h = bounds.h - (style->outlineSz * 2);
	can.setColor(style->colOutline);
	can.fillRect(0, 0, bounds.w, bounds.h);
	can.setRelViewport(contentBounds);
	can.setColor(select(*style, state));
	can.fillRect(0, 0, contentBounds.w, contentBounds.h);
	if (test()) {
		can.draw(tex, &texBounds);
#if defined(DEBUG_TEXTBUTTON_DRAWTEXTURE) && DEBUG_TEXTBUTTON_DRAWTEXTURE
		auto oldColor = can.getColorState();
		can.setColor(DEBUG_TEXTBUTTON_DRAWTEXTURE_COLOR, getAlpha<DEBUG_TEXTBUTTON_DRAWTEXTURE_ALPHA>());
		can.fillRect(texBounds);
		can.setColorState(oldColor);
#endif // DEBUG_TEXTBUTTON_DRAWTEXTURE
	}
	can.clearViewport();
}