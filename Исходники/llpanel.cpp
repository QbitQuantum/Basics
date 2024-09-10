//static 
LLView* LLLayoutStack::fromXML(LLXMLNodePtr node, LLView *parent, LLUICtrlFactory *factory)
{
	std::string orientation_string("vertical");
	node->getAttributeString("orientation", orientation_string);

	eLayoutOrientation orientation = VERTICAL;

	if (orientation_string == "horizontal")
	{
		orientation = HORIZONTAL;
	}
	else if (orientation_string == "vertical")
	{
		orientation = VERTICAL;
	}
	else
	{
		llwarns << "Unknown orientation " << orientation_string << ", using vertical" << llendl;
	}

	LLLayoutStack* layout_stackp = new LLLayoutStack(orientation);

	node->getAttributeS32("border_size", layout_stackp->mPanelSpacing);
	// don't allow negative spacing values
	layout_stackp->mPanelSpacing = llmax(layout_stackp->mPanelSpacing, 0);

	std::string name("stack");
	node->getAttributeString("name", name);

	layout_stackp->setName(name);
	layout_stackp->initFromXML(node, parent);

	LLXMLNodePtr child;
	for (child = node->getFirstChild(); child.notNull(); child = child->getNextSibling())
	{
		S32 min_width = 0;
		S32 min_height = 0;
		BOOL auto_resize = TRUE;

		child->getAttributeS32("min_width", min_width);
		child->getAttributeS32("min_height", min_height);
		child->getAttributeBOOL("auto_resize", auto_resize);

		if (child->hasName("layout_panel"))
		{
			BOOL user_resize = TRUE;
			child->getAttributeBOOL("user_resize", user_resize);
			LLPanel* panelp = (LLPanel*)LLPanel::fromXML(child, layout_stackp, factory);
			if (panelp)
			{
				panelp->setFollowsNone();
				layout_stackp->addPanel(panelp, min_width, min_height, auto_resize, user_resize);
			}
		}
		else
		{
			BOOL user_resize = FALSE;
			child->getAttributeBOOL("user_resize", user_resize);

			LLPanel* panelp = new LLPanel(std::string("auto_panel"));
			LLView* new_child = factory->createWidget(panelp, child);
			if (new_child)
			{
				// put child in new embedded panel
				layout_stackp->addPanel(panelp, min_width, min_height, auto_resize, user_resize);
				// resize panel to contain widget and move widget to be contained in panel
				panelp->setRect(new_child->getRect());
				new_child->setOrigin(0, 0);
			}
			else
			{
				panelp->die();
			}
		}
	}
	layout_stackp->updateLayout();

	return layout_stackp;
}