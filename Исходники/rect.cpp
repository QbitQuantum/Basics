Command* RectView::InterpretManipulator (Manipulator* m) {
    DragManip* dm = (DragManip*) m;
    Editor* ed = dm->GetViewer()->GetEditor();
    Tool* tool = dm->GetTool();
    Transformer* rel = dm->GetTransformer();
    Command* cmd = nil;

    if (tool->IsA(GRAPHIC_COMP_TOOL)) {
        RubberRect* rr = (RubberRect*) dm->GetRubberband();
        Coord x0, y0, x1, y1;
        rr->GetCurrent(x0, y0, x1, y1);

        if (x0 != x1 || y0 != y1) {
            BrushVar* brVar = (BrushVar*) ed->GetState("BrushVar");
            PatternVar* patVar = (PatternVar*) ed->GetState("PatternVar");
            ColorVar* colVar = (ColorVar*) ed->GetState("ColorVar");

            if (rel != nil) {
                rel = new Transformer(rel);
                rel->Invert();
            }

            Graphic* pg = GetGraphicComp()->GetGraphic();
            SF_Rect* rect = new SF_Rect(x0, y0, x1, y1, pg);

            if (brVar != nil) rect->SetBrush(brVar->GetBrush());
            if (patVar != nil) rect->SetPattern(patVar->GetPattern());

            if (colVar != nil) {
                rect->SetColors(colVar->GetFgColor(), colVar->GetBgColor());
            }
            rect->SetTransformer(rel);
            Unref(rel);
            cmd = new PasteCmd(ed, new Clipboard(new RectComp(rect)));
        }

    } else if (tool->IsA(RESHAPE_TOOL)) {
        RubberGroup* rubberGroup = (RubberGroup*) dm->GetRubberband();
	RubberLine* rubberLine = (RubberLine*) rubberGroup->First();
        SF_Polygon* polygon;
        Coord x[4], y[4];
	Coord x0, y0;
        
	GetCorners(x, y);
	rubberLine->GetCurrent(x0, y0, x[_reshapeCorner], y[_reshapeCorner]);

        if (rel != nil) {
            rel = new Transformer(rel);
            rel->Invert();
        }
        polygon = new SF_Polygon(x, y, 4, GetGraphic());
        polygon->SetTransformer(rel);
        Unref(rel);
        cmd = new ReplaceCmd(ed, new PolygonComp(polygon));

    } else if (tool->IsA(MOVE_TOOL)) {
        SlidingLineList* sll;
        Transformer* rel = dm->GetTransformer();
        Coord* ox, *oy, *cx, *cy;
        float fx0, fy0, fx1, fy1;
        int n;

        sll = (SlidingLineList*) dm->GetRubberband();
        sll->GetOriginal(ox, oy, n);
        sll->GetCurrent(cx, cy, n);
        if (rel != nil) {
            rel->InvTransform(float(ox[0]), float(oy[0]), fx0, fy0);
            rel->InvTransform(float(cx[0]), float(cy[0]), fx1, fy1);
        }
        delete ox; delete oy; delete cx; delete cy;
        cmd = new MoveCmd(ed, fx1 - fx0, fy1 - fy0);

    } else if (tool->IsA(SCALE_TOOL)) {
        ScalingLineList* sll = (ScalingLineList*) dm->GetRubberband();
        float sxy = sll->CurrentScaling();

        cmd = new ScaleCmd(ed, sxy, sxy);

    } else if (tool->IsA(ROTATE_TOOL)) {
        RotatingLineList* rll = (RotatingLineList*) dm->GetRubberband();
        float angle = rll->CurrentAngle() - rll->OriginalAngle();

        cmd = new RotateCmd(ed, angle);

    } else {
        cmd = GraphicView::InterpretManipulator(m);
    }
    return cmd;
}