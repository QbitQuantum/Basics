Ui::CallPanelMain::CallPanelMain(QWidget* parent)
    : QWidget(parent)
    , _menu(NULL)
    , actual_vol_(0)
    , menu_show_(NULL)
    , name_and_status_container_(NULL)
    , avatar_container_(NULL) {

        setProperty("CallPanelMain", true);

        QVBoxLayout* root_layout = new QVBoxLayout();
        root_layout->setContentsMargins(0, 0, 0, 0);
        root_layout->setSpacing(0);
        root_layout->setAlignment(Qt::AlignVCenter);
        setLayout(root_layout);

        QWidget* rootWidget = new QWidget(this);
        rootWidget->setContentsMargins(0, 0, 0, 0);
        rootWidget->setProperty("CallPanelMain", true);
        layout()->addWidget(rootWidget);

        QHBoxLayout* layout = new QHBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        layout->setAlignment(Qt::AlignVCenter);
        rootWidget->setLayout(layout);

        avatar_container_ = new AvatarContainerWidget(rootWidget, Utils::scale_value(50), Utils::scale_value(16), Utils::scale_value(12), Utils::scale_value(5));
        avatar_container_->setOverlap(0.6f);
        layout->addWidget(avatar_container_);

        name_and_status_container_ = new NameAndStatusWidget(rootWidget, Utils::scale_value(17), Utils::scale_value(12));
        name_and_status_container_->setNameProperty("CallPanelMainText_Name", true);
        name_and_status_container_->setStatusProperty("CallPanelMainText_Status", true);
        name_and_status_container_->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));
        layout->addWidget(name_and_status_container_);

        layout->addSpacing(Utils::scale_value(6));

        menu_show_ = new QPushButton(rootWidget);
        menu_show_->setProperty("MenuShow", true);
		menu_show_->setCursor(QCursor(Qt::PointingHandCursor));
        connect(menu_show_, SIGNAL(clicked()), this, SLOT(onMenuButtonClicked()), Qt::QueuedConnection);
        layout->addWidget(menu_show_);

        layout->addSpacing(Utils::scale_value(24));

        QPushButton* callStop = new QPushButton(rootWidget);
        callStop->setProperty("StopCallMainButton", true);
		callStop->setCursor(QCursor(Qt::PointingHandCursor));
        connect(callStop, SIGNAL(clicked()), this, SLOT(onHangUpButtonClicked()), Qt::QueuedConnection);
        layout->addWidget(callStop);

        layout->addSpacing(Utils::scale_value(16));
        connect(&_menu, SIGNAL(onMenuOpenChanged(bool)), this, SLOT(onMenuOpenChanged(bool)), Qt::QueuedConnection);
        _menu.hide();

        QObject::connect(&Ui::GetDispatcher()->getVoipController(), SIGNAL(onVoipCallNameChanged(const std::vector<voip_manager::Contact>&)), this, SLOT(onVoipCallNameChanged(const std::vector<voip_manager::Contact>&)), Qt::DirectConnection);
        QObject::connect(&Ui::GetDispatcher()->getVoipController(), SIGNAL(onVoipCallDestroyed(const voip_manager::ContactEx&)), this, SLOT(onVoipCallDestroyed(const voip_manager::ContactEx&)), Qt::DirectConnection);
        QObject::connect(&Ui::GetDispatcher()->getVoipController(), SIGNAL(onVoipVolumeChanged(const std::string&,int)), this, SLOT(onVoipVolumeChanged(const std::string&,int)), Qt::DirectConnection);
        QObject::connect(&Ui::GetDispatcher()->getVoipController(), SIGNAL(onVoipMuteChanged(const std::string&,bool)), this, SLOT(onVoipMuteChanged(const std::string&,bool)), Qt::DirectConnection);
        QObject::connect(&Ui::GetDispatcher()->getVoipController(), SIGNAL(onVoipMediaLocalAudio(bool)), this, SLOT(onVoipMediaLocalAudio(bool)), Qt::DirectConnection);
        QObject::connect(&Ui::GetDispatcher()->getVoipController(), SIGNAL(onVoipMediaLocalVideo(bool)), this, SLOT(onVoipMediaLocalVideo(bool)), Qt::DirectConnection);
		QObject::connect(&Ui::GetDispatcher()->getVoipController(), SIGNAL(onVoipCallTimeChanged(unsigned,bool)), this, SLOT(onVoipCallTimeChanged(unsigned,bool)), Qt::DirectConnection);

        {
            SliderEx* slider = new SliderEx(&_menu);
            slider->setProperty("CallMenuItemCommon", true);
            slider->set_property_for_slider("VideoPanelVolumeSlider", true);
            slider->set_property_for_icon("CallMenuItemButton", true);

            _menu.add_widget(kmenu_item_volume, slider);
            connect(slider, SIGNAL(onSliderValueChanged(int)), this, SLOT(onVolumeChanged(int)), Qt::QueuedConnection);
            connect(slider, SIGNAL(onSliderReleased()), this, SLOT(onVolumeReleased()), Qt::QueuedConnection);
            connect(slider, SIGNAL(onIconClick()), this, SLOT(onVolumeOnOff()), Qt::QueuedConnection);
        }
        
        {
            QPushButton* btn = new QPushButton(&_menu);
            btn->setProperty("CallMenuItemCommon", true);
            btn->setProperty("CallMenuItemButton", true);
			btn->setCursor(QCursor(Qt::PointingHandCursor));
            _menu.add_widget(kmenu_item_mic, btn);
            connect(btn, SIGNAL(clicked()), this, SLOT(onMuteMicOnOffClicked()), Qt::QueuedConnection);
        }
        
        {
            QPushButton* btn = new QPushButton(&_menu);
            btn->setProperty("CallMenuItemCommon", true);
            btn->setProperty("CallMenuItemButton", true);
			btn->setCursor(QCursor(Qt::PointingHandCursor));
            _menu.add_widget(kmenu_item_cam, btn);
            connect(btn, SIGNAL(clicked()), this, SLOT(onVideoOnOffClicked()), Qt::QueuedConnection);
        }
}