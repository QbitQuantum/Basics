void WindowMaterialGasMixtureInspectorView::createLayout()
{
  QWidget* visibleWidget = new QWidget();
  this->stackedWidget()->addWidget(visibleWidget);

  QGridLayout* mainGridLayout = new QGridLayout();
  mainGridLayout->setContentsMargins(7,7,7,7);
  mainGridLayout->setSpacing(14);
  visibleWidget->setLayout(mainGridLayout);

  unsigned row = 0;
  unsigned col = 0;

  // Name

  QLabel * label = new QLabel("Name: ");
  label->setObjectName("H2");
  mainGridLayout->addWidget(label,row++,col);

  m_nameEdit = new OSLineEdit();
  mainGridLayout->addWidget(m_nameEdit,row++,0,1,3);

  // Thickness

  label = new QLabel("Thickness: ");
  label->setObjectName("H2");
  mainGridLayout->addWidget(label,row++,col);

  m_thickness = new OSQuantityEdit(m_isIP);
  connect(this, &WindowMaterialGasMixtureInspectorView::toggleUnitsClicked, m_thickness, &OSQuantityEdit::onUnitSystemChange);
  mainGridLayout->addWidget(m_thickness,row++,0,1,3);

  // Number Of Gases In Mixture

  label = new QLabel("Number Of Gases In Mixture: ");
  label->setObjectName("H2");
  mainGridLayout->addWidget(label,row++,col);

  m_numberOfGasesInMixture = new OSIntegerEdit();
  mainGridLayout->addWidget(m_numberOfGasesInMixture,row++,0,1,3);

  //************************* 1 *************************

  // Gas Fraction

  label = new QLabel("Gas 1 Fraction: ");
  label->setObjectName("H2");
  mainGridLayout->addWidget(label,row++,col);

  m_gas1Fraction = new OSQuantityEdit(m_isIP);
  connect(this, &WindowMaterialGasMixtureInspectorView::toggleUnitsClicked, m_gas1Fraction, &OSQuantityEdit::onUnitSystemChange);
  mainGridLayout->addWidget(m_gas1Fraction,row++,0,1,3);

  // Gas Type

  label = new QLabel("Gas 1 Type: ");
  label->setObjectName("H2");
  mainGridLayout->addWidget(label,row++,col);

  m_gas1Type = new OSComboBox();
  m_gas1Type->addItem("Air");
  m_gas1Type->addItem("Argon");
  m_gas1Type->addItem("Krypton");
  m_gas1Type->addItem("Xenon");
  mainGridLayout->addWidget(m_gas1Type,row++,0,1,3);


  //************************* 2 *************************

  // Gas Fraction

  label = new QLabel("Gas 2 Fraction: ");
  label->setObjectName("H2");
  mainGridLayout->addWidget(label,row++,col);

  m_gas2Fraction = new OSQuantityEdit(m_isIP);
  connect(this, &WindowMaterialGasMixtureInspectorView::toggleUnitsClicked, m_gas2Fraction, &OSQuantityEdit::onUnitSystemChange);
  mainGridLayout->addWidget(m_gas2Fraction,row++,0,1,3);

  // Gas Type

  label = new QLabel("Gas 2 Type: ");
  label->setObjectName("H2");
  mainGridLayout->addWidget(label,row++,col);

  m_gas2Type = new OSComboBox();
  m_gas2Type->addItem("Air");
  m_gas2Type->addItem("Argon");
  m_gas2Type->addItem("Krypton");
  m_gas2Type->addItem("Xenon");
  mainGridLayout->addWidget(m_gas2Type,row++,0,1,3);

  //************************* 3 *************************

  // Gas Fraction

  label = new QLabel("Gas 3 Fraction: ");
  label->setObjectName("H2");
  mainGridLayout->addWidget(label,row++,col);

  m_gas3Fraction = new OSQuantityEdit(m_isIP);
  connect(this, &WindowMaterialGasMixtureInspectorView::toggleUnitsClicked, m_gas3Fraction, &OSQuantityEdit::onUnitSystemChange);
  mainGridLayout->addWidget(m_gas3Fraction,row++,0,1,3);

  // Gas Type

  label = new QLabel("Gas 3 Type: ");
  label->setObjectName("H2");
  mainGridLayout->addWidget(label,row++,col);

  m_gas3Type = new OSComboBox();
  m_gas3Type->addItem("Air");
  m_gas3Type->addItem("Argon");
  m_gas3Type->addItem("Krypton");
  m_gas3Type->addItem("Xenon");
  mainGridLayout->addWidget(m_gas3Type,row++,0,1,3);

  //************************* 4 *************************

  // Gas Fraction

  label = new QLabel("Gas 4 Fraction: ");
  label->setObjectName("H2");
  mainGridLayout->addWidget(label,row++,col);

  m_gas4Fraction = new OSQuantityEdit(m_isIP);
  connect(this, &WindowMaterialGasMixtureInspectorView::toggleUnitsClicked, m_gas4Fraction, &OSQuantityEdit::onUnitSystemChange);
  mainGridLayout->addWidget(m_gas4Fraction,row++,0,1,3);

  // Gas Type

  label = new QLabel("Gas 4 Type: ");
  label->setObjectName("H2");
  mainGridLayout->addWidget(label,row++,col);

  m_gas4Type = new OSComboBox();
  m_gas4Type->addItem("Air");
  m_gas4Type->addItem("Argon");
  m_gas4Type->addItem("Krypton");
  m_gas4Type->addItem("Xenon");
  mainGridLayout->addWidget(m_gas4Type,row++,0,1,3);

  // Stretch

  mainGridLayout->setRowStretch(100,100);

  mainGridLayout->setColumnStretch(100,100);
}