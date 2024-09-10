/**
 *  Draw Torso.
 *
 *  This function draws a box that represents the torso of the
 *  player.
 */
void NeutralModel :: drawTorso ()
{
    Vector3D a;
    Vector3D b;
    Vector3D c;
    Vector3D d;

    Vector3D ab;
    Vector3D ac;

    Vector3D n;

    a = Vector3D (joint[LSHOULDER]);
    b = Vector3D (joint[RSHOULDER]);
    c = Vector3D (joint[RHIP]);
    d = Vector3D (joint[LHIP]);

    ab = b - a;
    ac = c - a;

    n = ab.cross(ac);
    n.normalize();

    glPushMatrix();
        glBegin(GL_QUADS);
            glNormal3f(n.x, n.y, n.z);
            glVertex3f(a.x, a.y, a.z);
            glVertex3f(b.x, b.y, b.z);
            glVertex3f(c.x, c.y, c.z);
            glVertex3f(d.x, d.y, d.z);
        glEnd();
    glPopMatrix();
}