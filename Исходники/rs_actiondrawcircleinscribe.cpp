void RS_ActionDrawCircleInscribe::mouseMoveEvent(QMouseEvent* e) {
    RS_DEBUG->print("RS_ActionDrawCircle4Line::mouseMoveEvent begin");

    if(getStatus() == SetLine3) {
        RS_Entity*  en = catchEntity(e, RS2::EntityLine, RS2::ResolveAll);
        if(en == NULL) return;
        if(!(en->isVisible() && en->rtti()== RS2::EntityLine)) return;
        for(int i=0;i<getStatus();i++) {
            if(en->getId() == lines[i]->getId()) return; //do not pull in the same line again
        }
        if(en->getParent() != NULL) {
            if ( en->getParent()->rtti() == RS2::EntityInsert         /**Insert*/
                 || en->getParent()->rtti() == RS2::EntitySpline
                 || en->getParent()->rtti() == RS2::EntityText         /**< Text 15*/
                 || en->getParent()->rtti() == RS2::EntityDimAligned   /**< Aligned Dimension */
                 || en->getParent()->rtti() == RS2::EntityDimLinear    /**< Linear Dimension */
                 || en->getParent()->rtti() == RS2::EntityDimRadial    /**< Radial Dimension */
                 || en->getParent()->rtti() == RS2::EntityDimDiametric /**< Diametric Dimension */
                 || en->getParent()->rtti() == RS2::EntityDimAngular   /**< Angular Dimension */
                 || en->getParent()->rtti() == RS2::EntityDimLeader    /**< Leader Dimension */
                 ){
                return;
            }
        }
        coord= graphicView->toGraph(e->x(), e->y());
        lines.resize(getStatus());
        lines.push_back(static_cast<RS_Line*>(en));
//        lines[getStatus()]=static_cast<RS_Line*>(en);
        if(preparePreview()) {
            deletePreview();
            RS_Circle* e=new RS_Circle(preview, cData);
            preview->addEntity(e);
            drawPreview();
        }

    }
    RS_DEBUG->print("RS_ActionDrawCircle4Line::mouseMoveEvent end");
}