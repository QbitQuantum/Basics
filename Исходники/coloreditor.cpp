ColorEditor::ColorEditor(QWidget *parent) :
    QFrame(parent),
    d(new ColorEditorImpl(this))
{
    setFocusPolicy(Qt::StrongFocus);
    setFrameShape(QFrame::StyledPanel);
    setCursor(QCursor(Qt::ArrowCursor));

    // Build UI
    // Close button
    auto closeBtn = new QToolButton(this);
    closeBtn->setFixedSize(24, 24);
    closeBtn->setIcon(QIcon(QLatin1String(Core::Constants::ICON_BUTTON_CLOSE)));

    connect(closeBtn, &QToolButton::clicked,
            this, &ColorEditor::close);

    // Color format selection
    d->rgbBtn->setText(QLatin1String("rgb"));
    d->hsvBtn->setText(QLatin1String("hsv"));
    d->hslBtn->setText(QLatin1String("hsl"));
    d->qmlRgbaBtn->setText(QLatin1String("Qt.rgba"));
    d->qmlHslaBtn->setText(QLatin1String("Qt.hsla"));
    d->vecBtn->setText(QLatin1String("vec"));
    d->hexBtn->setText(QLatin1String("hex"));

    d->rgbBtn->setCheckable(true);
    d->hsvBtn->setCheckable(true);
    d->hslBtn->setCheckable(true);
    d->qmlRgbaBtn->setCheckable(true);
    d->qmlHslaBtn->setCheckable(true);
    d->vecBtn->setCheckable(true);
    d->hexBtn->setCheckable(true);

    // Build layouts
    d->formatsLayout->setSpacing(0);

    d->colorFrame->setMinimumSize(QSize(30, 35));

    auto rightLayout = new QVBoxLayout;
    rightLayout->addWidget(d->colorFrame);
    rightLayout->addStretch();

    auto leftPanelLayout = new QVBoxLayout;
    leftPanelLayout->addWidget(closeBtn);
    leftPanelLayout->addStretch();

    auto *colorWidgetsLayout = new QHBoxLayout;
    colorWidgetsLayout->addWidget(d->colorPicker);
    colorWidgetsLayout->addWidget(d->hueSlider);
    colorWidgetsLayout->addWidget(d->saturationSlider);
    colorWidgetsLayout->addWidget(d->valueSlider);
    colorWidgetsLayout->addWidget(d->opacitySlider);
    colorWidgetsLayout->addLayout(rightLayout);

    auto *centerLayout = new QVBoxLayout;
    centerLayout->addLayout(colorWidgetsLayout);
    centerLayout->addLayout(d->formatsLayout);

    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(leftPanelLayout);
    mainLayout->addSpacing(0);
    mainLayout->addLayout(centerLayout);

    // Color format selection logic
    d->btnGroup->addButton(d->rgbBtn);
    d->btnGroup->addButton(d->hsvBtn);
    d->btnGroup->addButton(d->hslBtn);
    d->btnGroup->addButton(d->qmlRgbaBtn);
    d->btnGroup->addButton(d->qmlHslaBtn);
    d->btnGroup->addButton(d->vecBtn);
    d->btnGroup->addButton(d->hexBtn);

    connect(d->btnGroup, static_cast<void (QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
            [=] (QAbstractButton *btn) {
        ColorFormat format;

        if (btn == d->rgbBtn) {
            format = ColorFormat::QCssRgbUCharFormat;
        }
        else if (btn == d->hsvBtn) {
            format = ColorFormat::QssHsvFormat;
        }
        else if (btn == d->hslBtn) {
            format = ColorFormat::CssHslFormat;
        }
        else if (btn == d->qmlRgbaBtn) {
            format = ColorFormat::QmlRgbaFormat;
        }
        else if (btn == d->qmlHslaBtn) {
            format = ColorFormat::QmlHslaFormat;
        }
        else if (btn == d->vecBtn) {
            format = ColorFormat::GlslFormat;
        }
        else if (btn == d->hexBtn)
            format = ColorFormat::HexFormat;

        d->setCurrentFormat(format);
    });

    // Color changes logic
    connect(d->colorPicker, &ColorPickerWidget::colorChanged,
            [=](const QColor &pureColor) {
        QColor newColor(pureColor);
        newColor.setAlpha(d->opacitySlider->value());

        d->updateColorWidgets(newColor, ColorEditorImpl::UpdateFromColorPicker);
        d->setCurrentColor(newColor);
    });

    connect(d->hueSlider, &HueSlider::valueChanged,
            [=](int hue) {
        QColor newColor = QColor::fromHsv(hue,
                                          d->color.hsvSaturation(),
                                          d->color.value(),
                                          d->opacitySlider->value());

        d->updateColorWidgets(newColor,
                              ColorEditorImpl::UpdateFromHueSlider);
        d->setCurrentColor(newColor);
    });

    connect(d->saturationSlider, &SaturationSlider::valueChanged,
            [=](int sat) {
        QColor newColor = QColor::fromHsv(d->color.hsvHue(),
                                          sat,
                                          d->color.value(),
                                          d->opacitySlider->value());

        d->updateColorWidgets(newColor,
                              ColorEditorImpl::UpdateFromSaturationSlider);
        d->setCurrentColor(newColor);
    });

    connect(d->valueSlider, &ValueSlider::valueChanged,
            [=](int val) {
        QColor newColor = QColor::fromHsv(d->color.hsvHue(),
                                          d->color.hsvSaturation(),
                                          val,
                                          d->opacitySlider->value());

        d->updateColorWidgets(newColor,
                              ColorEditorImpl::UpdateFromValueSlider);
        d->setCurrentColor(newColor);
    });


    connect(d->opacitySlider, &OpacitySlider::valueChanged,
            [=](int opacity) {
        QColor newColor = QColor::fromHsv(d->hueSlider->value(),
                                          d->color.hsvSaturation(),
                                          d->color.value(),
                                          opacity);

        d->updateColorWidgets(newColor,
                              ColorEditorImpl::UpdateFromOpacitySlider);
        d->setCurrentColor(newColor);
    });

    setColorCategory(ColorCategory::AnyCategory);
    setOutputFormat(ColorFormat::QCssRgbUCharFormat);
    setColor(Qt::red);
}