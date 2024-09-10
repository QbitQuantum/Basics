/**
 * Destroy an item.
 * @param it The item to destroy.
 * @return 1 if destroyed, 0 if not in list.
 */
int Place::destroy(Item *it)
{
    Item * t;
    t = m_item;
    while (t != NULL) {
        if (t == it) {
            t->unlink();	// remove from list
            if (m_cell != NULL) {
            	Position p = m_cell->get_position();
                map->update_seen_item(p);
	            if (int ownlight = t->obdata_ownLight())	/* if item has own light - an electro flare */
					map->remove_light_source(p.level(), p.column(), p.row(), ownlight);
			}
            delete it;
            return 1;
        }
        t = t->m_next;
    }
    return 0;
}