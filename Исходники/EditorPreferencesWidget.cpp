void EditorPreferencesWidget::initializeGUI()
{
	layout = new QGridLayout(this);

	// Initialize our general group box.

	generalGroupBox = new QGroupBox(tr("General"), this);
	generalLayout = new QGridLayout(generalGroupBox);

	showGutterCheckBox = new QCheckBox(tr("Show Gutter"), generalGroupBox);

	editorFontLabel =
	        new QLabel(tr("Editor Font"), generalGroupBox, nullptr);
	editorFontButton = new FontPickerButton(generalGroupBox);

	indentationWidthLabel =
	        new QLabel(tr("Indentation Width"), generalGroupBox, nullptr);
	indentationWidthSpinBox = new QSpinBox(generalGroupBox);
	indentationWidthSpinBox->setMinimum(2);
	indentationWidthSpinBox->setMaximum(24);

	indentationModeLabel =
	        new QLabel(tr("Indentation Mode"), generalGroupBox, nullptr);
	indentationModeButtonGroup = new QButtonGroup(generalGroupBox);
	indentationModeTabsRadioButton =
	        new QRadioButton(tr("Tabs"), generalGroupBox);
	indentationModeSpacesRadioButton =
	        new QRadioButton(tr("Spaces"), generalGroupBox);
	indentationModeButtonGroup->addButton(indentationModeTabsRadioButton);
	indentationModeButtonGroup->addButton(indentationModeSpacesRadioButton);

	generalLayout->addWidget(showGutterCheckBox, 0, 0, 1, 1, nullptr);
	generalLayout->addWidget(editorFontLabel, 1, 0, 1, 1, nullptr);
	generalLayout->addWidget(editorFontButton, 1, 1, 1, 1, nullptr);
	generalLayout->addWidget(indentationWidthLabel, 2, 0, 1, 1, nullptr);
	generalLayout->addWidget(indentationWidthSpinBox, 2, 1, 1, 1, nullptr);
	generalLayout->addWidget(indentationModeLabel, 3, 0, 1, 1, nullptr);
	generalLayout->addWidget(indentationModeTabsRadioButton, 3, 1, 1, 1,
	                         nullptr);
	generalLayout->addWidget(indentationModeSpacesRadioButton, 4, 1, 1, 1,
	                         nullptr);

	generalLayout->setRowStretch(5, 1);
	generalLayout->setColumnStretch(0, 1);

	generalGroupBox->setLayout(generalLayout);

	// Initialize our line wrap guide group box.

	lineWrapGuideGroupBox = new QGroupBox(tr("Line Wrap Guide"), this);
	lineWrapGuideLayout = new QGridLayout(lineWrapGuideGroupBox);

	lineWrapGuideCheckBox =
	        new QCheckBox(tr("Show Guide (Monospaced fonts only.)"),
	                      lineWrapGuideGroupBox);

	lineWrapGuideWidthLabel = new QLabel(tr("Character Width"),
	                                     lineWrapGuideGroupBox, nullptr);

	lineWrapGuideWidthSpinBox = new QSpinBox(lineWrapGuideGroupBox);
	lineWrapGuideWidthSpinBox->setMinimum(10);
	lineWrapGuideWidthSpinBox->setMaximum(500);

	lineWrapGuideColorLabel =
	        new QLabel(tr("Color"), lineWrapGuideGroupBox, nullptr);

	lineWrapGuideColorButton = new ColorPickerButton(lineWrapGuideGroupBox);

	lineWrapGuideLayout->addWidget(lineWrapGuideCheckBox, 0, 0, 1, 1,
	                               nullptr);
	lineWrapGuideLayout->addWidget(lineWrapGuideWidthLabel, 1, 0, 1, 1,
	                               nullptr);
	lineWrapGuideLayout->addWidget(lineWrapGuideWidthSpinBox, 1, 1, 1, 1,
	                               nullptr);
	lineWrapGuideLayout->addWidget(lineWrapGuideColorLabel, 2, 0, 1, 1,
	                               nullptr);
	lineWrapGuideLayout->addWidget(lineWrapGuideColorButton, 2, 1, 1, 1,
	                               nullptr);

	lineWrapGuideLayout->setRowStretch(3, 1);
	lineWrapGuideLayout->setColumnStretch(0, 1);

	lineWrapGuideGroupBox->setLayout(lineWrapGuideLayout);

	// Initialize our colors group box.

	colorsGroupBox = new QGroupBox(tr("Colors"), this);
	colorsLayout = new QGridLayout(colorsGroupBox);

	editorFGLabel =
	        new QLabel(tr("Editor Foreground"), colorsGroupBox, nullptr);
	editorFGButton = new ColorPickerButton(colorsGroupBox);

	editorBGLabel =
	        new QLabel(tr("Editor Background"), colorsGroupBox, nullptr);
	editorBGButton = new ColorPickerButton(colorsGroupBox);

	currentLineBGLabel = new QLabel(tr("Current Line Background"),
	                                colorsGroupBox, nullptr);
	currentLineBGButton = new ColorPickerButton(colorsGroupBox);

	gutterFGLabel =
	        new QLabel(tr("Gutter Foreground"), colorsGroupBox, nullptr);
	gutterFGButton = new ColorPickerButton(colorsGroupBox);

	gutterBGLabel =
	        new QLabel(tr("Gutter Background"), colorsGroupBox, nullptr);
	gutterBGButton = new ColorPickerButton(colorsGroupBox);

	colorsLayout->addWidget(editorFGLabel, 0, 0, 1, 1, nullptr);
	colorsLayout->addWidget(editorFGButton, 0, 1, 1, 1, nullptr);
	colorsLayout->addWidget(editorBGLabel, 1, 0, 1, 1, nullptr);
	colorsLayout->addWidget(editorBGButton, 1, 1, 1, 1, nullptr);
	colorsLayout->addWidget(currentLineBGLabel, 2, 0, 1, 1, nullptr);
	colorsLayout->addWidget(currentLineBGButton, 2, 1, 1, 1, nullptr);
	colorsLayout->addWidget(gutterFGLabel, 3, 0, 1, 1, nullptr);
	colorsLayout->addWidget(gutterFGButton, 3, 1, 1, 1, nullptr);
	colorsLayout->addWidget(gutterBGLabel, 4, 0, 1, 1, nullptr);
	colorsLayout->addWidget(gutterBGButton, 4, 1, 1, 1, nullptr);

	colorsLayout->setRowStretch(5, 1);
	colorsLayout->setColumnStretch(0, 1);

	colorsGroupBox->setLayout(colorsLayout);

	// Add these group boxes to our layout.

	layout->addWidget(generalGroupBox, 1, 0, 1, 1, nullptr);
	layout->addWidget(lineWrapGuideGroupBox, 2, 0, 1, 1, nullptr);
	layout->addWidget(colorsGroupBox, 3, 0, 1, 1, nullptr);

	layout->setColumnStretch(0, 1);
	layout->setRowStretch(4, 1);

	setLayout(layout);
}