EclListItem::EclListItem(Container *parent) :
        CustomControl(parent), m_itemImage(0), m_listItem(0), m_highlightContainer(0) {

    Container *itemContainer = new Container();
    DockLayout *itemLayout = new DockLayout();
    itemContainer->setLayout(itemLayout);

    m_listItem = new StandardListItem();
    Container *imageContainer = new Container();
    imageContainer->setRightPadding(20);
    imageContainer->setHorizontalAlignment(HorizontalAlignment::Right);
    imageContainer->setVerticalAlignment(VerticalAlignment::Center);

    m_itemImage = new ImageView();
    m_itemImage->setImageSource(QUrl("asset:///images/forward.png"));
    imageContainer->add(m_itemImage);

    itemContainer->add(m_listItem);
    itemContainer->add(imageContainer);

    // A Colored Container will be used to show if an item is highlighted.
    m_highlightContainer = new Container();

    m_highlightContainer->setBackground(Color::fromARGB(0xff75b5d3));
    m_highlightContainer->setOpacity(0.0);
    m_highlightContainer->setPreferredWidth(m_highlightContainer->maxWidth());

    m_highlightContainer->setPreferredHeight(120.0f);

    itemContainer->add(m_highlightContainer);
    setRoot(itemContainer);

}