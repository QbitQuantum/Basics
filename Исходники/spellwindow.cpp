    void SpellWindow::updateSpells()
    {
        const int spellHeight = 18;

        mHeight = 0;
        while (mSpellView->getChildCount())
            MyGUI::Gui::getInstance().destroyWidget(mSpellView->getChildAt(0));

        // retrieve all player spells, divide them into Powers and Spells and sort them
        std::vector<std::string> spellList;
        MWWorld::Ptr player = MWBase::Environment::get().getWorld()->getPlayer().getPlayer();
        MWWorld::InventoryStore& store = MWWorld::Class::get(player).getInventoryStore(player);
        MWMechanics::CreatureStats& stats = MWWorld::Class::get(player).getCreatureStats(player);
        MWMechanics::Spells& spells = stats.getSpells();

        // the following code switches between selected enchanted item and selected spell (only one of these
        // can be active at a time)
        std::string selectedSpell = spells.getSelectedSpell();
        MWWorld::Ptr selectedItem;
        if (store.getSelectedEnchantItem() != store.end())
        {
            selectedSpell = "";
            selectedItem = *store.getSelectedEnchantItem();

            bool allowSelectedItem = true;

            // make sure that the item is still in the player inventory, otherwise it can't be selected
            bool found = false;
            for (MWWorld::ContainerStoreIterator it(store.begin()); it != store.end(); ++it)
            {
                if (*it == selectedItem)
                    found = true;
            }
            if (!found)
                allowSelectedItem = false;

            // if the selected item can be equipped, make sure that it actually is equipped
            std::pair<std::vector<int>, bool> slots;
            slots = MWWorld::Class::get(selectedItem).getEquipmentSlots(selectedItem);
            if (!slots.first.empty())
            {
                bool equipped = false;
                for (int i=0; i < MWWorld::InventoryStore::Slots; ++i)
                {
                    if (store.getSlot(i) != store.end() && *store.getSlot(i) == selectedItem)
                    {
                        equipped = true;
                        break;
                    }
                }

                if (!equipped)
                    allowSelectedItem = false;
            }

            if (!allowSelectedItem)
            {
                store.setSelectedEnchantItem(store.end());
                spells.setSelectedSpell("");
                mWindowManager.unsetSelectedSpell();
                selectedItem = MWWorld::Ptr();
            }
        }



        for (MWMechanics::Spells::TIterator it = spells.begin(); it != spells.end(); ++it)
        {
            spellList.push_back(*it);
        }

        std::vector<std::string> powers;
        std::vector<std::string>::iterator it = spellList.begin();
        while (it != spellList.end())
        {
            const ESM::Spell* spell = MWBase::Environment::get().getWorld()->getStore().spells.find(*it);
            if (spell->data.type == ESM::Spell::ST_Power)
            {
                powers.push_back(*it);
                it = spellList.erase(it);
            }
            else if (spell->data.type == ESM::Spell::ST_Ability
                || spell->data.type == ESM::Spell::ST_Blight
                || spell->data.type == ESM::Spell::ST_Curse
                || spell->data.type == ESM::Spell::ST_Disease)
            {
                it = spellList.erase(it);
            }
            else
                ++it;
        }
        std::sort(powers.begin(), powers.end(), sortSpells);
        std::sort(spellList.begin(), spellList.end(), sortSpells);

        // retrieve player's enchanted items
        std::vector<MWWorld::Ptr> items;
        for (MWWorld::ContainerStoreIterator it(store.begin()); it != store.end(); ++it)
        {
            std::string enchantId = MWWorld::Class::get(*it).getEnchantment(*it);
            if (enchantId != "")
            {
                // only add items with "Cast once" or "Cast on use"
                const ESM::Enchantment* enchant = MWBase::Environment::get().getWorld()->getStore().enchants.find(enchantId);
                int type = enchant->data.type;
                if (type != ESM::Enchantment::CastOnce
                    && type != ESM::Enchantment::WhenUsed)
                    continue;

                items.push_back(*it);
            }
        }
        std::sort(items.begin(), items.end(), sortItems);


        int height = estimateHeight(items.size() + powers.size() + spellList.size());
        bool scrollVisible = height > mSpellView->getHeight();
        mWidth = mSpellView->getWidth() - (scrollVisible ? 18 : 0);

        // powers
        addGroup("#{sPowers}", "");

        for (std::vector<std::string>::const_iterator it = powers.begin(); it != powers.end(); ++it)
        {
            const ESM::Spell* spell = MWBase::Environment::get().getWorld()->getStore().spells.find(*it);
            MyGUI::Button* t = mSpellView->createWidget<MyGUI::Button>("SpellText",
                MyGUI::IntCoord(4, mHeight, mWidth-8, spellHeight), MyGUI::Align::Left | MyGUI::Align::Top);
            t->setCaption(spell->name);
            t->setTextAlign(MyGUI::Align::Left);
            t->setUserString("ToolTipType", "Spell");
            t->setUserString("Spell", *it);
            t->eventMouseWheel += MyGUI::newDelegate(this, &SpellWindow::onMouseWheel);
            t->eventMouseButtonClick += MyGUI::newDelegate(this, &SpellWindow::onSpellSelected);

            if (*it == selectedSpell)
                t->setStateSelected(true);

            mHeight += spellHeight;
        }

        // other spells
        addGroup("#{sSpells}", "#{sCostChance}");
        for (std::vector<std::string>::const_iterator it = spellList.begin(); it != spellList.end(); ++it)
        {
            const ESM::Spell* spell = MWBase::Environment::get().getWorld()->getStore().spells.find(*it);
            MyGUI::Button* t = mSpellView->createWidget<MyGUI::Button>("SpellText",
                MyGUI::IntCoord(4, mHeight, mWidth-8, spellHeight), MyGUI::Align::Left | MyGUI::Align::Top);
            t->setCaption(spell->name);
            t->setTextAlign(MyGUI::Align::Left);
            t->setUserString("ToolTipType", "Spell");
            t->setUserString("Spell", *it);
            t->eventMouseWheel += MyGUI::newDelegate(this, &SpellWindow::onMouseWheel);
            t->eventMouseButtonClick += MyGUI::newDelegate(this, &SpellWindow::onSpellSelected);
            t->setStateSelected(*it == selectedSpell);

            // cost / success chance
            MyGUI::Button* costChance = mSpellView->createWidget<MyGUI::Button>("SpellText",
                MyGUI::IntCoord(4, mHeight, mWidth-8, spellHeight), MyGUI::Align::Left | MyGUI::Align::Top);
            std::string cost = boost::lexical_cast<std::string>(spell->data.cost);
            std::string chance = boost::lexical_cast<std::string>(int(MWMechanics::getSpellSuccessChance(*it, player)));
            costChance->setCaption(cost + "/" + chance);
            costChance->setTextAlign(MyGUI::Align::Right);
            costChance->setNeedMouseFocus(false);
            costChance->setStateSelected(*it == selectedSpell);


            mHeight += spellHeight;
        }


        // enchanted items
        addGroup("#{sMagicItem}", "#{sCostCharge}");

        for (std::vector<MWWorld::Ptr>::const_iterator it = items.begin(); it != items.end(); ++it)
        {
            MWWorld::Ptr item = *it;

            const ESM::Enchantment* enchant = MWBase::Environment::get().getWorld()->getStore().enchants.find(MWWorld::Class::get(item).getEnchantment(item));

            // check if the item is currently equipped (will display in a different color)
            bool equipped = false;
            for (int i=0; i < MWWorld::InventoryStore::Slots; ++i)
            {
                if (store.getSlot(i) != store.end() && *store.getSlot(i) == item)
                {
                    equipped = true;
                    break;
                }
            }

            MyGUI::Button* t = mSpellView->createWidget<MyGUI::Button>(equipped ? "SpellText" : "SpellTextUnequipped",
                MyGUI::IntCoord(4, mHeight, mWidth-8, spellHeight), MyGUI::Align::Left | MyGUI::Align::Top);
            t->setCaption(MWWorld::Class::get(item).getName(item));
            t->setTextAlign(MyGUI::Align::Left);
            t->setUserData(item);
            t->setUserString("ToolTipType", "ItemPtr");
            t->setUserString("Equipped", equipped ? "true" : "false");
            t->eventMouseButtonClick += MyGUI::newDelegate(this, &SpellWindow::onEnchantedItemSelected);
            t->eventMouseWheel += MyGUI::newDelegate(this, &SpellWindow::onMouseWheel);
            t->setStateSelected(item == selectedItem);

            // cost / charge
            MyGUI::Button* costCharge = mSpellView->createWidget<MyGUI::Button>(equipped ? "SpellText" : "SpellTextUnequipped",
                MyGUI::IntCoord(4, mHeight, mWidth-8, spellHeight), MyGUI::Align::Left | MyGUI::Align::Top);

            std::string cost = boost::lexical_cast<std::string>(enchant->data.cost);
            std::string charge = boost::lexical_cast<std::string>(enchant->data.charge); /// \todo track current charge
            if (enchant->data.type == ESM::Enchantment::CastOnce)
            {
                // this is Morrowind behaviour
                cost = "100";
                charge = "100";
            }

            costCharge->setCaption(cost + "/" + charge);
            costCharge->setTextAlign(MyGUI::Align::Right);
            costCharge->setNeedMouseFocus(false);
            costCharge->setStateSelected(item == selectedItem);

            mHeight += spellHeight;
        }

        mSpellView->setCanvasSize(mSpellView->getWidth(), std::max(mSpellView->getHeight(), mHeight));
    }