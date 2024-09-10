void UIComponentImage::onRender(GraphicsDevice* renderer, UIView* view)
{
	RectangleShape backgroundRect;
	backgroundRect.setRect(view->getBounds());
	if(mTexture) backgroundRect.setTexture(mTexture);
	renderer->draw(backgroundRect);
}