/**
 * @return true if a parent entity of this entity is selected.
 */
bool RS_Entity::isParentSelected() {
    RS_Entity* p = this;

    do {
        p = p->getParent();
        if (p!=NULL && p->isSelected()==true) {
            return true;
        }
    } while(p!=NULL);

    return false;
}