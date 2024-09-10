Command* PadView::InterpGraphicCompManip (Manipulator* m) {
    Command* cmd = nil;
    DragManip* dm = (DragManip*) m;
    SlidingRect* sr = (SlidingRect*) dm->GetRubberband();
    Coord l, b, r, t;
    sr->GetCurrent(l, b, r, t);

    if (l != r || b != t) {
        DragManip* dm = (DragManip*) m;
        Editor* ed = dm->GetViewer()->GetEditor();
        BrushVar* brVar = (BrushVar*) ed->GetState("Brush");
        Transformer* rel = dm->GetTransformer();

        if (rel != nil) {
            rel = new Transformer(rel);
            rel->Invert();
        }

        Graphic* pg = GetGraphicComp()->GetGraphic();
        PadGraphic* padGraphic = new PadGraphic(l, b, r, t, pg);

        if (brVar != nil) padGraphic->SetBrush(brVar->GetBrush());

        padGraphic->SetTransformer(rel);
        Unref(rel);
        cmd = new PasteCmd(ed, new Clipboard(NewSubject(padGraphic)));
    }
    return cmd;
}