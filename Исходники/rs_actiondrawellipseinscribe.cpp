void RS_ActionDrawEllipseInscribe::mouseReleaseEvent(QMouseEvent* e) {
    // Proceed to next status
    if (e->button()==Qt::LeftButton) {
        if (e==NULL) {
            return;
        }
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
        lines.resize(getStatus());
        lines.push_back(static_cast<RS_Line*>(en));

        switch (getStatus()) {
        case SetLine1:
        case SetLine2:
        case SetLine3:
            en->setHighlighted(true);
            setStatus(getStatus()+1);
            graphicView->redraw(RS2::RedrawDrawing);
            break;
        case SetLine4:
            if( preparePreview()) {
                trigger();
            }

        default:
            break;
        }
    } else if (e->button()==Qt::RightButton) {
        // Return to last status:
        if(getStatus()>0){
            lines[getStatus()-1]->setHighlighted(false);
            lines.pop_back();
            graphicView->redraw(RS2::RedrawDrawing);
            deletePreview();

        }
        init(getStatus()-1);
    }
}