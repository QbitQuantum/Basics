	void TextBox::handleLayout(LayoutEngine& eng, const Dimensions& containing)
	{
		// TextBox's have no children to deal with, by definition.	
		// XXX fix the point() to be the actual last point, say from LayoutEngine
		point cursor = reflowText(eng, containing, eng.getCursor());
		eng.setCursor(cursor);

		calculateHorzMPB(containing.content_.width);
		calculateVertMPB(containing.content_.height);
	}