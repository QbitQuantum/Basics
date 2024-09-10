void KbLayoutWidget::initUI() {
    setObjectName("KeyboardLayoutFrame");
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSelectionMode(QAbstractItemView::NoSelection);
    setResizeMode(Adjust);

    for (int i = 0; i < m_buttons.length(); i++) {
        LayoutButton* itemButton = new LayoutButton(m_buttons[i]);
        m_layoutButtons.append(itemButton);
        itemButton->setFixedSize(widget_width, DDESESSIONCC::LAYOUTBUTTON_HEIGHT);

        QFrame* borderFrame = new QFrame;
        borderFrame->setObjectName("LayoutBorderFrame");
        QVBoxLayout* borderLayout = new QVBoxLayout;
        borderLayout->setContentsMargins(0, 0, 0, 0);
        borderLayout->setSpacing(0);
        borderLayout->addWidget(itemButton);
        borderFrame->setLayout(borderLayout);
        borderFrame->setFixedSize(widget_width, DDESESSIONCC::LAYOUTBUTTON_HEIGHT);

        QListWidgetItem* item = new QListWidgetItem(this);
        item->sizeHint();
        this->addItem(item);
        setItemWidget(item,  borderFrame);
        this->setGridSize(QSize(widget_width, DDESESSIONCC::LAYOUTBUTTON_HEIGHT));
        this->setFixedWidth(widget_width);
    }
    this->setFixedHeight(DDESESSIONCC::LAYOUTBUTTON_HEIGHT*3);



    updateStyle(":/skin/keybdlayoutwidget.qss", this);
}