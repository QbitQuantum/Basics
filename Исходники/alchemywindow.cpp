    void AlchemyWindow::update()
    {
        Widgets::SpellEffectList effects;

        for (int i=0; i<4; ++i)
        {
            MyGUI::ImageBox* ingredient;
            if (i==0)
                ingredient = mIngredient1;
            else if (i==1)
                ingredient = mIngredient2;
            else if (i==2)
                ingredient = mIngredient3;
            else if (i==3)
                ingredient = mIngredient4;

            if (!ingredient->isUserString("ToolTipType"))
                continue;

            // add the effects of this ingredient to list of effects
            MWWorld::LiveCellRef<ESM::Ingredient>* ref = ingredient->getUserData<MWWorld::Ptr>()->get<ESM::Ingredient>();
            for (int i=0; i<4; ++i)
            {
                if (ref->base->mData.mEffectID[i] < 0)
                    continue;
                MWGui::Widgets::SpellEffectParams params;
                params.mEffectID = ref->base->mData.mEffectID[i];
                params.mAttribute = ref->base->mData.mAttributes[i];
                params.mSkill = ref->base->mData.mSkills[i];
                effects.push_back(params);
            }

            // update ingredient count labels
            if (ingredient->getChildCount())
                MyGUI::Gui::getInstance().destroyWidget(ingredient->getChildAt(0));

            MyGUI::TextBox* text = ingredient->createWidget<MyGUI::TextBox>("SandBrightText", MyGUI::IntCoord(0, 14, 32, 18), MyGUI::Align::Default, std::string("Label"));
            text->setTextAlign(MyGUI::Align::Right);
            text->setNeedMouseFocus(false);
            text->setTextShadow(true);
            text->setTextShadowColour(MyGUI::Colour(0,0,0));
            text->setCaption(getCountString(ingredient->getUserData<MWWorld::Ptr>()->getRefData().getCount()));
        }

        // now remove effects that are only present once
        Widgets::SpellEffectList::iterator it = effects.begin();
        while (it != effects.end())
        {
            Widgets::SpellEffectList::iterator next = it;
            ++next;
            bool found = false;
            for (; next != effects.end(); ++next)
            {
                if (*next == *it)
                    found = true;
            }

            if (!found)
                it = effects.erase(it);
            else
                ++it;
        }

        // now remove duplicates, and don't allow more than 4 effects
        Widgets::SpellEffectList old = effects;
        effects.clear();
        int i=0;
        for (Widgets::SpellEffectList::iterator it = old.begin();
            it != old.end(); ++it)
        {
            bool found = false;
            for (Widgets::SpellEffectList::iterator it2 = effects.begin();
                it2 != effects.end(); ++it2)
            {
                // MW considers all "foritfy attribute" effects as the same effect. See the
                // "Can't create multi-state boost potions" discussion on http://www.uesp.net/wiki/Morrowind_talk:Alchemy
                // thus, we are only checking effectID here and not attribute or skill
                if (it2->mEffectID == it->mEffectID)
                    found = true;
            }
            if (!found && i<4)
            {
                ++i;
                effects.push_back(*it);
            }
        }
        mEffects = effects;

        while (mEffectsBox->getChildCount())
            MyGUI::Gui::getInstance().destroyWidget(mEffectsBox->getChildAt(0));

        MyGUI::IntCoord coord(0, 0, mEffectsBox->getWidth(), 24);
        Widgets::MWEffectListPtr effectsWidget = mEffectsBox->createWidget<Widgets::MWEffectList>
            ("MW_StatName", coord, MyGUI::Align::Left | MyGUI::Align::Top);
        effectsWidget->setWindowManager(&mWindowManager);
        effectsWidget->setEffectList(effects);

        std::vector<MyGUI::WidgetPtr> effectItems;
        effectsWidget->createEffectWidgets(effectItems, mEffectsBox, coord, false, 0);
        effectsWidget->setCoord(coord);
    }