PostTypeRenderer::PostTypeRenderer() :
	CustomControl()
{
	Container *itemContainer = new Container();

	    // Dock layout with margins inside.
	    DockLayout *itemLayout = new DockLayout();
	    itemContainer->setLayout(itemLayout);
	    itemContainer->setPreferredWidth(300);

	    // A list item label, docked to the bottom, the text is set in updateItem.
	    postType = Label::create()
	        .text(" ")
	        .layoutProperties(DockLayoutProperties::create()
	        .horizontal(HorizontalAlignment::Center)
	        .vertical(VerticalAlignment::Bottom))
	        .bottomMargin(10.0f)
	        .leftMargin(10.0f);

	    // Add the three controls to the item container.
	    //itemContainer->add(imageContainer);
	    itemContainer->add(postType);

	    setRoot(itemContainer);
}