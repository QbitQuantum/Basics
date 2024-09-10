Interactor* Builder::ScrollerPositionControls () {
    Tray* t = new Tray;
    Interactor* scrollerLabel = ScrollerLabel();
    Interactor* hscrollerPositions = HScrollerPositions();
    Interactor* vscrollerPositions = VScrollerPositions();
    
    t->HBox(t, scrollerLabel);
    t->HBox(t, hspc(2), horizontal, hspc(2), hscrollerPositions, new HGlue, t);
    t->HBox(t, hspc(2), vertical, hspc(2), vscrollerPositions, new HGlue, t);
    t->Align(Left, horizontal, vertical);
    t->Align(Left, hscrollerPositions, vscrollerPositions);

    t->VBox(t, scrollerLabel, vspc(), horizontal, vspc(), vertical, t);
    t->Align(VertCenter, horizontal, hscrollerPositions);
    t->Align(VertCenter, vertical, vscrollerPositions);
    
    return t;
}