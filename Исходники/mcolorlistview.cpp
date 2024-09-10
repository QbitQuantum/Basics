MColorListViewPrivate::MColorListViewPrivate(MColorListView *p, MColorList *controller)
    : q_ptr(p), controller(controller), landscapePolicy(0), portraitPolicy(0), buttonGroup(0)
{
    QGraphicsGridLayout *layout = new QGraphicsGridLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    controller->setLayout(layout);

    MStylableWidget* container = new MStylableWidget();
    container->setStyleName("ColorSelectionContainer");
    MLayout *containerLayout = new MLayout();
    container->setLayout(containerLayout);

    landscapePolicy = new MGridLayoutPolicy(containerLayout);
    landscapePolicy->setContentsMargins(0, 0, 0, 0);
    landscapePolicy->setSpacing(0);
    containerLayout->setLandscapePolicy(landscapePolicy);

    portraitPolicy = new MGridLayoutPolicy(containerLayout);
    portraitPolicy->setContentsMargins(0, 0, 0, 0);
    portraitPolicy->setSpacing(0);
    containerLayout->setPortraitPolicy(portraitPolicy);

    layout->addItem(container, 0, 0);

    // Current color list
    colors << QColor(0x95, 0xE8, 0x5D);
    colors << QColor(0x73, 0xC0, 0xF5);
    colors << QColor(0xCB, 0xA4, 0xDE);
    colors << QColor(0xE9, 0x48, 0xA3);
    colors << QColor(0xFF, 0x9E, 0x9E);
    colors << QColor(0xFF, 0xF6, 0x57);
    colors << QColor(0x9C, 0x9C, 0x9C);

    colors << QColor(0x74, 0xD9, 0x41);
    colors << QColor(0x31, 0xB0, 0xDE);
    colors << QColor(0xBC, 0x79, 0xDE);
    colors << QColor(0xE9, 0x48, 0xA3);
    colors << QColor(0xFF, 0x79, 0x4D);
    colors << QColor(0xFB, 0xFF, 0x14);
    colors << QColor(0x80, 0x80, 0x80);

    colors << QColor(0x55, 0xD5, 0x00);
    colors << QColor(0x00, 0x88, 0xE6);
    colors << QColor(0xAE, 0x4E, 0xDE);
    colors << QColor(0xE9, 0x48, 0xA3);
    colors << QColor(0xFF, 0x40, 0x00);
    colors << QColor(0xFF, 0xE6, 0x00);
    colors << QColor(0x4D, 0x4D, 0x4D);

    colors << QColor(0x45, 0x90, 0x27);
    colors << QColor(0x00, 0x6F, 0xBA);
    colors << QColor(0x89, 0x3D, 0xAF);
    colors << QColor(0xE9, 0x48, 0xA3);
    colors << QColor(0xCC, 0x33, 0x00);
    colors << QColor(0xFF, 0x90, 0x00);
    colors << QColor(0x33, 0x33, 0x33);

    colors << QColor(0x00, 0x73, 0x00);
    colors << QColor(0x00, 0x41, 0x82);
    colors << QColor(0x5E, 0x2A, 0x78);
    colors << QColor(0xE9, 0x48, 0xA3);
    colors << QColor(0xB5, 0x2D, 0x00);
    colors << QColor(0xFF, 0x6A, 0x00);
    colors << QColor(0x1A, 0x1A, 0x1A);
}