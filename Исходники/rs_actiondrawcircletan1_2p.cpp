RS_Entity* RS_ActionDrawCircleTan1_2P::catchCircle(QMouseEvent* e) {
    RS_Entity* ret=NULL;
    RS_Entity*  en = catchEntity(e,enTypeList, RS2::ResolveAll);
    if(en == NULL) return ret;
    if(en->isVisible()==false) return ret;
    if(en->getParent() != NULL) {
        if ( en->getParent()->ignoredOnModification()){
            return NULL;
        }
    }
    return en;
}