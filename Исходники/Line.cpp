Command* LineView::InterpretManipulator (Manipulator* m) {
    DragManip* dm = (DragManip*) m;
    Editor* ed = dm->GetViewer()->GetEditor();
    Tool* tool = dm->GetTool();
    Transformer* rel = dm->GetTransformer();
    Command* cmd = nil;

    if (tool->IsA(GRAPHIC_COMP_TOOL)) {
        RubberLine* rl = (RubberLine*) dm->GetRubberband();
        Coord x0, y0, x1, y1;
        rl->GetCurrent(x0, y0, x1, y1);

        if (x0 != x1 || y0 != y1) {
            BrushVar* brVar = (BrushVar*) ed->GetState("BrushVar");
            ColorVar* colVar = (ColorVar*) ed->GetState("ColorVar");

            if (rel != nil) {
                rel = new Transformer(rel);
                rel->Invert();
            }

            Graphic* pg = GetGraphicComp()->GetGraphic();
            Line* line = new Line(x0, y0, x1, y1, pg);

            if (brVar != nil) line->SetBrush(brVar->GetBrush());

            if (colVar != nil) {
                line->SetColors(colVar->GetFgColor(), colVar->GetBgColor());
            }
            line->SetTransformer(rel);
            Unref(rel);
            cmd = new PasteCmd(ed, new Clipboard(new LineComp(line)));
        }

    } else if (tool->IsA(MOVE_TOOL)) {
        Coord x0, y0, x1, y1, dummy1, dummy2;
        float fx0, fy0, fx1, fy1;

        SlidingLine* sl = (SlidingLine*) dm->GetRubberband();
        sl->GetOriginal(x0, y0, dummy1, dummy2);
        sl->GetCurrent(x1, y1, dummy1, dummy2);

        if (rel != nil) {
            rel->InvTransform(float(x0), float(y0), fx0, fy0);
            rel->InvTransform(float(x1), float(y1), fx1, fy1);
        }
        cmd = new MoveCmd(ed, fx1 - fx0, fy1 - fy0);

    } else if (tool->IsA(SCALE_TOOL)) {
        ScalingLine* sl = (ScalingLine*) dm->GetRubberband();
        float sxy = sl->CurrentScaling();

        cmd = new ScaleCmd(ed, sxy, sxy);

    } else if (tool->IsA(ROTATE_TOOL)) {
        RotatingLine* rl = (RotatingLine*) dm->GetRubberband();
        float angle = rl->CurrentAngle() - rl->OriginalAngle();

        cmd = new RotateCmd(ed, angle);

    } else if (tool->IsA(RESHAPE_TOOL)) {
        RubberLine* rl = (RubberLine*) dm->GetRubberband();
        Coord x0, y0, x1, y1;
        rl->GetCurrent(x0, y0, x1, y1);

        if (rel != nil) {
            rel = new Transformer(rel);
            rel->Invert();
        }
        Line* line = new Line(x0, y0, x1, y1, GetGraphic());
        line->SetTransformer(rel);
        Unref(rel);
	cmd = new ReplaceCmd(ed, new LineComp(line));

    } else {
        cmd = GraphicView::InterpretManipulator(m);
    }
    return cmd;
}