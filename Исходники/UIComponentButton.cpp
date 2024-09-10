void UIComponentButton::onRender(Renderer* renderer, UIView* view)
{
	if(hovering)
	{
		RectangleShape hoverRect;
		hoverRect.setRect(view->getBounds());
		hoverRect.setColor(mHoverColor);
		if(mTexture)
		{
			hoverRect.setTexture(mHoverTexture);
		}
		renderer->draw(hoverRect);
	}
	else
	{
		RectangleShape hoverRect;
		hoverRect.setRect(view->getBounds());
		hoverRect.setColor(mNormalColor);
		if(mTexture)
		{
			hoverRect.setTexture(mTexture);
		}
		renderer->draw(hoverRect);
	}

	// -- Label
	Text buttonLabel;
	buttonLabel.setFont(*view->mCore->m_defaultFont);
	buttonLabel.setString(mString);
	buttonLabel.setCharacterSize(view->mRect.height / 2);
	buttonLabel.setOrigin(static_cast<int>((buttonLabel.getLocalBounds().width / 2.f ) + 0.5f), static_cast<int>((buttonLabel.getLocalBounds().height / 2.f) + 0.5f));
	buttonLabel.setPosition(static_cast<int>((view->mRect.left + view->mRect.width / 2.f ) + 0.5f), static_cast<int>((view->mRect.top +  view->mRect.height / 2.f) + 0.5f));
	if(buttonLabel.getLocalBounds().width > view->getSize().x * 0.9f)
	{
		// The text is too big and passes the 90% of the button's width
		float diminishRatio = (view->getSize().x * 0.9f) / buttonLabel.getLocalBounds().width;
		buttonLabel.setCharacterSize(static_cast<unsigned int>(static_cast<float>(buttonLabel.getCharacterSize()) * diminishRatio));
		buttonLabel.setOrigin(static_cast<int>((buttonLabel.getLocalBounds().width / 2.f ) + 0.5f), static_cast<int>((buttonLabel.getLocalBounds().height / 2.f) + 0.5f));
	}
	renderer->draw(buttonLabel);
}