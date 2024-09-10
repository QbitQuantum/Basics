PropertiesRasterLayer::PropertiesRasterLayer() :
   LabeledSectionGroup(NULL),
   mInitializing(false),
   mpRasterLayer(NULL)
{
   // Display configuration
   QWidget* pDisplayWidget = new QWidget(this);

   QLabel* pDisplayModeLabel = new QLabel("Display Mode:", pDisplayWidget);
   mpDisplayModeCombo = new QComboBox(pDisplayWidget);
   vector<string> modes = StringUtilities::getAllEnumValuesAsDisplayString<DisplayMode>();
   for (vector<string>::iterator it = modes.begin(); it != modes.end(); ++it)
   {
      mpDisplayModeCombo->addItem(QString::fromStdString(*it));
   }
   mpComplexComponentLabel = new QLabel("Complex Component:", pDisplayWidget);
   mpComplexComponentCombo = new ComplexComponentComboBox(pDisplayWidget);
   QLabel* pOpacityLabel = new QLabel("Opacity:", pDisplayWidget);
   mpOpacitySpin = new QSpinBox(pDisplayWidget);
   mpOpacitySpin->setMinimum(0);
   mpOpacitySpin->setMaximum(255);
   mpOpacitySpin->setSingleStep(1);

   LabeledSection* pDisplaySection = new LabeledSection(pDisplayWidget, "Display Configuration", this);

   QGridLayout* pDisplayGrid = new QGridLayout(pDisplayWidget);
   pDisplayGrid->setMargin(0);
   pDisplayGrid->setSpacing(5);
   pDisplayGrid->addWidget(pDisplayModeLabel, 0, 0);
   pDisplayGrid->addWidget(mpDisplayModeCombo, 0, 1, Qt::AlignLeft);
   pDisplayGrid->addWidget(mpComplexComponentLabel, 1, 0);
   pDisplayGrid->addWidget(mpComplexComponentCombo, 1, 1, Qt::AlignLeft);
   pDisplayGrid->addWidget(pOpacityLabel, 2, 0);
   pDisplayGrid->addWidget(mpOpacitySpin, 2, 1, Qt::AlignLeft);
   pDisplayGrid->setRowStretch(3, 10);
   pDisplayGrid->setColumnStretch(1, 10);

   // Grayscale
   QWidget* pGrayscaleWidget = new QWidget(this);

   QLabel* pGrayElementLabel = new QLabel("Display Element:", pGrayscaleWidget);
   mpGrayElementCombo = new QComboBox(pGrayscaleWidget);
   mpGrayElementCombo->setMinimumContentsLength(10);

   QLabel* pGrayBandLabel = new QLabel("Display Band:", pGrayscaleWidget);
   mpGrayBandCombo = new QComboBox(pGrayscaleWidget);

   QLabel* pGrayLowerLabel = new QLabel("Lower Stretch Value:", pGrayscaleWidget);
   mpGrayLowerSpin = new QDoubleSpinBox(pGrayscaleWidget);
   mpGrayLowerSpin->setRange(-1 * numeric_limits<double>::max(), numeric_limits<double>::max());
   mpGrayLowerSpin->setDecimals(6);

   QLabel* pGrayUpperLabel = new QLabel("Upper Stretch Value:", pGrayscaleWidget);
   mpGrayUpperSpin = new QDoubleSpinBox(pGrayscaleWidget);
   mpGrayUpperSpin->setRange(-1 * numeric_limits<double>::max(), numeric_limits<double>::max());
   mpGrayUpperSpin->setDecimals(6);

   QLabel* pGrayUnitsLabel = new QLabel("Stretch Units:", pGrayscaleWidget);
   mpGrayUnitsCombo = new RegionUnitsComboBox(pGrayscaleWidget);

   QLabel* pGrayStretchTypeLabel = new QLabel("Stretch Type:", pGrayscaleWidget);
   mpGrayStretchTypeCombo = new StretchTypeComboBox(pGrayscaleWidget);

   QPushButton* pGrayStretchFavoritesButton = new QPushButton("Favorites", this);
   mpGrayStretchMenu = new QMenu(pGrayStretchFavoritesButton);
   pGrayStretchFavoritesButton->setMenu(mpGrayStretchMenu);

   mpAddFavoriteGrayAction = new QAction("Add Stretch to Favorites", this);
   mpRemoveFavoriteAction = new QAction("Remove Stretch from Favorites...", this);

   LabeledSection* pGrayscaleSection = new LabeledSection(pGrayscaleWidget, "Grayscale", this);

   QGridLayout* pGrayscaleGrid = new QGridLayout(pGrayscaleWidget);
   pGrayscaleGrid->setMargin(0);
   pGrayscaleGrid->setSpacing(5);
   pGrayscaleGrid->addWidget(pGrayElementLabel, 0, 0);
   pGrayscaleGrid->addWidget(mpGrayElementCombo, 0, 1, 1, 2);
   pGrayscaleGrid->addWidget(pGrayBandLabel, 1, 0);
   pGrayscaleGrid->addWidget(mpGrayBandCombo, 1, 1, 1, 2);
   pGrayscaleGrid->addWidget(pGrayLowerLabel, 2, 0);
   pGrayscaleGrid->addWidget(mpGrayLowerSpin, 2, 1);
   pGrayscaleGrid->addWidget(pGrayStretchFavoritesButton, 2, 2, Qt::AlignLeft);
   pGrayscaleGrid->addWidget(pGrayUpperLabel, 3, 0);
   pGrayscaleGrid->addWidget(mpGrayUpperSpin, 3, 1);
   pGrayscaleGrid->addWidget(pGrayUnitsLabel, 4, 0);
   pGrayscaleGrid->addWidget(mpGrayUnitsCombo, 4, 1);
   pGrayscaleGrid->addWidget(pGrayStretchTypeLabel, 5, 0);
   pGrayscaleGrid->addWidget(mpGrayStretchTypeCombo, 5, 1);
   pGrayscaleGrid->setRowStretch(6, 10);
   pGrayscaleGrid->setColumnStretch(2, 10);

   // RGB
   QWidget* pRgbWidget = new QWidget(this);

   QLabel* pRedLabel = new QLabel("Red:", pRgbWidget);
   QLabel* pGreenLabel = new QLabel("Green:", pRgbWidget);
   QLabel* pBlueLabel = new QLabel("Blue:", pRgbWidget);

   QLabel* pRgbElementLabel = new QLabel("Display Element:", pRgbWidget);
   mpRedElementCombo = new QComboBox(pRgbWidget);
   mpRedElementCombo->setMinimumContentsLength(10);
   mpGreenElementCombo = new QComboBox(pRgbWidget);
   mpGreenElementCombo->setMinimumContentsLength(10);
   mpBlueElementCombo = new QComboBox(pRgbWidget);
   mpBlueElementCombo->setMinimumContentsLength(10);

   QLabel* pRgbBandLabel = new QLabel("Display Band:", pRgbWidget);
   mpRedBandCombo = new QComboBox(pRgbWidget);
   mpGreenBandCombo = new QComboBox(pRgbWidget);
   mpBlueBandCombo = new QComboBox(pRgbWidget);

   QLabel* pRgbLowerLabel = new QLabel("Lower Stretch Value:", pRgbWidget);
   mpRedLowerSpin = new QDoubleSpinBox(pRgbWidget);
   mpRedLowerSpin->setRange(-1 * numeric_limits<double>::max(), numeric_limits<double>::max());
   mpRedLowerSpin->setDecimals(6);
   mpGreenLowerSpin = new QDoubleSpinBox(pRgbWidget);
   mpGreenLowerSpin->setRange(-1 * numeric_limits<double>::max(), numeric_limits<double>::max());
   mpGreenLowerSpin->setDecimals(6);
   mpBlueLowerSpin = new QDoubleSpinBox(pRgbWidget);
   mpBlueLowerSpin->setRange(-1 * numeric_limits<double>::max(), numeric_limits<double>::max());
   mpBlueLowerSpin->setDecimals(6);

   QLabel* pRgbUpperLabel = new QLabel("Upper Stretch Value:", pRgbWidget);
   mpRedUpperSpin = new QDoubleSpinBox(pRgbWidget);
   mpRedUpperSpin->setRange(-1 * numeric_limits<double>::max(), numeric_limits<double>::max());
   mpRedUpperSpin->setDecimals(6);
   mpGreenUpperSpin = new QDoubleSpinBox(pRgbWidget);
   mpGreenUpperSpin->setRange(-1 * numeric_limits<double>::max(), numeric_limits<double>::max());
   mpGreenUpperSpin->setDecimals(6);
   mpBlueUpperSpin = new QDoubleSpinBox(pRgbWidget);
   mpBlueUpperSpin->setRange(-1 * numeric_limits<double>::max(), numeric_limits<double>::max());
   mpBlueUpperSpin->setDecimals(6);

   QLabel* pRgbUnitsLabel = new QLabel("Stretch Units:", pRgbWidget);
   mpRedUnitsCombo = new RegionUnitsComboBox(pRgbWidget);
   mpGreenUnitsCombo = new RegionUnitsComboBox(pRgbWidget);
   mpBlueUnitsCombo = new RegionUnitsComboBox(pRgbWidget);

   mpDisplayBandButton = new QPushButton("Presets", pRgbWidget);
   mpDisplayBandButton->setEnabled(false);
   QMenu* pMenu = new QMenu(mpDisplayBandButton);
   mpDisplayBandButton->setMenu(pMenu);

   const DynamicObject* pColorComposites = RasterLayer::getSettingColorComposites();
   if (pColorComposites != NULL)
   {
      vector<string> names;
      pColorComposites->getAttributeNames(names);
      if (names.empty() == false)
      {
         for (vector<string>::const_iterator iter = names.begin(); iter != names.end(); ++iter)
         {
            pMenu->addAction(QString::fromStdString(*iter));
         }

         mpDisplayBandButton->setEnabled(true);
      }
   }

   QLabel* pRgbStretchTypeLabel = new QLabel("Stretch Type:", pRgbWidget);
   mpRgbStretchTypeCombo = new StretchTypeComboBox(pRgbWidget);

   QPushButton* pRgbStretchFavoritesButton = new QPushButton("Favorites", pRgbWidget);
   mpRgbStretchMenu = new QMenu(pRgbStretchFavoritesButton);
   pRgbStretchFavoritesButton->setMenu(mpRgbStretchMenu);

   mpAddFavoriteRedAction = new QAction("Add Red Stretch to Favorites", pRgbWidget);
   mpAddFavoriteGreenAction = new QAction("Add Green Stretch to Favorites", pRgbWidget);
   mpAddFavoriteBlueAction = new QAction("Add Blue Stretch to Favorites", pRgbWidget);

   LabeledSection* pRgbSection = new LabeledSection(pRgbWidget, "RGB", this);

   QGridLayout* pRgbGrid = new QGridLayout(pRgbWidget);
   pRgbGrid->setMargin(0);
   pRgbGrid->setSpacing(5);
   pRgbGrid->addWidget(pRedLabel, 0, 1);
   pRgbGrid->addWidget(pGreenLabel, 0, 2);
   pRgbGrid->addWidget(pBlueLabel, 0, 3);
   pRgbGrid->addWidget(pRgbElementLabel, 1, 0);
   pRgbGrid->addWidget(mpRedElementCombo, 1, 1);
   pRgbGrid->addWidget(mpGreenElementCombo, 1, 2);
   pRgbGrid->addWidget(mpBlueElementCombo, 1, 3);
   pRgbGrid->addWidget(pRgbBandLabel, 2, 0);
   pRgbGrid->addWidget(mpRedBandCombo, 2, 1);
   pRgbGrid->addWidget(mpGreenBandCombo, 2, 2);
   pRgbGrid->addWidget(mpBlueBandCombo, 2, 3);
   pRgbGrid->addWidget(mpDisplayBandButton, 2, 4);
   pRgbGrid->addWidget(pRgbLowerLabel, 3, 0);
   pRgbGrid->addWidget(mpRedLowerSpin, 3, 1, Qt::AlignLeft);
   pRgbGrid->addWidget(mpGreenLowerSpin, 3, 2, Qt::AlignLeft);
   pRgbGrid->addWidget(mpBlueLowerSpin, 3, 3, Qt::AlignLeft);
   pRgbGrid->addWidget(pRgbStretchFavoritesButton, 3, 4);
   pRgbGrid->addWidget(pRgbUpperLabel, 4, 0);
   pRgbGrid->addWidget(mpRedUpperSpin, 4, 1, Qt::AlignLeft);
   pRgbGrid->addWidget(mpGreenUpperSpin, 4, 2, Qt::AlignLeft);
   pRgbGrid->addWidget(mpBlueUpperSpin, 4, 3, Qt::AlignLeft);
   pRgbGrid->addWidget(pRgbUnitsLabel, 5, 0);
   pRgbGrid->addWidget(mpRedUnitsCombo, 5, 1, Qt::AlignLeft);
   pRgbGrid->addWidget(mpGreenUnitsCombo, 5, 2, Qt::AlignLeft);
   pRgbGrid->addWidget(mpBlueUnitsCombo, 5, 3, Qt::AlignLeft);
   pRgbGrid->addWidget(pRgbStretchTypeLabel, 6, 0);
   pRgbGrid->addWidget(mpRgbStretchTypeCombo, 6, 1, Qt::AlignLeft);
   pRgbGrid->setRowStretch(7, 10);
   pRgbGrid->setColumnStretch(1, 10);
   pRgbGrid->setColumnStretch(2, 10);
   pRgbGrid->setColumnStretch(3, 10);

   // Graphics acceleration
   QLabel* pUnsupportedLabel = new QLabel("Dynamic texture generation is not supported on this system.", this);
   pUnsupportedLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);

   QWidget* pAccelerationWidget = new QWidget(this);
   mpAccelerationCheck = new QCheckBox("Enable Dynamic Generation", pAccelerationWidget);
   mpFilterCheck = new QCheckBox("Filter:", pAccelerationWidget);
   mpFilterList = new QListWidget(pDisplayWidget);
   mpFilterList->setSelectionMode(QAbstractItemView::ExtendedSelection);

   QStringList filterNames;
   Service<ImageFilterManager> pFilterManager;

   vector<string> filters = pFilterManager->getAvailableFilters();
   for (vector<string>::iterator iter = filters.begin(); iter != filters.end(); ++iter)
   {
      string filterName = *iter;
      if (filterName.empty() == false)
      {
         filterNames.append(QString::fromStdString(filterName));
      }
   }

   filterNames.sort();
   mpFilterList->addItems(filterNames);

   QStackedWidget* pAccelerationStack = new QStackedWidget(this);
   LabeledSection* pAccelerationSection = new LabeledSection(pAccelerationStack,
      "Dynamic Texture Generation", this);

   QGridLayout* pAccelerationGrid = new QGridLayout(pAccelerationWidget);
   pAccelerationGrid->setMargin(0);
   pAccelerationGrid->setSpacing(5);
   pAccelerationGrid->addWidget(mpAccelerationCheck, 0, 0, 1, 2);
   pAccelerationGrid->addWidget(mpFilterCheck, 1, 0, Qt::AlignTop);
   pAccelerationGrid->addWidget(mpFilterList, 1, 1, Qt::AlignLeft);
   pAccelerationGrid->setRowStretch(1, 10);
   pAccelerationGrid->setColumnStretch(1, 10);

   bool bUnsupported = true;
#if defined (CG_SUPPORTED)
   if (CgContext::instance() != NULL)
   {
      bUnsupported = false;
   }
#endif

   if (bUnsupported == true)
   {
      pAccelerationStack->addWidget(pUnsupportedLabel);
      pAccelerationWidget->hide();
   }
   else
   {
      pAccelerationStack->addWidget(pAccelerationWidget);
      pUnsupportedLabel->hide();
   }

   // Initialization
   addSection(pDisplaySection);
   addSection(pGrayscaleSection);
   addSection(pRgbSection);
   addSection(pAccelerationSection, 10);
   setSizeHint(600, 610);

   // Connections
   VERIFYNR(mDisplayConfigModifier.attachSignal(mpDisplayModeCombo, SIGNAL(currentIndexChanged(int))));
   VERIFYNR(mDisplayConfigModifier.attachSignal(mpComplexComponentCombo, SIGNAL(valueChanged(ComplexComponent))));
   VERIFYNR(mDisplayConfigModifier.attachSignal(mpOpacitySpin, SIGNAL(valueChanged(int))));

   VERIFYNR(connect(mpGrayElementCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDisplayedBandCombo(int))));
   VERIFYNR(connect(mpGrayBandCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateStretchValuesFromBand())));
   VERIFYNR(connect(mpGrayStretchMenu, SIGNAL(aboutToShow()), this, SLOT(initializeStretchMenu())));
   VERIFYNR(connect(mpGrayStretchMenu, SIGNAL(triggered(QAction*)), this, SLOT(setGrayStretch(QAction*))));
   VERIFYNR(connect(mpRemoveFavoriteAction, SIGNAL(triggered()), this, SLOT(removeStretchFavorite())));
   VERIFYNR(connect(mpGrayUnitsCombo, SIGNAL(valueChanged(RegionUnits)), this,
      SLOT(updateStretchValuesFromUnits(RegionUnits))));
   VERIFYNR(mGrayscaleModifier.attachSignal(mpGrayElementCombo, SIGNAL(currentIndexChanged(int))));
   VERIFYNR(mGrayscaleModifier.attachSignal(mpGrayBandCombo, SIGNAL(currentIndexChanged(int))));
   VERIFYNR(mGrayscaleModifier.attachSignal(mpGrayLowerSpin, SIGNAL(valueChanged(double))));
   VERIFYNR(mGrayscaleModifier.attachSignal(mpGrayUpperSpin, SIGNAL(valueChanged(double))));
   VERIFYNR(mGrayscaleModifier.attachSignal(mpGrayUnitsCombo, SIGNAL(valueChanged(RegionUnits))));
   VERIFYNR(mGrayscaleModifier.attachSignal(mpGrayStretchTypeCombo, SIGNAL(valueChanged(StretchType))));

   VERIFYNR(connect(mpRedElementCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDisplayedBandCombo(int))));
   VERIFYNR(connect(mpGreenElementCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDisplayedBandCombo(int))));
   VERIFYNR(connect(mpBlueElementCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDisplayedBandCombo(int))));
   VERIFYNR(connect(mpRedBandCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateStretchValuesFromBand())));
   VERIFYNR(connect(mpGreenBandCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateStretchValuesFromBand())));
   VERIFYNR(connect(mpBlueBandCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateStretchValuesFromBand())));
   VERIFYNR(connect(pMenu, SIGNAL(triggered(QAction*)), this, SLOT(setDisplayBands(QAction*))));
   VERIFYNR(connect(mpRgbStretchMenu, SIGNAL(aboutToShow()), this, SLOT(initializeStretchMenu())));
   VERIFYNR(connect(mpRgbStretchMenu, SIGNAL(triggered(QAction*)), this, SLOT(setRgbStretch(QAction*))));
   VERIFYNR(connect(mpRedUnitsCombo, SIGNAL(valueChanged(RegionUnits)), this,
      SLOT(updateStretchValuesFromUnits(RegionUnits))));
   VERIFYNR(connect(mpGreenUnitsCombo, SIGNAL(valueChanged(RegionUnits)), this,
      SLOT(updateStretchValuesFromUnits(RegionUnits))));
   VERIFYNR(connect(mpBlueUnitsCombo, SIGNAL(valueChanged(RegionUnits)), this,
      SLOT(updateStretchValuesFromUnits(RegionUnits))));
   VERIFYNR(mRgbModifier.attachSignal(mpRedElementCombo, SIGNAL(currentIndexChanged(int))));
   VERIFYNR(mRgbModifier.attachSignal(mpGreenElementCombo, SIGNAL(currentIndexChanged(int))));
   VERIFYNR(mRgbModifier.attachSignal(mpBlueElementCombo, SIGNAL(currentIndexChanged(int))));
   VERIFYNR(mRgbModifier.attachSignal(mpRedBandCombo, SIGNAL(currentIndexChanged(int))));
   VERIFYNR(mRgbModifier.attachSignal(mpGreenBandCombo, SIGNAL(currentIndexChanged(int))));
   VERIFYNR(mRgbModifier.attachSignal(mpBlueBandCombo, SIGNAL(currentIndexChanged(int))));
   VERIFYNR(mRgbModifier.attachSignal(mpRedLowerSpin, SIGNAL(valueChanged(double))));
   VERIFYNR(mRgbModifier.attachSignal(mpGreenLowerSpin, SIGNAL(valueChanged(double))));
   VERIFYNR(mRgbModifier.attachSignal(mpBlueLowerSpin, SIGNAL(valueChanged(double))));
   VERIFYNR(mRgbModifier.attachSignal(mpRedUpperSpin, SIGNAL(valueChanged(double))));
   VERIFYNR(mRgbModifier.attachSignal(mpGreenUpperSpin, SIGNAL(valueChanged(double))));
   VERIFYNR(mRgbModifier.attachSignal(mpBlueUpperSpin, SIGNAL(valueChanged(double))));
   VERIFYNR(mRgbModifier.attachSignal(mpRedUnitsCombo, SIGNAL(valueChanged(RegionUnits))));
   VERIFYNR(mRgbModifier.attachSignal(mpGreenUnitsCombo, SIGNAL(valueChanged(RegionUnits))));
   VERIFYNR(mRgbModifier.attachSignal(mpBlueUnitsCombo, SIGNAL(valueChanged(RegionUnits))));
   VERIFYNR(mRgbModifier.attachSignal(mpRgbStretchTypeCombo, SIGNAL(valueChanged(StretchType))));

   VERIFYNR(connect(mpAccelerationCheck, SIGNAL(toggled(bool)), this, SLOT(enableFilterCheck(bool))));
   VERIFYNR(connect(mpFilterCheck, SIGNAL(toggled(bool)), this, SLOT(enableFilterCombo(bool))));
   VERIFYNR(mGraphicsAccModifier.attachSignal(mpAccelerationCheck, SIGNAL(toggled(bool))));
   VERIFYNR(mGraphicsAccModifier.attachSignal(mpFilterCheck, SIGNAL(toggled(bool))));
   VERIFYNR(mGraphicsAccModifier.attachSignal(mpFilterList, SIGNAL(itemSelectionChanged())));
}