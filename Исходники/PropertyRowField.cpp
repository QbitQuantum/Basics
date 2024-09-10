void PropertyRowField::redraw(IDrawContext& context)
{
	int buttonCount = this->buttonCount();
	int offset = 0;
	for (int i = 0; i < buttonCount; ++i) {
		Icon icon = buttonIcon(context.tree, i);
		Rect iconRect(context.widgetRect.right() - BUTTON_SIZE * buttonCount + offset, context.widgetRect.top(), BUTTON_SIZE, context.widgetRect.height());
		context.drawIcon(iconRect, icon, userReadOnly() ? ICON_DISABLED : ICON_NORMAL);
		offset += BUTTON_SIZE;
	}

	int iconSpace = offset ? offset + 2 : 0;
    if(multiValue())
		context.drawEntry(context.widgetRect, " ... ", false, userReadOnly(), iconSpace);
    else if(userReadOnly())
		context.drawValueText(pulledSelected(), valueAsString().c_str());
    else
        context.drawEntry(context.widgetRect, valueAsString().c_str(), usePathEllipsis(), false, iconSpace);

}