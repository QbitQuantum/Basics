/** draw circle as a 2 pi arc */
void RS_Circle::draw(RS_Painter* painter, RS_GraphicView* view, double& patternOffset) {
    RS_Arc arc(getParent(), RS_ArcData(getCenter(),getRadius(),0.,2.*M_PI, false));
    arc.setSelected(isSelected());
    arc.setPen(getPen());
    arc.draw(painter,view,patternOffset);
}