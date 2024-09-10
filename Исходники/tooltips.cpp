void ToolTips::onFrame(float frameDuration)
{
    while (mDynamicToolTipBox->getChildCount())
    {
        MyGUI::Gui::getInstance().destroyWidget(mDynamicToolTipBox->getChildAt(0));
    }

    // start by hiding everything
    for (unsigned int i=0; i < mMainWidget->getChildCount(); ++i)
    {
        mMainWidget->getChildAt(i)->setVisible(false);
    }

    const IntSize &viewSize = RenderManager::getInstance().getViewSize();

    if (!mEnabled)
    {
        return;
    }

    if (!mGameMode)
    {
        const MyGUI::IntPoint& mousePos = InputManager::getInstance().getMousePosition();

        if (mWindowManager->getWorldMouseOver() && ((mWindowManager->getMode() == GM_Console)
            || (mWindowManager->getMode() == GM_Container)
            || (mWindowManager->getMode() == GM_Inventory)))
        {
            std::string handle = MWBase::Environment::get().getWorld()->getFacedHandle();
            try
            {
                mFocusObject = MWBase::Environment::get().getWorld()->getPtrViaHandle(handle);
            }
            catch (std::exception& e)
            {
                return;
            }

            MyGUI::IntSize tooltipSize = getToolTipViaPtr(true);

            IntPoint tooltipPosition = InputManager::getInstance().getMousePosition() + IntPoint(0, 24);

            // make the tooltip stay completely in the viewport
            if ((tooltipPosition.left + tooltipSize.width) > viewSize.width)
            {
                tooltipPosition.left = viewSize.width - tooltipSize.width;
            }
            if ((tooltipPosition.top + tooltipSize.height) > viewSize.height)
            {
                tooltipPosition.top = viewSize.height - tooltipSize.height;
            }

            setCoord(tooltipPosition.left, tooltipPosition.top, tooltipSize.width, tooltipSize.height);
        }

        else
        {
            const MyGUI::IntPoint& lastPressed = InputManager::getInstance().getLastPressedPosition(MyGUI::MouseButton::Left);

            if (mousePos == lastPressed) // mouseclick makes tooltip disappear
                return;

            if (mousePos.left == mLastMouseX && mousePos.top == mLastMouseY)
            {
                mRemainingDelay -= frameDuration;
            }
            else
            {
                mRemainingDelay = mDelay;
            }
            mLastMouseX = mousePos.left;
            mLastMouseY = mousePos.top;

            if (mRemainingDelay > 0)
                return;

            Widget* focus = InputManager::getInstance().getMouseFocusWidget();
            if (focus == 0)
            {
                return;
            }

            IntSize tooltipSize;

            // try to go 1 level up until there is a widget that has tooltip
            // this is necessary because some skin elements are actually separate widgets
            int i=0;
            while (!focus->isUserString("ToolTipType"))
            {
                focus = focus->getParent();
                if (!focus)
                    return;
                ++i;
            }

            std::string type = focus->getUserString("ToolTipType");
            std::string text = focus->getUserString("ToolTipText");

            if (type == "")
            {
                return;
            }
            else if (type == "ItemPtr")
            {
                mFocusObject = *focus->getUserData<MWWorld::Ptr>();
                tooltipSize = getToolTipViaPtr(false);
            }
            else if (type == "Spell")
            {
                ToolTipInfo info;
                const ESM::Spell *spell = MWBase::Environment::get().getWorld()->getStore().spells.find(focus->getUserString("Spell"));
                info.caption = spell->name;
                Widgets::SpellEffectList effects;
                std::vector<ESM::ENAMstruct>::const_iterator end = spell->effects.list.end();
                for (std::vector<ESM::ENAMstruct>::const_iterator it = spell->effects.list.begin(); it != end; ++it)
                {
                    Widgets::SpellEffectParams params;
                    params.mEffectID = it->effectID;
                    params.mSkill = it->skill;
                    params.mAttribute = it->attribute;
                    params.mDuration = it->duration;
                    params.mMagnMin = it->magnMin;
                    params.mMagnMax = it->magnMax;
                    params.mRange = it->range;
                    params.mIsConstant = (spell->data.type == ESM::Spell::ST_Ability);
                    effects.push_back(params);
                }
                info.effects = effects;
                tooltipSize = createToolTip(info);
            }
            else if (type == "Layout")
            {
                // tooltip defined in the layout
                MyGUI::Widget* tooltip;
                getWidget(tooltip, focus->getUserString("ToolTipLayout"));

                tooltip->setVisible(true);
                if (!tooltip->isUserString("DontResize"))
                {
                    tooltip->setCoord(0, 0, 450, 300); // this is the maximum width of the tooltip before it starts word-wrapping

                    tooltipSize = MyGUI::IntSize(0, tooltip->getSize().height);
                }
                else
                    tooltipSize = tooltip->getSize();

                std::map<std::string, std::string> userStrings = focus->getUserStrings();
                for (std::map<std::string, std::string>::iterator it = userStrings.begin();
                    it != userStrings.end(); ++it)
                {
                    if (it->first == "ToolTipType"
                        || it->first == "ToolTipLayout")
                        continue;


                    size_t underscorePos = it->first.find("_");
                    std::string propertyKey = it->first.substr(0, underscorePos);
                    std::string widgetName = it->first.substr(underscorePos+1, it->first.size()-(underscorePos+1));

                    MyGUI::Widget* w;
                    getWidget(w, widgetName);
                    w->setProperty(propertyKey, it->second);
                }

                for (unsigned int i=0; i<tooltip->getChildCount(); ++i)
                {
                    MyGUI::Widget* w = tooltip->getChildAt(i);

                    if (w->isUserString("AutoResizeHorizontal"))
                    {
                        MyGUI::TextBox* text = w->castType<MyGUI::TextBox>();
                        tooltipSize.width = std::max(tooltipSize.width, w->getLeft() + text->getTextSize().width + 8);
                    }
                    else if (!tooltip->isUserString("DontResize"))
                        tooltipSize.width = std::max(tooltipSize.width, w->getLeft() + w->getWidth() + 8);

                    if (w->isUserString("AutoResizeVertical"))
                    {
                        MyGUI::TextBox* text = w->castType<MyGUI::TextBox>();
                        int height = text->getTextSize().height;
                        if (height > w->getHeight())
                        {
                            tooltipSize += MyGUI::IntSize(0, height - w->getHeight());
                        }
                        if (height < w->getHeight())
                        {
                            tooltipSize -= MyGUI::IntSize(0, w->getHeight() - height);
                        }
                    }
                }
                tooltip->setCoord(0, 0, tooltipSize.width, tooltipSize.height);
            }
            else
                throw std::runtime_error ("unknown tooltip type");

            IntPoint tooltipPosition = InputManager::getInstance().getMousePosition() + IntPoint(0, 24);

            // make the tooltip stay completely in the viewport
            if ((tooltipPosition.left + tooltipSize.width) > viewSize.width)
            {
                tooltipPosition.left = viewSize.width - tooltipSize.width;
            }
            if ((tooltipPosition.top + tooltipSize.height) > viewSize.height)
            {
                tooltipPosition.top = viewSize.height - tooltipSize.height;
            }

            setCoord(tooltipPosition.left, tooltipPosition.top, tooltipSize.width, tooltipSize.height);
        }
    }
    else
    {
        if (!mFocusObject.isEmpty())
        {
            IntSize tooltipSize = getToolTipViaPtr();

            setCoord(viewSize.width/2 - tooltipSize.width/2,
                    std::max(0, int(mFocusToolTipY*viewSize.height - tooltipSize.height)),
                    tooltipSize.width,
                    tooltipSize.height);

            mDynamicToolTipBox->setVisible(true);
        }
    }
}