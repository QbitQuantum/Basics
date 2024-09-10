void MenuBook::loadBook() {
	if (book_loaded) return;

	// Read data from config file
	FileParser infile;

	// @CLASS MenuBook|Description of books in books/
	if (infile.open(book_name)) {
		while (infile.next()) {
			if (parseMenuKey(infile.key, infile.val))
				continue;

			infile.val = infile.val + ',';

			// @ATTR close|x (integer), y (integer)|Position of the close button.
			if(infile.key == "close") {
				closeButton->pos.x = popFirstInt(infile.val);
				closeButton->pos.y = popFirstInt(infile.val);
			}
			// @ATTR background|string|Filename for the background image.
			else if (infile.key == "background") {
				setBackground(popFirstString(infile.val));
			}
			else if (infile.section == "") {
				infile.error("MenuBook: '%s' is not a valid key.", infile.key.c_str());
			}

			if (infile.new_section) {

				// for sections that are stored in collections, add a new object here
				if (infile.section == "text") {
					text.push_back(NULL);
					textData.push_back("");
					textColor.push_back(Color());
					justify.push_back(0);
					textFont.push_back("");
					size.push_back(Rect());
				}
				else if (infile.section == "image") {
					image.push_back(NULL);
					image_dest.push_back(Point());
				}

			}
			if (infile.section == "text")
				loadText(infile);
			else if (infile.section == "image")
				loadImage(infile);
		}

		infile.close();
	}

	// setup image dest
	for (unsigned i=0; i < image.size(); i++) {
	       image[i]->setDest(image_dest[i]);
	}

	// render text to surface
	for (unsigned i=0; i<text.size(); i++) {
		font->setFont(textFont[i]);
		Point pSize = font->calc_size(textData[i], size[i].w);
		Image *graphics = render_device->createImage(size[i].w, pSize.y);

		if (justify[i] == JUSTIFY_CENTER)
			font->render(textData[i], size[i].w/2, 0, justify[i], graphics, size[i].w, textColor[i]);
		else if (justify[i] == JUSTIFY_RIGHT)
			font->render(textData[i], size[i].w, 0, justify[i], graphics, size[i].w, textColor[i]);
		else
			font->render(textData[i], 0, 0, justify[i], graphics, size[i].w, textColor[i]);
		text[i] = graphics->createSprite();
		graphics->unref();
	}

	align();
	alignElements();

	book_loaded = true;
}