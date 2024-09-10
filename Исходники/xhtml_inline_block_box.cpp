	void InlineBlockBox::handlePreChildLayout2(LayoutEngine& eng, const Dimensions& containing)
	{
		cursor_ = eng.getCursor();
		eng.setCursor(point(0, 0));
		if(!getChildren().empty() || !isReplaceable()) {
			setContentHeight(0);
		} else if(isReplaceable()) {
			NodePtr node = getNode();
			const rect& r = node->getDimensions();
			setContentWidth(r.w() * LayoutEngine::getFixedPointScale());
			setContentHeight(r.h() * LayoutEngine::getFixedPointScale());
		}
	}