bool LayoutItem::IsEmpty() const {
    if(GetWidget() && GetWidget()->IsVisible()) {
        return false;
    } else if(GetLayout() && !GetLayout()->IsEmpty()) {
        return false;
    } else if(GetLayoutSpace()) {
        return false;
    }
    return true;
}