// ------------------------------------------------------
//  GLifeConfig Class Constructor Definition
GLifeConfig::GLifeConfig(BRect frame, GLifeState* pglsState)
	:
	BView(frame, "", B_FOLLOW_ALL_SIDES, B_WILL_DRAW),
	m_pglsState(pglsState)
{
	SetLayout(new BGroupLayout(B_HORIZONTAL));
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	// Info text
	BStringView* name = new BStringView(frame, B_EMPTY_STRING,
		B_TRANSLATE("OpenGL \"Game of Life\""), B_FOLLOW_LEFT);
	BStringView* author = new BStringView(frame, B_EMPTY_STRING,
		B_TRANSLATE("by Aaron Hill"), B_FOLLOW_LEFT);

	// Sliders
	fGridDelay = new BSlider(frame, "GridDelay",
		B_TRANSLATE("Grid Life Delay: "),
		new BMessage(kGridDelay),
		0, 4, B_BLOCK_THUMB);

	fGridDelay->SetHashMarks(B_HASH_MARKS_BOTTOM);
	fGridDelay->SetLimitLabels(B_TRANSLATE("None"), B_TRANSLATE_COMMENT("4x", 
			"This is a factor: the x represents 'times'"));
	fGridDelay->SetValue(pglsState->GridDelay());
	fGridDelay->SetHashMarkCount(5);

	fGridBorder = new BSlider(frame, "GridBorder",
		B_TRANSLATE("Grid Border: "),
		new BMessage(kGridBorder),
		0, 10, B_BLOCK_THUMB);

	fGridBorder->SetHashMarks(B_HASH_MARKS_BOTTOM);
	fGridBorder->SetLimitLabels("0", "10");
	fGridBorder->SetValue(pglsState->GridBorder());
	fGridBorder->SetHashMarkCount(11);

	fGridWidth = new BSlider(frame, "GridWidth",
		B_TRANSLATE("Grid Width: "),
		new BMessage(kGridWidth),
		10, 100, B_BLOCK_THUMB);

	fGridWidth->SetHashMarks(B_HASH_MARKS_BOTTOM);
	//fGridWidth->SetLimitLabels("10", "100");
	fGridWidth->SetValue(pglsState->GridWidth());
	fGridWidth->SetHashMarkCount(10);

	fGridHeight = new BSlider(frame, "GridHeight",
		B_TRANSLATE("Grid Height: "),
		new BMessage(kGridHeight),
		10, 100, B_BLOCK_THUMB);

	fGridHeight->SetHashMarks(B_HASH_MARKS_BOTTOM);
	//fGridHeight->SetLimitLabels("10", "100");
	fGridHeight->SetValue(pglsState->GridHeight());
	fGridHeight->SetHashMarkCount(10);

	AddChild(BGroupLayoutBuilder(B_VERTICAL, B_USE_DEFAULT_SPACING)
		.Add(BGroupLayoutBuilder(B_VERTICAL, 0)
			.Add(name)
			.Add(author)
		)
		.AddGlue()
		.Add(fGridDelay)
		.Add(fGridBorder)
		.Add(BGroupLayoutBuilder(B_HORIZONTAL, 0)
			.Add(fGridWidth)
			.Add(fGridHeight)
		)
		.SetInsets(B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING,
			B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING)
	);

	// Do our first label update
	_UpdateLabels();
}