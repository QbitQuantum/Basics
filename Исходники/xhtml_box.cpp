	void Box::layout(LayoutEngine& eng, const Dimensions& ocontaining)
	{
		auto containing = ocontaining;
		auto styles = getStyleNode();

		std::unique_ptr<LayoutEngine::FloatContextManager> fcm;
		if(getParent() && getParent()->isFloat()) {
			fcm.reset(new LayoutEngine::FloatContextManager(eng, FloatList()));
		}

		point cursor;
		// If we have a clear flag set, then move the cursor in the layout engine to clear appropriate floats.
		if(node_ != nullptr) {
			eng.moveCursorToClearFloats(node_->getClear(), cursor);
		}

		NodePtr node = getNode();

		std::unique_ptr<RenderContext::Manager> ctx_manager;
		if(node != nullptr) {
			ctx_manager.reset(new RenderContext::Manager(node->getProperties()));
		}

		if(styles != nullptr) {
			auto ovf = styles->getOverflow();
			// this is kind of a hack, since we really want to avoid re-running layout
			//if(ovf == Overflow::SCROLL || ovf == Overflow::AUTO) {
				containing.content_.width -= scrollbar_default_width * LayoutEngine::getFixedPointScale();
			//}
		}

		handlePreChildLayout(eng, containing);

		if(node_ != nullptr) {
			const std::vector<StyleNodePtr>& node_children = node_->getChildren();
			if(!node_children.empty()) {
				boxes_ = eng.layoutChildren(node_children, shared_from_this());
			}
		}

		for(auto& child : boxes_) {
			if(child->isFloat()) {
				handlePreChildLayout3(eng, containing);
				child->layout(eng, dimensions_);
				handlePostFloatChildLayout(eng, child);
				eng.addFloat(child);
			}
		}

		offset_ = (getParent() != nullptr ? getParent()->getOffset() : point()) + point(dimensions_.content_.x, dimensions_.content_.y);
		if(isBlockBox()) {
			const FixedPoint y1 = offset_.y;
			point p(eng.getXAtPosition(y1, y1 + getLineHeight()), 0);
			eng.setCursor(p);
		}

		handlePreChildLayout2(eng, containing);

		for(auto& child : boxes_) {
			if(!child->isFloat()) {
				handlePreChildLayout3(eng, containing);
				child->layout(eng, dimensions_);
				handlePostChildLayout(eng, child);
			}
		}
		
		handleLayout(eng, containing);
		//layoutAbsolute(eng, containing);

		for(auto& child : boxes_) {
			child->postParentLayout(eng, dimensions_);
		}

		// need to call this after doing layout, since we need to now what the computed padding/border values are.
		border_info_.init(dimensions_);
		background_info_.init(dimensions_);

		if(isBlockBox() && !isFloat()) {
			point p;
			p.y = getTop() + getHeight() + getMBPBottom();
			p.x = eng.getXAtPosition(p.y, p.y + getLineHeight());
			eng.setCursor(p);
		}

		precss_content_height_ = dimensions_.content_.height;
		if(isBlockBox() && styles != nullptr) {
			auto css_h = styles->getHeight();
			if(!css_h->isAuto()) {
				setContentHeight(css_h->getLength().compute(containing.content_.height));				
			}
		}

		eng.closeLineBox();
	}