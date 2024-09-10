	void ColorRectSprite::doRender(const RenderState &rs)
	{
		_vstyle._apply(rs);
		
		
		rs.renderer->setTexture(Renderer::white, 0);		
		rs.renderer->draw(&rs, getColor(), RectF(0, 0, 1, 1), getDestRect());
	}