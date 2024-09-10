    void InventoryWindow::pickUpObject (MWWorld::Ptr object)
    {
        /// \todo scripts

        // make sure the object is of a type that can be picked up
        std::string type = object.getTypeName();
        if ( (type != typeid(ESM::Apparatus).name())
            && (type != typeid(ESM::Armor).name())
            && (type != typeid(ESM::Book).name())
            && (type != typeid(ESM::Clothing).name())
            && (type != typeid(ESM::Ingredient).name())
            && (type != typeid(ESM::Light).name())
            && (type != typeid(ESM::Miscellaneous).name())
            && (type != typeid(ESM::Tool).name())
            && (type != typeid(ESM::Probe).name())
            && (type != typeid(ESM::Repair).name())
            && (type != typeid(ESM::Weapon).name())
            && (type != typeid(ESM::Potion).name()))
            return;

        // sound
        std::string sound = MWWorld::Class::get(object).getUpSoundId(object);
        MWBase::Environment::get().getSoundManager()->playSound(sound, 1, 1);

        int count = object.getRefData().getCount();

        // add to player inventory
        // can't use ActionTake here because we need an MWWorld::Ptr to the newly inserted object
        MWWorld::Ptr player = MWBase::Environment::get().getWorld()->getPlayer().getPlayer();
        MWWorld::Ptr newObject = *MWWorld::Class::get (player).getContainerStore (player).add (object);
        // remove from world
        MWBase::Environment::get().getWorld()->deleteObject (object);

        mDragAndDrop->mIsOnDragAndDrop = true;
        mDragAndDrop->mDraggedCount = count;

        std::string path = std::string("icons\\");
        path += MWWorld::Class::get(newObject).getInventoryIcon(newObject);
        MyGUI::ImageBox* baseWidget = mContainerWidget->createWidget<ImageBox>("ImageBox", MyGUI::IntCoord(0, 0, 42, 42), MyGUI::Align::Default);
        baseWidget->detachFromWidget();
        baseWidget->attachToWidget(mDragAndDrop->mDragAndDropWidget);
        baseWidget->setUserData(newObject);
        mDragAndDrop->mDraggedWidget = baseWidget;
        ImageBox* image = baseWidget->createWidget<ImageBox>("ImageBox", MyGUI::IntCoord(5, 5, 32, 32), MyGUI::Align::Default);
        int pos = path.rfind(".");
        path.erase(pos);
        path.append(".dds");
        image->setImageTexture(path);
        image->setNeedMouseFocus(false);

        // text widget that shows item count
        MyGUI::TextBox* text = image->createWidget<MyGUI::TextBox>("SandBrightText", MyGUI::IntCoord(0, 14, 32, 18), MyGUI::Align::Default, std::string("Label"));
        text->setTextAlign(MyGUI::Align::Right);
        text->setNeedMouseFocus(false);
        text->setTextShadow(true);
        text->setTextShadowColour(MyGUI::Colour(0,0,0));
        text->setCaption(getCountString(count));
        mDragAndDrop->mDraggedFrom = this;
    }