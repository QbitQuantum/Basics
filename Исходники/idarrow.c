Command* ArrowLineView::InterpretManipulator (Manipulator* m) {
    DragManip* dm = (DragManip*) m;
    Editor* ed = dm->GetViewer()->GetEditor();
    Tool* tool = dm->GetTool();
    Transformer* rel = dm->GetTransformer();
    Command* cmd = nil;
    ArrowVar* aVar = (ArrowVar*) ed->GetState("ArrowVar");

    if (tool->IsA(GRAPHIC_COMP_TOOL)) {
        RubberLine* rl = (RubberLine*) dm->GetRubberband();
        Coord x0, y0, x1, y1;
        rl->GetCurrent(x0, y0, x1, y1);

        if (x0 != x1 || y0 != y1) {
            BrushVar* brVar = (BrushVar*) ed->GetState("BrushVar");
            ColorVar* colVar = (ColorVar*) ed->GetState("ColorVar");
            PatternVar* patVar = (PatternVar*) ed->GetState("PatternVar");

            if (rel != nil) {
                rel = new Transformer(rel);
                rel->Invert();
            }

            ArrowLine* aline = new ArrowLine(
                x0, y0, x1, y1, aVar->Head(), aVar->Tail(), 
                dm->GetViewer()->GetMagnification(), stdgraphic
            );

            if (brVar != nil) aline->SetBrush(brVar->GetBrush());
            if (patVar != nil) { aline->SetPattern(patVar->GetPattern()); }

            if (colVar != nil) {
                aline->SetColors(colVar->GetFgColor(), colVar->GetBgColor());
            }

            aline->SetTransformer(rel);
            Unref(rel);
            cmd = new PasteCmd(ed, new Clipboard(new ArrowLineComp(aline)));
        }

    } else if (tool->IsA(RESHAPE_TOOL)) {
        RubberLine* rl = (RubberLine*) dm->GetRubberband();
        Coord epx0, epy0, epx1, epy1;
        GetEndpoints(epx0, epy0, epx1, epy1);

        Coord x0, y0, x1, y1;
        rl->GetCurrent(x0, y0, x1, y1);

        if (x0 == epx1 && y0 == epy1) {
            x0 = x1; y0 = y1;
            x1 = epx1; y1 = epy1;
        }

        if (rel != nil) {
            rel = new Transformer(rel);
            rel->Invert();
        }
        ArrowLine* orig = GetArrowLineComp()->GetArrowLine();
        ArrowLine* aline = new ArrowLine(
	    x0, y0, x1, y1, orig->Head(), orig->Tail(),
            dm->GetViewer()->GetMagnification(), GetGraphic()
	);
        aline->SetTransformer(rel);
        Unref(rel);
        cmd = new ReplaceCmd(ed, new ArrowLineComp(aline));

    } else {
        cmd = LineView::InterpretManipulator(m);
    }
    return cmd;
}