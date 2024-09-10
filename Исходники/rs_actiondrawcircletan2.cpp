RS_Entity* RS_ActionDrawCircleTan2::catchCircle(QMouseEvent* e) {
    RS_Entity*  en = catchEntity(e,enTypeList, RS2::ResolveAll);
	if(en == nullptr) return nullptr;
	if(en->isVisible()==false) return nullptr;
    for(int i=0;i<getStatus();i++) {
		if(en->getId() == circles[i]->getId()) return nullptr; //do not pull in the same line again
    }
	if(en->getParent()) {
        if ( en->getParent()->ignoredOnModification()){
			return nullptr;
        }
    }
    return en;
}