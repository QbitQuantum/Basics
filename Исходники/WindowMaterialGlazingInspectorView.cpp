void WindowMaterialGlazingInspectorView::createLayout()
{
    auto hiddenWidget = new QWidget();
    this->stackedWidget()->addWidget(hiddenWidget);

    auto visibleWidget = new QWidget();
    this->stackedWidget()->addWidget(visibleWidget);

    auto mainGridLayout = new QGridLayout();
    mainGridLayout->setContentsMargins(7, 7, 7, 7);
    mainGridLayout->setSpacing(14);
    visibleWidget->setLayout(mainGridLayout);

    int row = mainGridLayout->rowCount();

    QLabel * label = nullptr;

    // Name

    label = new QLabel("Name: ");
    label->setObjectName("H2");
    mainGridLayout->addWidget(label, row, 0);

    ++row;

    m_nameEdit = new OSLineEdit();
    mainGridLayout->addWidget(m_nameEdit, row, 0, 1, 3);

    ++row;

    // Standards Information

    m_standardsInformationWidget = new StandardsInformationMaterialWidget(m_isIP, mainGridLayout, row);

    ++row;

    // Optical Data Type

    label = new QLabel("Optical Data Type: ");
    label->setObjectName("H2");
    mainGridLayout->addWidget(label,row++,0);

    m_opticalDataType = new OSComboBox();
    m_opticalDataType->addItem("Spectral Average");
    m_opticalDataType->addItem("Spectral");
    mainGridLayout->addWidget(m_opticalDataType,row++,0,1,3);

    // Window Glass Spectral Data Set Name

    label = new QLabel("Window Glass Spectral Data Set Name: ");
    label->setObjectName("H2");
    mainGridLayout->addWidget(label,row++,0);

    m_windowGlassSpectralDataSetName = new OSLineEdit();
    mainGridLayout->addWidget(m_windowGlassSpectralDataSetName,row++,0,1,3);

    // Thickness

    label = new QLabel("Thickness: ");
    label->setObjectName("H2");
    mainGridLayout->addWidget(label,row++,0);

    m_thickness = new OSQuantityEdit(m_isIP);
    connect(this, &WindowMaterialGlazingInspectorView::toggleUnitsClicked, m_thickness, &OSQuantityEdit::onUnitSystemChange);
    mainGridLayout->addWidget(m_thickness,row++,0,1,3);

    // Solar Transmittance At Normal Incidence

    label = new QLabel("Solar Transmittance At Normal Incidence: ");
    label->setObjectName("H2");
    mainGridLayout->addWidget(label,row++,0);

    m_solarTransmittanceAtNormalIncidence = new OSQuantityEdit(m_isIP);
    connect(this, &WindowMaterialGlazingInspectorView::toggleUnitsClicked, m_solarTransmittanceAtNormalIncidence, &OSQuantityEdit::onUnitSystemChange);
    mainGridLayout->addWidget(m_solarTransmittanceAtNormalIncidence,row++,0,1,3);

    // Front Side Solar Reflectance At Normal Incidence

    label = new QLabel("Front Side Solar Reflectance At Normal Incidence: ");
    label->setObjectName("H2");
    mainGridLayout->addWidget(label,row++,0);

    m_frontSideSolarReflectanceAtNormalIncidence = new OSQuantityEdit(m_isIP);
    connect(this, &WindowMaterialGlazingInspectorView::toggleUnitsClicked, m_frontSideSolarReflectanceAtNormalIncidence, &OSQuantityEdit::onUnitSystemChange);
    mainGridLayout->addWidget(m_frontSideSolarReflectanceAtNormalIncidence,row++,0,1,3);

    // Back Side Solar Reflectance At Normal Incidence

    label = new QLabel("Back Side Solar Reflectance At Normal Incidence: ");
    label->setObjectName("H2");
    mainGridLayout->addWidget(label,row++,0);

    m_backSideSolarReflectanceAtNormalIncidence = new OSQuantityEdit(m_isIP);
    connect(this, &WindowMaterialGlazingInspectorView::toggleUnitsClicked, m_backSideSolarReflectanceAtNormalIncidence, &OSQuantityEdit::onUnitSystemChange);
    mainGridLayout->addWidget(m_backSideSolarReflectanceAtNormalIncidence,row++,0,1,3);

    // Visible Transmittance At Normal Incidence

    label = new QLabel("Visible Transmittance At Normal Incidence: ");
    label->setObjectName("H2");
    mainGridLayout->addWidget(label,row++,0);

    m_visibleTransmittanceAtNormalIncidence = new OSQuantityEdit(m_isIP);
    connect(this, &WindowMaterialGlazingInspectorView::toggleUnitsClicked, m_visibleTransmittanceAtNormalIncidence, &OSQuantityEdit::onUnitSystemChange);
    mainGridLayout->addWidget(m_visibleTransmittanceAtNormalIncidence,row++,0,1,3);

    // Front Side Visible Reflectance At Normal Incidence

    label = new QLabel("Front Side Visible Reflectance At Normal Incidence: ");
    label->setObjectName("H2");
    mainGridLayout->addWidget(label,row++,0);

    m_frontSideVisibleReflectanceAtNormalIncidence = new OSQuantityEdit(m_isIP);
    connect(this, &WindowMaterialGlazingInspectorView::toggleUnitsClicked, m_frontSideVisibleReflectanceAtNormalIncidence, &OSQuantityEdit::onUnitSystemChange);
    mainGridLayout->addWidget(m_frontSideVisibleReflectanceAtNormalIncidence,row++,0,1,3);

    // Back Side Visible Reflectance At Normal Incidence

    label = new QLabel("Back Side Visible Reflectance At Normal Incidence: ");
    label->setObjectName("H2");
    mainGridLayout->addWidget(label,row++,0);

    m_backSideVisibleReflectanceAtNormalIncidence = new OSQuantityEdit(m_isIP);
    connect(this, &WindowMaterialGlazingInspectorView::toggleUnitsClicked, m_backSideVisibleReflectanceAtNormalIncidence, &OSQuantityEdit::onUnitSystemChange);
    mainGridLayout->addWidget(m_backSideVisibleReflectanceAtNormalIncidence,row++,0,1,3);

    // Infrared Transmittance at Normal Incidence

    label = new QLabel("Infrared Transmittance at Normal Incidence: ");
    label->setObjectName("H2");
    mainGridLayout->addWidget(label,row++,0);

    m_infraredTransmittanceAtNormalIncidence = new OSQuantityEdit(m_isIP);
    connect(this, &WindowMaterialGlazingInspectorView::toggleUnitsClicked, m_infraredTransmittanceAtNormalIncidence, &OSQuantityEdit::onUnitSystemChange);
    mainGridLayout->addWidget(m_infraredTransmittanceAtNormalIncidence,row++,0,1,3);

    // Front Side Infrared Hemispherical Emissivity

    label = new QLabel("Front Side Infrared Hemispherical Emissivity: ");
    label->setObjectName("H2");
    mainGridLayout->addWidget(label,row++,0);

    m_frontSideInfraredHemisphericalEmissivity = new OSQuantityEdit(m_isIP);
    connect(this, &WindowMaterialGlazingInspectorView::toggleUnitsClicked, m_frontSideInfraredHemisphericalEmissivity, &OSQuantityEdit::onUnitSystemChange);
    mainGridLayout->addWidget(m_frontSideInfraredHemisphericalEmissivity,row++,0,1,3);

    // Back Side Infrared Hemispherical Emissivity

    label = new QLabel("Back Side Infrared Hemispherical Emissivity: ");
    label->setObjectName("H2");
    mainGridLayout->addWidget(label,row++,0);

    m_backSideInfraredHemisphericalEmissivity = new OSQuantityEdit(m_isIP);
    connect(this, &WindowMaterialGlazingInspectorView::toggleUnitsClicked, m_backSideInfraredHemisphericalEmissivity, &OSQuantityEdit::onUnitSystemChange);
    mainGridLayout->addWidget(m_backSideInfraredHemisphericalEmissivity,row++,0,1,3);

    // Conductivity

    label = new QLabel("Conductivity: ");
    label->setObjectName("H2");
    mainGridLayout->addWidget(label,row++,0);

    m_conductivity = new OSQuantityEdit(m_isIP);
    connect(this, &WindowMaterialGlazingInspectorView::toggleUnitsClicked, m_conductivity, &OSQuantityEdit::onUnitSystemChange);
    mainGridLayout->addWidget(m_conductivity,row++,0,1,3);

    // Dirt Correction Factor For Solar And Visible Transmittance

    label = new QLabel("Dirt Correction Factor For Solar And Visible Transmittance: ");
    label->setObjectName("H2");
    mainGridLayout->addWidget(label,row++,0);

    m_dirtCorrectionFactorForSolarAndVisibleTransmittance = new OSQuantityEdit(m_isIP);
    connect(this, &WindowMaterialGlazingInspectorView::toggleUnitsClicked, m_dirtCorrectionFactorForSolarAndVisibleTransmittance, &OSQuantityEdit::onUnitSystemChange);
    mainGridLayout->addWidget(m_dirtCorrectionFactorForSolarAndVisibleTransmittance,row++,0,1,3);

    // Solar Diffusing

    label = new QLabel("Solar Diffusing: ");
    label->setObjectName("H2");
    mainGridLayout->addWidget(label,row++,0);

    m_solarDiffusing = new OSSwitch();
    mainGridLayout->addWidget(m_solarDiffusing,row++,0,1,3);

    // Stretch

    mainGridLayout->setRowStretch(100,100);

    mainGridLayout->setColumnStretch(100,100);
}