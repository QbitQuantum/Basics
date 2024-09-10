void
WonderBrushView::AttachedToWindow()
{
	// Hack for DataTranslations which doesn't resize visible area to requested by view
	// which makes some parts of bigger than usual translationviews out of visible area
	// so if it was loaded to DataTranslations resize window if needed
	BWindow *window = Window();
	if (!strcmp(window->Name(), "DataTranslations")) {
		BView *view = Parent();
		if (view) {
			BRect frame = view->Frame();
			float x, y;
			GetPreferredSize(&x, &y);
			if (frame.Width() < x || (frame.Height() - 48) < y) {
				x -= frame.Width();
				y -= frame.Height() - 48;
				if (x < 0) x = 0;
				if (y < 0) y = 0;

				// DataTranslations has main view called "Background"
				// change it's resizing mode so it will always resize with window
				// also make sure view will be redrawed after resize
				view = window->FindView("Background");
				if (view) {
					view->SetResizingMode(B_FOLLOW_ALL);
					view->SetFlags(B_FULL_UPDATE_ON_RESIZE);
				}

				// The same with "Info..." button, except redrawing, which isn't needed
				view = window->FindView("Info" B_UTF8_ELLIPSIS);
				if (view)
					view->SetResizingMode(B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM);

				window->ResizeBy( x, y);
			}
		}
	}
}