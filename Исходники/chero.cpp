void Hero::takeAll()
{
    ObjectWeakPtrs objects;
    if (Simulator::get().listObjectsAt(
            getX(),
            getY(),
            getZ(),
            &objects))
    {
        ItemSharedPtrs items;
        std::for_each(
            objects.begin(), objects.end(), [&items](const ObjectWeakPtr& o)
            {
                ObjectSharedPtr object = o.lock();
                if (object->getObjectType() & OBJECT_TYPE_CHARACTER)
                {
                    Character* target = (Character*)object.get();
                    if (target->getHp() == 0)
                    {
                        items.reserve(items.size() + target->getItems().size());
                        items.insert(items.end(), target->getItems().begin(), target->getItems().end());
                        target->removeAllItems();
                    }
                }
                else if (object->getObjectType() & OBJECT_TYPE_CHEST)
                {
                    Chest* target = (Chest*)object.get();
                    items.reserve(items.size() + target->getItems().size());
                    items.insert(items.end(), target->getItems().begin(), target->getItems().end());
                    target->removeAllItems();
                }
            });

        if (!items.empty())
        {
            WindowSharedPtr w(new Window());
            w->setHorizontalAlign(Window::HorizontalAlign::CENTER);
            w->setVerticalAlign(Window::VerticalAlign::BOTTOM);
            w->setTitle("Added To Inventory");
            w->setMaxWidth(50);

            bool first = true;
            for_each(items.begin(), items.end(),
                     [w, &first] (const ItemSharedPtr& item)
                     {
                         if (!first)
                         {
                             w->printEndLine();
                         }
                         first = false;
                         w->print(Colors::WHITE(), item->getName());
                     });

            WindowManager::get().popup(w, 5);

            addItems(items);
        }
    }
}