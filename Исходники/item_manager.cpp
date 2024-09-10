/** Creates a new item.
 *  \param type Type of the item.
 *  \param xyz  Position of the item.
 *  \param normal The normal of the terrain to set roll and pitch.
 *  \param parent In case of a dropped item used to avoid that a kart
 *         is affected by its own items.
 */
Item* ItemManager::newItem(Item::ItemType type, const Vec3& xyz, 
                           const Vec3 &normal, Kart *parent)
{
    // Find where the item can be stored in the index list: either in a
    // previously deleted entry, otherwise at the end.
    int index = -1;
    for(index=m_all_items.size()-1; index>=0 && m_all_items[index]; index--) {}

    if(index==-1) index = m_all_items.size();
    Item* item;
    item = new Item(type, xyz, normal, m_item_mesh[type], index);
    if(parent != NULL) item->setParent(parent);
    if(m_switch_time>=0)
    {
        Item::ItemType new_type = m_switch_to[item->getType()];
        item->switchTo(new_type, m_item_mesh[(int)new_type]);
    }
    if(index<(int)m_all_items.size())
        m_all_items[index] = item;
    else
        m_all_items.push_back(item);

    return item;
}   // newItem