GraphicsPath *GraphicsPathFromPathData(const char *s)
{
    VecSegmented<SvgPathInstr> instr;
    if (!ParseSvgPathData(s, instr))
        return nullptr;
    GraphicsPath *gp = ::new GraphicsPath();
    PointF prevEnd(0.f, 0.f);
    for (SvgPathInstr& i : instr) {
        PathInstrType type = i.type;

        // convert relative coordinates to absolute based on end position of
        // previous element
        // TODO: support the rest of instructions
        if (MoveRel == type) {
            RelPointToAbs(prevEnd, i.v);
            type = MoveAbs;
        } else if (LineToRel == type) {
            RelPointToAbs(prevEnd, i.v);
            type = LineToAbs;
        } else if (HLineRel == type) {
            RelXToAbs(prevEnd, i.v);
            type = HLineAbs;
        } else if (VLineRel == type) {
            RelYToAbs(prevEnd, i.v);
            type = VLineAbs;
        }

        if (MoveAbs == type) {
            PointF p(i.v[0], i.v[1]);
            prevEnd = p;
            gp->StartFigure();
        } else if (LineToAbs == type) {
            PointF p(i.v[0], i.v[1]);
            gp->AddLine(prevEnd, p);
            prevEnd = p;
        } else if (HLineAbs == type) {
            PointF p(prevEnd);
            p.X = i.v[0];
            gp->AddLine(prevEnd, p);
            prevEnd = p;
        } else if (VLineAbs == type) {
            PointF p(prevEnd);
            p.Y = i.v[0];
            gp->AddLine(prevEnd, p);
            prevEnd = p;
        } else if ((Close == type) || (Close2 == type)) {
            gp->CloseFigure();
        } else {
            CrashIf(true);
        }
    }
    return gp;
}