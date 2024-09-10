GUIWidget* CursesBaseContainer::nextFocusable(GUIWidget *from) {
    GUIContainer::Children chld = ((GUIContainer*)widget())->childWidgets();
    QListIterator<GUIWidget*> i(chld);

    while(i.hasNext()) {
        GUIWidget* next = i.next();
        GUIContainer* con = qobject_cast<GUIContainer*>(next);
        if(!con && !next->isFocusable())
            continue;

        if(from == 0) {
            from = next;
            i.previous();
        }

        if(from == next || (from == (GUIWidget *)-1 && next->isFocused())) {
            while(i.hasNext()) {
                next = i.next();
                con = qobject_cast<GUIContainer*>(next);
                if(con && !con->isWindow()) {
                    next = con->internal<CursesBaseContainer>()->nextFocusable(0);
                    if(next)
                        return next;
                    continue;
                }

                if(next->isFocusable())
                    return next;
            }

            break;
        }
    }

    if(!isWindow()) {
        GUIContainer* par = widget()->parentContainer();
        if(par)
            return par->internal<CursesBaseContainer>()->nextFocusable(widget());
    }

    return 0;
}