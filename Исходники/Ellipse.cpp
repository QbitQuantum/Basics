Command* EllipseView::InterpretManipulator (Manipulator* m) {
    DragManip* dm = (DragManip*) m;
    Editor* ed = dm->GetViewer()->GetEditor();
    Tool* tool = dm->GetTool();
    Transformer* rel = dm->GetTransformer();
    Command* cmd = nil;

    if (tool->IsA(GRAPHIC_COMP_TOOL)) {
        RubberEllipse* re = (RubberEllipse*) dm->GetRubberband();
        Coord x, y, dummy1, dummy2;
        re->GetCurrent(x, y, dummy1, dummy2);

        if (dummy1 != x || dummy2 != y) {
            BrushVar* brVar = (BrushVar*) ed->GetState("BrushVar");
            PatternVar* patVar = (PatternVar*) ed->GetState("PatternVar");
            ColorVar* colVar = (ColorVar*) ed->GetState("ColorVar");
            Coord xr, yr;
            re->CurrentRadii(xr, yr);

            if (rel != nil) {
                rel = new Transformer(rel);
                rel->Invert();
            }

            Graphic* pg = GetGraphicComp()->GetGraphic();
            SF_Ellipse* ellipse = new SF_Ellipse(x, y, xr, yr, pg);

            if (brVar != nil) ellipse->SetBrush(brVar->GetBrush());
            if (patVar != nil) ellipse->SetPattern(patVar->GetPattern());

            if (colVar != nil) {
                ellipse->SetColors(colVar->GetFgColor(), colVar->GetBgColor());
            }
            ellipse->SetTransformer(rel);
            Unref(rel);
            cmd = new PasteCmd(ed, new Clipboard(new EllipseComp(ellipse)));
        }

    } else {
        cmd = GraphicView::InterpretManipulator(m);
    }
    return cmd;
}