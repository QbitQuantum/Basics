void Graphic::Align (Alignment falign, Graphic* moved, Alignment malign) {
    float fx0, fy0, fx1, fy1, mx0, my0, mx1, my1, dx = 0, dy = 0;

    GetBounds(fx0, fy0, fx1, fy1);
    moved->GetBounds(mx0, my0, mx1, my1);

    switch (falign) {
    case BottomLeft:
    case CenterLeft:
    case TopLeft:
    case Left:
        dx = fx0;
        break;
    case BottomCenter:
    case Center:
    case TopCenter:
    case HorizCenter:
        dx = (fx0 + fx1 + 1)/2;
        break;
    case BottomRight:
    case CenterRight:
    case TopRight:
    case Right:
        dx = fx1 + 1;
        break;
    }
    switch (falign) {
    case BottomLeft:
    case BottomCenter:
    case BottomRight:
    case Bottom:
        dy = fy0;
        break;
    case CenterLeft:
    case Center:
    case CenterRight:
    case VertCenter:
        dy = (fy0 + fy1 + 1)/2;
        break;
    case TopLeft:
    case TopCenter:
    case TopRight:
    case Top:
        dy = fy1 + 1;
        break;
    }

    switch (malign) {
    case BottomLeft:
    case CenterLeft:
    case TopLeft:
    case Left:
        dx -= mx0;
        break;
    case BottomCenter:
    case Center:
    case TopCenter:
    case HorizCenter:
        dx -= (mx0 + mx1 + 1)/2;
        break;
    case BottomRight:
    case CenterRight:
    case TopRight:
    case Right:
        dx -= (mx1 + 1);
        break;
    }
    switch (malign) {
    case BottomLeft:
    case BottomCenter:
    case BottomRight:
    case Bottom:
        dy -= my0;
        break;
    case CenterLeft:
    case Center:
    case CenterRight:
    case VertCenter:
        dy -= (my0 + my1 + 1)/2;
        break;
    case TopLeft:
    case TopCenter:
    case TopRight:
    case Top:
        dy -= (my1 + 1);
        break;
    }
    if (dx != 0 || dy != 0) {
        Transformer parents;
        moved->parentXform(parents);

        parents.Invert();
        parents.Transform(0.0, 0.0, fx0, fy0);
        parents.Transform(dx, dy, mx0, my0);

        moved->Translate(mx0-fx0, my0-fy0);
    }
}