void
QuantumFlash::UpdateVerts(const Point& cam_pos)
{
    if (length < radius) {
        length += radius/80;
        width  += 1;
    }

    for (int i = 0; i < npolys; i++) {
        Matrix& m = beams[i];
        
        m.Yaw(0.05);
        Point vpn = Point(m(2,0), m(2,1), m(2,2));

        Point head  = loc;
        Point tail  = loc - vpn * length;
        Point vtail = tail - head;
        Point vcam  = cam_pos - loc;
        Point vtmp  = vcam.cross(vtail);
        vtmp.Normalize();
        Point vlat  = vtmp * -width;

        verts->loc[4*i+0] = head + vlat;
        verts->loc[4*i+1] = tail + vlat * 8;
        verts->loc[4*i+2] = tail - vlat * 8;
        verts->loc[4*i+3] = head - vlat;

        DWORD color = D3DCOLOR_RGBA((BYTE) (255*shade), (BYTE) (255*shade), (BYTE) (255*shade), 255);

        for (int n = 0; n < 4; n++) {
            verts->diffuse[4*i+n] = color;
        }
    }
}