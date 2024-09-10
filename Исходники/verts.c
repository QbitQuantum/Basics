boolean Vertices::GetPoint (int index, Coord& px, Coord& py) {
    if (index<0 || index>=count()) return false;
    Coord tx, ty;
    Transformer t;
    tx = x()[index];
    ty = y()[index];
    TotalTransformation(t);
    t.Transform(tx, ty, px, py);
    return true;
}