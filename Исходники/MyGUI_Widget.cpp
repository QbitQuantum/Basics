	Widget::Widget(const IntCoord& _coord, Align _align, const WidgetSkinInfoPtr _info, CroppedRectanglePtr _parent, WidgetCreator * _creator, const Ogre::String & _name) :
		CroppedRectangleInterface(IntCoord(_coord.point(), _info->getSize()), _align, _parent), // размер по скину
		mOwner(static_cast<Widget*>(_parent)),
		UserData(),
		LayerItem(),
		mStateInfo(_info->getStateInfo()),
		mMaskPeekInfo(_info->getMask()),
		mText(null),
		mEnabled(true),
		mVisible(true),
		mInheritedShow(true),
		mAlpha(ALPHA_MIN),
		mName(_name),
		mTexture(_info->getTextureName()),
		mMainSkin(null),
		mWidgetCreator(_creator),
		mInheritsAlpha(true),
		mNeedKeyFocus(false),
		mNeedMouseFocus(true),
		mNeedDragDrop(false),
		mWidgetClient(null)
	{
		// корректируем абсолютные координаты
		mAbsolutePosition = _coord.point();
		if (null != mParent) mAbsolutePosition += mParent->getAbsolutePosition();

		// имя отсылателя сообщений
		mWidgetEventSender = this;

		// загружаем кирпичики виджета
		SubWidgetManager & manager = SubWidgetManager::getInstance();
		for (VectorSubWidgetInfo::const_iterator iter =_info->getBasisInfo().begin(); iter!=_info->getBasisInfo().end(); ++iter) {
			CroppedRectangleInterface * sub = manager.createSubWidget(*iter, this);
			mSubSkinChild.push_back(sub);
			if (sub->_isText()) mText = static_cast<SubWidgetTextInterfacePtr>(sub);
			else if (null == mMainSkin) mMainSkin = sub;
		}

		if (false == isRootWidget()) {
			// если отец уже приаттачен, то и мы аттачимся ??? проверить что уже аттачиться при сет текстуре
			if ((null != getParent()->getLayerItemKeeper())) _attachToLayerItemKeeper(getParent()->getLayerItemKeeper());

			// проверяем наследуемую скрытость
			if ((!mParent->isShow()) || (!getParent()->_isInheritedShow())) {
				mInheritedShow = false;
				// скрываем только саб скины, детей у нас еще нет
				for (VectorCroppedRectanglePtr::iterator skin = mSubSkinChild.begin(); skin != mSubSkinChild.end(); ++skin) (*skin)->hide();
			}
		}

		// этот стиль есть всегда, даже если создатель не хотел его
		setState("normal");

		// парсим свойства
		const MapString & param = _info->getParams();
		if (false == param.empty()) {
			MapString::const_iterator iter = param.find("FontName");
			if (iter != param.end()) setFontName(iter->second);
			iter = param.find("FontHeight");
			if (iter != param.end()) setFontHeight(utility::parseInt(iter->second));
			iter = param.find("NeedKey");
			if (iter != param.end()) setNeedKeyFocus(iter->second == "true");
			iter = param.find("NeedMouse");
			if (iter != param.end()) setNeedMouseFocus(iter->second == "true");
			iter = param.find("AlignText");
			if (iter != param.end()) setTextAlign(SkinManager::parseAlign(iter->second));
			iter = param.find("Colour");
			if (iter != param.end()) setColour(utility::parseColour(iter->second));
			iter = param.find("Pointer");
			if (iter != param.end()) mPointer = iter->second;
			iter = param.find("Show");
			if (iter != param.end()) {
				if (utility::parseBool(iter->second)) show();
				else hide();
			}
		}

		// выставляем альфу, корректировка по отцу автоматически
		setAlpha(ALPHA_MAX);

		// создаем детей
		const VectorChildSkinInfo& child = _info->getChild();
		for (VectorChildSkinInfo::const_iterator iter=child.begin(); iter!=child.end(); ++iter) {
			WidgetPtr widget = createWidgetT(iter->type, iter->skin, iter->coord, iter->align);
			widget->_setInternalString(iter->name);
			// заполняем UserString пропертями
			for (MapString::const_iterator prop=iter->params.begin(); prop!=iter->params.end(); ++prop) {
				widget->setUserString(prop->first, prop->second);
			}
		}

		// а вот теперь нормальный размер
		setSize(_coord.size());

	}