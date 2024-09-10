ListItem::ListItem(Container* parent) :
    CustomControl(parent)
{
    // Dock layout with margins inside.
    Container* itemContainer = new Container();
    DockLayout* itemLayout = new DockLayout();
    itemContainer->setLayout(itemLayout);
    itemContainer->setPreferredWidth(250.0f);

    // A background Container that will hold a background image and an item content Container.
    Container* backgroundContainer = new Container();
    DockLayout* backgroundLayout = new DockLayout();
    backgroundContainer->setLayout(backgroundLayout);
    backgroundContainer->setHorizontalAlignment(HorizontalAlignment::Center);
    backgroundContainer->setVerticalAlignment(VerticalAlignment::Center);

    // A Colored Container will be used to show if an item is highlighted.
    m_highlighContainer = new Container();
    m_highlighContainer->setBackground(Color::fromARGB(0xff75b5d3));
    m_highlighContainer->setHorizontalAlignment(HorizontalAlignment::Center);
    m_highlighContainer->setVerticalAlignment(VerticalAlignment::Center);
    m_highlighContainer->setOpacity(0.0);
    m_highlighContainer->setPreferredWidth(242.0f);
    m_highlighContainer->setPreferredHeight(168.0f);

    // Content Container, Image + text with padding to get alignment on background image.
    Container* contentContainer = new Container();
    DockLayout* contentLayout = new DockLayout();
    contentContainer->setLayout(contentLayout);
    contentContainer->setHorizontalAlignment(HorizontalAlignment::Center);
    contentContainer->setVerticalAlignment(VerticalAlignment::Center);

    // The list item image, docked to the top, the actual image is set in updateItem.
    m_itemImage = ImageView::create("asset:///images/white_photo.png").preferredSize(238.0f, 160.0f);
    m_itemImage->setHorizontalAlignment(HorizontalAlignment::Center);
    m_itemImage->setVerticalAlignment(VerticalAlignment::Center);

    // A list item label, docked to the center, the text is set in updateItem.
    m_itemLabel = Label::create().text(" ");
    m_itemLabel->setHorizontalAlignment(HorizontalAlignment::Center);
    m_itemLabel->setVerticalAlignment(VerticalAlignment::Center);
    m_itemLabel->textStyle()->setBase(SystemDefaults::TextStyles::titleText());
    m_itemLabel->textStyle()->setColor(Color::Black);

    // Add the Label to the content.
    contentContainer->add(m_itemLabel);

    // Add the background image and the content to the background item container.
    backgroundContainer->add(m_itemImage);
    backgroundContainer->add(m_highlighContainer);
    backgroundContainer->add(contentContainer);

    // Finally add the background Container to the item Container.
    itemContainer->add(backgroundContainer);

    setRoot(itemContainer);
}