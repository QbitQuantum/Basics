void LLToastScriptQuestion::createButtons()
{
	LLNotificationFormPtr form = mNotification->getForm();
	int num_elements = form->getNumElements();
	int buttons_width = 0;

	for (int i = 0; i < num_elements; ++i)
	{
		LLSD form_element = form->getElement(i);
		if ("button" == form_element["type"].asString())
		{
			LLButton::Params p;
			const LLFontGL* font = LLFontGL::getFontSansSerif();
			p.name(form_element["name"].asString());
			p.label(form_element["text"].asString());
			p.layout("topleft");
			p.font(font);
			p.rect.height(BUTTON_HEIGHT);
			p.click_callback.function(boost::bind(&LLToastScriptQuestion::onButtonClicked, this, form_element["name"].asString()));
			p.rect.left = LEFT_PAD;
			p.rect.width = font->getWidth(form_element["text"].asString());
			p.auto_resize = true;
			p.follows.flags(FOLLOWS_LEFT | FOLLOWS_BOTTOM);
			p.image_color(LLUIColorTable::instance().getColor("ButtonCautionImageColor"));
			p.image_color_disabled(LLUIColorTable::instance().getColor("ButtonCautionImageColor"));

			LLButton* button = LLUICtrlFactory::create<LLButton>(p);
			button->autoResize();
			getChild<LLPanel>("buttons_panel")->addChild(button);

			LLRect rect = button->getRect();
			rect.setLeftTopAndSize(buttons_width, rect.mTop, rect.getWidth(), rect.getHeight());
			button->setRect(rect);

			buttons_width += rect.getWidth() + LEFT_PAD;
		}
	}
}