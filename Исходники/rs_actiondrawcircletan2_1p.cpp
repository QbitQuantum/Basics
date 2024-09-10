RS_Entity* RS_ActionDrawCircleTan2_1P::catchCircle(QMouseEvent* e) {
    RS_Entity* ret=NULL;
    RS_Entity*  en = catchEntity(e,enTypeList, RS2::ResolveAll);
    if(en == NULL) return ret;
    if(en->isVisible()==false) return ret;
    for(int i=0; i<circles.size(); ++i) {
        if(circles[i])
            if(en->getId() == circles[i]->getId()) return ret; //do not pull in the same line again
    }
    if(en->getParent() != NULL) {
        if ( en->getParent()->rtti() == RS2::EntityInsert         /**Insert*/
             || en->getParent()->rtti() == RS2::EntitySpline
             || en->getParent()->rtti() == RS2::EntityMText        /**< Text 15*/
             || en->getParent()->rtti() == RS2::EntityText         /**< Text 15*/
             || en->getParent()->rtti() == RS2::EntityDimAligned   /**< Aligned Dimension */
             || en->getParent()->rtti() == RS2::EntityDimLinear    /**< Linear Dimension */
             || en->getParent()->rtti() == RS2::EntityDimRadial    /**< Radial Dimension */
             || en->getParent()->rtti() == RS2::EntityDimDiametric /**< Diametric Dimension */
             || en->getParent()->rtti() == RS2::EntityDimAngular   /**< Angular Dimension */
             || en->getParent()->rtti() == RS2::EntityDimLeader    /**< Leader Dimension */
             ){
            return ret;
        }
    }
    return en;
}