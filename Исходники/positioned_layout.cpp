	ViewGeometry PositionedLayout::get_geometry(Canvas &canvas, View *view, const Rectf &containing_box)
	{
		bool definite_left = !view->style_cascade().computed_value("left").is_keyword("auto");
		bool definite_right = !view->style_cascade().computed_value("right").is_keyword("auto");
		bool definite_width = !view->style_cascade().computed_value("width").is_keyword("auto");

		float computed_left = resolve_percentage(view->style_cascade().computed_value("left"), containing_box.get_width());
		float computed_right = resolve_percentage(view->style_cascade().computed_value("right"), containing_box.get_width());
		float computed_width = resolve_percentage(view->style_cascade().computed_value("width"), containing_box.get_width());

		float x = 0.0f;
		float width = 0.0f;

		if (definite_left && definite_right)
		{
			x = computed_left;
			width = clan::max(containing_box.get_width() - computed_right - x, 0.0f);
		}
		else if (definite_left && definite_width)
		{
			x = computed_left;
			width = computed_width;
		}
		else if (definite_right && definite_width)
		{
			width = computed_width;
			x = containing_box.get_width() - computed_right - width;
		}
		else if (definite_left)
		{
			x = computed_left;
			width = view->preferred_width(canvas);
			// Note: in HTML there's an additional implicit "max-width: calc(100%-left)" rule active here.
			// We are not emulating this "feature" as it is most likely a bug that got standardized for backwards compatibility.
			// The user should add an max-width rule themselves if they want such an odd constraint active.
		}
		else if (definite_right)
		{
			width = view->preferred_width(canvas);
			x = containing_box.get_width() - computed_right - width;
		}
		else if (definite_width)
		{
			x = 0.0f;
			width = view->style_cascade().computed_value("width").number();
		}
		else
		{
			x = 0.0f;
			width = view->preferred_width(canvas);
		}

		bool definite_top = !view->style_cascade().computed_value("top").is_keyword("auto");
		bool definite_bottom = !view->style_cascade().computed_value("bottom").is_keyword("auto");
		bool definite_height = !view->style_cascade().computed_value("height").is_keyword("auto");

		float computed_top = resolve_percentage(view->style_cascade().computed_value("top"), containing_box.get_height());
		float computed_bottom = resolve_percentage(view->style_cascade().computed_value("bottom"), containing_box.get_height());
		float computed_height = resolve_percentage(view->style_cascade().computed_value("height"), containing_box.get_height());

		float y = 0.0f;
		float height = 0.0f;

		if (definite_top && definite_bottom)
		{
			y = computed_top;
			height = clan::max(containing_box.get_height() - computed_bottom - y, 0.0f);
		}
		else if (definite_top && definite_height)
		{
			y = computed_top;
			height = computed_height;
		}
		else if (definite_bottom && definite_height)
		{
			height = computed_height;
			y = containing_box.get_height() - computed_bottom - height;
		}
		else if (definite_top)
		{
			y = computed_top;
			height = view->preferred_height(canvas, width);
		}
		else if (definite_bottom)
		{
			height = view->preferred_height(canvas, width);
			y = containing_box.get_height() - computed_bottom - height;
		}
		else if (definite_height)
		{
			y = 0.0f;
			height = computed_height;
		}
		else
		{
			y = 0.0f;
			height = view->preferred_height(canvas, width);
		}


		x += containing_box.left;
		y += containing_box.top;

		auto tl = canvas.grid_fit(Pointf(x, y));
		auto br = canvas.grid_fit(Pointf(x + width, y + height));
		Rectf box = Rectf(tl.x, tl.y, br.x, br.y);
		return ViewGeometry::from_content_box(view->style_cascade(), box);
	}