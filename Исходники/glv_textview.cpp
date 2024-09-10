void DropDown::hideList(GLV& g){
	mItemList.disable(Visible);
	g.setFocus(this);
}