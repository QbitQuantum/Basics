    void SpellView::update()
    {
        if (!mModel.get())
            return;

        mModel->update();

        int curType = -1;

        const int spellHeight = 18;

        mLines.clear();

        while (mScrollView->getChildCount())
            MyGUI::Gui::getInstance().destroyWidget(mScrollView->getChildAt(0));

        for (SpellModel::ModelIndex i = 0; i<int(mModel->getItemCount()); ++i)
        {
            const Spell& spell = mModel->getItem(i);
            if (curType != spell.mType)
            {
                if (spell.mType == Spell::Type_Power)
                    addGroup("#{sPowers}", "");
                else if (spell.mType == Spell::Type_Spell)
                    addGroup("#{sSpells}", "#{sCostChance}");
                else
                    addGroup("#{sMagicItem}", "#{sCostCharge}");
                curType = spell.mType;
            }

            const std::string skin = spell.mActive ? "SandTextButton" : "SpellTextUnequipped";

            Gui::SharedStateButton* t = mScrollView->createWidget<Gui::SharedStateButton>(skin,
                MyGUI::IntCoord(0, 0, 0, spellHeight), MyGUI::Align::Left | MyGUI::Align::Top);
            t->setCaption(spell.mName);
            t->setTextAlign(MyGUI::Align::Left);
            adjustSpellWidget(spell, i, t);

            if (!spell.mCostColumn.empty() && mShowCostColumn)
            {
                Gui::SharedStateButton* costChance = mScrollView->createWidget<Gui::SharedStateButton>(skin,
                    MyGUI::IntCoord(0, 0, 0, spellHeight), MyGUI::Align::Left | MyGUI::Align::Top);
                costChance->setCaption(spell.mCostColumn);
                costChance->setTextAlign(MyGUI::Align::Right);
                adjustSpellWidget(spell, i, costChance);

                Gui::ButtonGroup group;
                group.push_back(t);
                group.push_back(costChance);
                Gui::SharedStateButton::createButtonGroup(group);

                mLines.push_back(LineInfo(t, costChance, i));
            }
            else
                mLines.push_back(LineInfo(t, (MyGUI::Widget*)NULL, i));

            t->setStateSelected(spell.mSelected);
        }

        layoutWidgets();
    }