Matrix33F Patch::tangentFrame() const
{
    Matrix33F frm;
    Vector3F du = (vertex(1) - vertex(0) + vertex(2) - vertex(3)) * .5f;
    Vector3F dv = (vertex(3) - vertex(0) + vertex(2) - vertex(1)) * .5f;
    du.normalize();
    dv.normalize();
    
    Vector3F side = du.cross(dv);
    side.normalize();
    
    Vector3F up = du.cross(side);
    up.normalize();
    
    frm.fill(side, up, du);
    return frm;
}