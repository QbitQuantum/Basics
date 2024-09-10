ExprQuaternion ExprQuaternion::Times(ExprQuaternion b) {
    Expr *sa = w, *sb = b.w;
    ExprVector va = { vx, vy, vz };
    ExprVector vb = { b.vx, b.vy, b.vz };

    ExprQuaternion r;
    r.w = (sa->Times(sb))->Minus(va.Dot(vb));
    ExprVector vr = vb.ScaledBy(sa).Plus(
                    va.ScaledBy(sb).Plus(
                    va.Cross(vb)));
    r.vx = vr.x;
    r.vy = vr.y;
    r.vz = vr.z;
    return r;
}