AlbumItem::AlbumItem(Container *parent) :
        CustomControl(parent)
{
    // Dock layout with margins inside
    Container *itemContainer = new Container();
    DockLayout *itemLayout = new DockLayout();
    itemContainer->setLayout(itemLayout);
    itemContainer->setBackground(ImagePaint(QUrl("asset:///images/customcomponents/list_background.png"), RepeatPattern::XY));
    itemContainer->setHorizontalAlignment(HorizontalAlignment::Center);
    itemContainer->setMinHeight(212);
    itemContainer->setPreferredWidth(740);

    // Sub item container
	Container *subItemContainer = Container::create();
	StackLayout *stackLayout = new StackLayout();
	stackLayout->setOrientation( LayoutOrientation::LeftToRight );
	subItemContainer->setLayout(stackLayout);
	subItemContainer->setTopPadding(10);
	subItemContainer->setLeftPadding(10);
	subItemContainer->setRightPadding(10);
	subItemContainer->setBottomPadding(13);
	subItemContainer->setHorizontalAlignment(HorizontalAlignment::Fill);
	subItemContainer->setVerticalAlignment(VerticalAlignment::Fill);

    // A Colored Container will be used to show if an item is highlighted
    mHighlighContainer = Container::create().background(Color::fromARGB(0xff75b5d3)).opacity(0.0);
    mHighlighContainer->setHorizontalAlignment(HorizontalAlignment::Fill);
    mHighlighContainer->setVerticalAlignment(VerticalAlignment::Fill);

    // The list item image, the actual image is set in updateItem
    mItemImage = ImageView::create("asset:///images/loading.jpg");
    //mItemImage->setHorizontalAlignment(HorizontalAlignment::Left);
    mItemImage->setVerticalAlignment(VerticalAlignment::Center);
    mItemImage->setPreferredSize(144.0, 192.0);

    mItemTitle = Label::create("Title");
    mItemTitle->setLayoutProperties(StackLayoutProperties::create().spaceQuota(1));
    mItemTitle->textStyle()->setColor(Color::DarkGray);
    //mItemTitle->setHorizontalAlignment(HorizontalAlignment::Center);
    mItemTitle->setVerticalAlignment(VerticalAlignment::Center);

    mItemDescription = Label::create("Description");
    mItemDescription->textStyle()->setBase(SystemDefaults::TextStyles::subtitleText());
    mItemDescription->setHorizontalAlignment(HorizontalAlignment::Center);
    mItemDescription->setVerticalAlignment(VerticalAlignment::Center);
    mItemDescription->setMultiline(true);

    // Add the shopitem details to the subitem container
    subItemContainer->add(mItemImage);
    subItemContainer->add(mItemTitle);
    subItemContainer->add(mItemDescription);

    // Add the background image and the content to the full item container.
    itemContainer->add(mHighlighContainer);
    itemContainer->add(subItemContainer);

    setRoot(itemContainer);
}