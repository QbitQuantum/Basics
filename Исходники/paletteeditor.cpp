PaletteEditor::PaletteEditor ( QWidget* parent )
: QWidget(parent), checkers(15)
{
	setupUi ( this );
	loadPalette(0);

	m_palettesView->setModel(&m_flamPalettes);
	m_browseView->setModel(&m_browsePalettes);
	hasUGR = false;
	QSettings settings;
	settings.beginGroup("paletteeditor");
	m_tabWidget->setCurrentIndex(settings.value("tabwidgetindex", 0).toInt());
	m_lastBrowseDir = settings.value("lastdirectory", QDir::homePath()).toString();
	m_gradientEnds->setArrowDirection(Qt::DownArrow);
	m_gradientEnds->setMenuEnabled(false);

	m_gradientSpreadGroup = new QButtonGroup(this);
	m_gradientSpreadGroup->addButton(m_padSpreadButton, QGradient::PadSpread);
	m_gradientSpreadGroup->addButton(m_repeatSpreadButton, QGradient::RepeatSpread);
	m_gradientSpreadGroup->addButton(m_reflectSpreadButton, QGradient::ReflectSpread);
	m_padSpreadButton->setChecked(true);

	// restore the gradient from settings
	int nstops( settings.beginReadArray("gradient") );
	if (nstops > 1)
	{
		GradientStops stops;
		for (int n = 0 ; n < nstops ; n++)
		{
			settings.setArrayIndex(n);
			double pos( settings.value("pos").toDouble() );
			QColor color( settings.value("color").value<QColor>()) ;
			stops.append(GradientStop( pos, color ));
		}
		settings.endArray();
		p_stops = stops;
		m_gradientStops->setStops(stops);
	}
	stopsChangedAction();

	connect(m_palettesView, SIGNAL(pressed(const QModelIndex&)), this, SLOT(paletteIndexChangedAction(const QModelIndex&)));
	connect(m_browseView, SIGNAL(pressed(const QModelIndex&)), this, SLOT(selectGradientAction(const QModelIndex&)));
	connect(m_rotateSlider, SIGNAL(valueChanged(int)), this, SLOT(paletteRotatedAction(int)));
	connect(m_rotateSlider, SIGNAL(sliderReleased()), this, SIGNAL(undoStateSignal()));
	connect(m_openButton, SIGNAL(clicked(bool)), this, SLOT(openGradientAction(bool)));
	connect(m_gradientStops, SIGNAL(stopsChanged()), this, SLOT(stopsChangedAction()));
	connect(m_gradientStops, SIGNAL(stopsDropped()), this, SIGNAL(undoStateSignal()));
	connect(m_gradientEnds, SIGNAL(stopsChanged()), this, SLOT(stopsChangedAction()));
	connect(m_gradientEnds, SIGNAL(stopsDropped()), this, SIGNAL(undoStateSignal()));
	connect(m_gradientSpreadGroup, SIGNAL(buttonClicked(int)), this, SLOT(stopsChangedAction()));
	connect(m_gradientSpreadGroup, SIGNAL(buttonClicked(int)), this, SIGNAL(undoStateSignal()));
	connect(m_resetGradientButton, SIGNAL(clicked(bool)), this, SLOT(resetGradientAction()));
	connect(m_resetGradientButton, SIGNAL(clicked(bool)), this, SIGNAL(undoStateSignal()));
	connect(m_saveGradientButton, SIGNAL(clicked(bool)), this, SLOT(saveGradientAction()));
	connect(m_browseLineEdit, SIGNAL(returnPressed()), this, SLOT(browsePathChangedAction()));
	connect(m_randomGradientButton, SIGNAL(clicked(bool)), this, SLOT(createRandomGradientAction()));
	connect(m_randomGradientButton, SIGNAL(clicked(bool)), this, SIGNAL(undoStateSignal()));
}