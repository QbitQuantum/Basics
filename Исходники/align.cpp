void AlignToGridCmd::Align (GraphicView* gv, float refx, float refy) {
    MoveData* md = (MoveData*) Recall(gv->GetGraphicComp());

    if (md == nil) {
        Viewer* v = gv->GetViewer();
        Grid* grid = (v == nil) ? nil : v->GetGrid();

        if (grid == nil) {
            return;
        }

        Graphic* g = gv->GetGraphic();
        Transformer t;
        g->Parent()->TotalTransformation(t);
        t.Invert();

        Coord cx = iv26_round(refx);
        Coord cy = iv26_round(refy);

        grid->Constrain(cx, cy);

        float dx, dy, trefx, trefy;

        t.Transform(float(cx), float(cy), dx, dy);
        t.Transform(refx, refy, trefx, trefy);

        dx -= trefx;
        dy -= trefy;
        Store(gv->GetGraphicComp(), new MoveData(dx, dy));

    }
    Move(gv->GetGraphicComp());
}