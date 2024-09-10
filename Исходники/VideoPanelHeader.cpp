Ui::VideoPanelHeader::VideoPanelHeader(QWidget* _parent, int _items)
    : MoveablePanel(_parent)
    , itemsToShow_(_items)
    , callName_(nullptr)
    , callTime_(nullptr)
    , btnMin_(nullptr)
    , btnClose_(nullptr)
    , lowWidget_(nullptr)
    , secureCallEnabled_(false)
{
#ifdef __linux__
    setStyleSheet(Utils::LoadStyle(":/qss/video_panel_linux"));
#else
    setStyleSheet(Utils::LoadStyle(":/qss/video_panel"));
#endif
    setProperty("VideoPanelHeader", true);
    setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* layout = Utils::emptyHLayout();
    lowWidget_ = new QFrame(this);
    { // low widget. it makes background panel coloured
        lowWidget_->setContentsMargins(DEFAULT_BORDER, 0, 0, 0);
#ifdef __APPLE__
        lowWidget_->setProperty("VideoPanelHeaderMac", true);
#else
        lowWidget_->setProperty("VideoPanelHeader", true);
#endif

        lowWidget_->setLayout(layout);

        QVBoxLayout* vLayoutParent = Utils::emptyVLayout();
        vLayoutParent->setAlignment(Qt::AlignVCenter);
        vLayoutParent->addWidget(lowWidget_);
        setLayout(vLayoutParent);

        layout->setAlignment(Qt::AlignVCenter);

        //layout->addSpacing(DEFAULT_BORDER);
    }

    auto addWidget = [] (QWidget* _parent)
    {
        QWidget* w = new QWidget(_parent);
        w->setContentsMargins(0, 0, 0, 0);
        w->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        return w;
    };

    auto addLayout = [] (QWidget* _w, Qt::Alignment _align)
    {
        assert(_w);
        if (_w)
        {
            QHBoxLayout* layout = Utils::emptyHLayout();
            layout->setAlignment(_align);
            _w->setLayout(layout);
        }
    };

    QWidget* leftWidg    = addWidget(lowWidget_);
    QWidget* centerWidg  = addWidget(lowWidget_);
    QWidget* rightWidg   = addWidget(lowWidget_);

    layout->addWidget(leftWidg, 1);
    layout->addWidget(centerWidg);
    layout->addWidget(rightWidg, 1);

    addLayout(leftWidg,   Qt::AlignLeft | Qt::AlignVCenter);
    addLayout(centerWidg, Qt::AlignCenter);
    addLayout(rightWidg,  Qt::AlignRight | Qt::AlignVCenter);

    QFont font = QApplication::font();
    font.setStyleStrategy(QFont::PreferAntialias);
    if (itemsToShow_ & kVPH_ShowName)
    {
        callName_ = new NameWidget(leftWidg, Utils::scale_value(18));
        callName_->setFont(font);
        callName_->layout()->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        callName_->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding));
        callName_->setNameProperty("VideoPanelHeaderText", true);

        leftWidg->layout()->addWidget(callName_);
    }

    if (itemsToShow_ & kVPH_ShowTime)
    {
        callTime_ = new voipTools::BoundBox<PushButton_t>(centerWidg);
        callTime_->setPostfixColor(CommonStyle::getColor(CommonStyle::Color::TEXT_PRIMARY));
        callTime_->setFont(font);
        callTime_->setEnabled(false);
        callTime_->setAlignment(Qt::AlignCenter);
        callTime_->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding));
        callTime_->setFixedWidth(SECURE_BTN_TEXT_W);
        callTime_->setIconSize(SECURE_BTN_ICON_W, SECURE_BTN_ICON_H);

        QObject::connect(callTime_, SIGNAL(clicked()), this, SLOT(_onSecureCallClicked()), Qt::QueuedConnection);
        Utils::ApplyStyle(callTime_, secureCallButton);
        centerWidg->layout()->addWidget(callTime_);
    }

    QWidget* parentWidget = rightWidg;
    auto addButton = [this, parentWidget] (const QString& _propertyName, const char* _slot)->QPushButton*
    {
        QPushButton* btn = new voipTools::BoundBox<QPushButton>(parentWidget);

        Utils::ApplyStyle(btn, _propertyName);
        btn->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding));
        btn->setCursor(QCursor(Qt::PointingHandCursor));
        btn->setFlat(true);
        parentWidget->layout()->addWidget(btn);
        connect(btn, SIGNAL(clicked()), this, _slot, Qt::QueuedConnection);
        return btn;
    };
    if (itemsToShow_ & kVPH_ShowMin)
    {
        btnMin_ = addButton(CommonStyle::getMinimizeButtonStyle(), SLOT(_onMinimize()));
    }

    if (itemsToShow_ & kVPH_ShowClose)
    {
        btnClose_ = addButton(CommonStyle::getCloseButtonStyle(), SLOT(_onClose()));
    }
}