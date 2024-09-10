ToolsDockWidget::ToolsDockWidget(QWidget * parent) :
    QDockWidget(i18n("Tools"),parent),
//    m_has_selection(false),
    m_current_item(0),
    m_scene(0),
    d(new ToolsDockWidgetPrivate)
{
    this->setFeatures(QDockWidget::DockWidgetMovable);
    this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QWidget * widget = new QWidget(this);
    QVBoxLayout * layout = new QVBoxLayout(widget);
    //layout->setSizeConstraint(QLayout::SetMinimumSize);

    // tools buttons layout
    d->formLayout = new QGridLayout();
    //formLayout->setSizeConstraint(QLayout::SetMinimumSize);
    layout->addLayout(d->formLayout);

    // stacked widget (with tools widgets)
    d->toolArea = new QScrollArea(widget);
    //sa->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    d->toolArea->setFrameShape(QFrame::NoFrame);
    d->toolArea->setWidgetResizable(true);
    d->toolArea->setWidget(0);
    layout->addWidget(d->toolArea,1);

    QButtonGroup * group = new QButtonGroup(widget);

    // Selection tool

    m_tool_pointer = new KPushButton(KGuiItem("",":/pointer.png",
                                              i18n("Allows to select and move images on canvas"),
                                              i18n("Tool which allows one to select and move images on canvas. Any other operations are disabled.")), widget);
    m_tool_pointer->setIconSize(QSize(24,24));
    m_tool_pointer->setFixedSize(32,32);
    m_tool_pointer->setCheckable(true);
    m_tool_pointer->setFlat(true);
    group->addButton(m_tool_pointer);
    connect(m_tool_pointer,SIGNAL(toggled(bool)),this,SLOT(setPointerToolVisible(bool)));

    // View tool
    m_tool_hand = new KPushButton(KGuiItem("",":/hand.png",
                                           i18n("Viewing tool"),
                                           i18n("This tool allows one to view whole canvas in read-only mode. Only scrolling and zooming are available.")), widget);
    m_tool_hand->setIconSize(QSize(24,24));
    m_tool_hand->setFixedSize(32,32);
    m_tool_hand->setCheckable(true);
    m_tool_hand->setFlat(true);
    group->addButton(m_tool_hand);
    connect(m_tool_hand,SIGNAL(toggled(bool)),this,SLOT(setHandToolVisible(bool)));

    // Zoom tool
    m_tool_zoom = new KPushButton(KGuiItem("",":/zoom.png",
                                           i18n("Zooming tool"),
                                           i18n("This tool allows one to zoom canvas to fit it to the application window or users preferences.")), widget);
    m_tool_zoom->setIconSize(QSize(24,24));
    m_tool_zoom->setFixedSize(32,32);
    m_tool_zoom->setCheckable(true);
    m_tool_zoom->setFlat(true);
    group->addButton(m_tool_zoom);
    connect(m_tool_zoom,SIGNAL(toggled(bool)),this,SLOT(setZoomWidgetVisible(bool)));

    // Canvas edit tool
    m_canvas_button = new KPushButton(KGuiItem("", ":/tool_canvas.png",
                                               i18n("Canvas editor"),
                                               i18n("This tool allows you to edit canvas properties like size and background.")), widget);
    m_canvas_button->setIconSize(QSize(24,24));
    m_canvas_button->setFixedSize(32,32);
    m_canvas_button->setCheckable(true);
    m_canvas_button->setFlat(true);
    group->addButton(m_canvas_button);
    connect(m_canvas_button,SIGNAL(toggled(bool)),this,SLOT(setCanvasWidgetVisible(bool)));

    // Text tool
    m_text_button = new KPushButton(KGuiItem("", ":/tool_text.png",
                                              i18n("Text editor"),
                                              i18n("This tool allows you to write text on the canvas. It's simple - just click on the canvas where you want to add some text and write it!")), widget);

    m_text_button->setIconSize(QSize(24,24));
    m_text_button->setFixedSize(32,32);
    m_text_button->setCheckable(true);
    m_text_button->setFlat(true);
    group->addButton(m_text_button);
    connect(m_text_button,SIGNAL(toggled(bool)),this,SLOT(setTextWidgetVisible(bool)));

    // Rotate tool
    m_rotate_button = new KPushButton(KGuiItem("", ":/tool_rotate.png",
                                              i18n("Rotation tool"),
                                              i18n("This tool allows you to rotate items on your canvas.")), widget);
    m_rotate_button->setIconSize(QSize(24,24));
    m_rotate_button->setFixedSize(32,32);
    m_rotate_button->setCheckable(true);
    m_rotate_button->setFlat(true);
    group->addButton(m_rotate_button);
    connect(m_rotate_button,SIGNAL(toggled(bool)),this,SLOT(setRotateWidgetVisible(bool)));

    // Scale tool
    m_scale_button = new KPushButton(KGuiItem("", ":/tool_scale4.png",
                                              i18n("Scaling tool"),
                                              i18n("This tool allows you to scale items on your canvas.")), widget);
    m_scale_button->setIconSize(QSize(24,24));
    m_scale_button->setFixedSize(32,32);
    m_scale_button->setCheckable(true);
    m_scale_button->setFlat(true);
    group->addButton(m_scale_button);
    connect(m_scale_button,SIGNAL(toggled(bool)),this,SLOT(setScaleWidgetVisible(bool)));

    // Crop tool
    m_crop_button = new KPushButton(KGuiItem("", ":/tool_cropt.png",
                                              i18n("Crop tool"),
                                              i18n("This tool allows you to crop items.")), widget);
    m_crop_button->setIconSize(QSize(24,24));
    m_crop_button->setFixedSize(32,32);
    m_crop_button->setCheckable(true);
    m_crop_button->setFlat(true);
    group->addButton(m_crop_button);
    connect(m_crop_button,SIGNAL(toggled(bool)),this,SLOT(setCropWidgetVisible(bool)));

    // Photo effects tool
    m_effects_button = new KPushButton(KGuiItem("", ":/tool_effects.png",
                                              i18n("Image effects editor"),
                                              i18n("This tool allows you to edit existing effects of your photo layers and add some new one.")), widget);
    m_effects_button->setIconSize(QSize(24,24));
    m_effects_button->setFixedSize(32,32);
    m_effects_button->setCheckable(true);
    m_effects_button->setFlat(true);
    group->addButton(m_effects_button);
    connect(m_effects_button,SIGNAL(toggled(bool)),this,SLOT(setEffectsWidgetVisible(bool)));

    // Border edit tool
    m_tool_border = new KPushButton(QIcon::fromTheme(":/tool_border.png"), "", widget);
    m_tool_border->setIconSize(QSize(24,24));
    m_tool_border->setFixedSize(32,32);
    m_tool_border->setCheckable(true);
    m_tool_border->setFlat(true);
    group->addButton(m_tool_border);
    connect(m_tool_border,SIGNAL(toggled(bool)),this,SLOT(setBordersWidgetVisible(bool)));

    // Spacer
    d->formLayout->setSpacing(0);
    d->formLayout->setMargin(0);

    layout->setSpacing(0);
    layout->setMargin(0);
    widget->setLayout(layout);
    //widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    this->setWidget(widget);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    this->setMinimumWidth(235);

    setDefaultTool();
}