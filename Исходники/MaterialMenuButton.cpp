void MenuButton::layoutSubviews() {
	auto height = 48.0f;

	auto menu = getMenu();
	if (!menu) {
		return;
	}
	auto menuMetrics = menu->getMetrics();

	auto font = (menuMetrics == MenuMetrics::Navigation)?FontType::Body_1:FontType::Subhead;

	_menuNameLabel->setFont(font);
	_menuValueLabel->setFont(font);

	_menuNameLabel->setVisible(false);
	_menuValueLabel->setVisible(false);
	_menuNameIcon->setVisible(false);
	_menuValueIcon->setVisible(false);

	if (_source) {
		bool enabled = (_source->getCallback() != nullptr || _source->getNextMenu() != nullptr);
		float namePos = metrics::menuFirstLeftKeyline(menuMetrics);
		auto nameIcon = _source->getNameIcon();
		if (nameIcon != IconName::None) {
			_menuNameIcon->setIconName(nameIcon);
			_menuNameIcon->setPosition(cocos2d::Vec2(namePos, height / 2));
			_menuNameIcon->setVisible(true);
			_menuNameIcon->setOpacity((enabled) ? 222 : 138);

			namePos = metrics::menuSecondLeftKeyline(menuMetrics);
		} else {
			_menuNameIcon->setVisible(false);
		}

		auto name = _source->getName();
		if (!name.empty()) {
			_menuNameLabel->setString(name);
			_menuNameLabel->setPosition(cocos2d::Vec2(namePos, height / 2));
			_menuNameLabel->setVisible(true);
			_menuNameLabel->setOpacity((enabled) ? 222 : 138);
		} else {
			_menuNameLabel->setVisible(false);
		}

		if (_source->getNextMenu()) {
			_menuValueIcon->setIconName(IconName::Navigation_arrow_drop_down);
			_menuValueIcon->setPosition(cocos2d::Vec2(_contentSize.width - 8, height / 2));
			_menuValueIcon->setVisible(true);
			_menuValueIcon->setRotated(true);
		} else {
			_menuValueIcon->setVisible(false);
			_menuValueIcon->setRotated(false);
		}

		if (!_source->getValue().empty() && !_menuValueIcon->isVisible()) {
			_menuValueLabel->setVisible(true);
			_menuValueLabel->setString(_source->getValue());
			_menuValueLabel->setPosition(cocos2d::Vec2(_contentSize.width - 16, height / 2));
			_menuValueLabel->setOpacity((enabled) ? 222 : 138);
		} else {
			_menuValueLabel->setVisible(false);
		}

		if (_source->getValueIcon() != IconName::Empty && _source->getValueIcon() != IconName::None
			&& !_menuValueLabel->isVisible() && !_menuValueIcon->isVisible()) {

			_menuValueIcon->setIconName(_source->getValueIcon());
			_menuValueIcon->setPosition(cocos2d::Vec2(_contentSize.width - 16, height / 2));
			_menuValueIcon->setVisible(true);
			_menuValueIcon->setOpacity((enabled) ? 222 : 138);
		}

		if (_source->isSelected()) {
			setSelected(true, true);
		} else {
			setSelected(false);
		}

		setEnabled(enabled && _menu->isEnabled());
	}
}