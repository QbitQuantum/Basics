void draw () {
    //On récupère la matrice objet monde
    GLfloat	modl[16];
    glGetFloatv( GL_MODELVIEW_MATRIX, modl );
    GLfloat lightPos[4];
    glGetLightfv(GL_LIGHT1, GL_POSITION, lightPos);
    
    //Vec3Df lightPosition()
    const vector<Vertex> & V = mesh.V;
    const vector<Triangle> & T = mesh.T;
    glBegin (GL_TRIANGLES);
    
    for (unsigned int i = 0; i < T.size (); i++) {
        /*if(i < (unsigned int)T.size()/2){
            glColor3ub(255, 12, 4);
        }  else{    
            glColor3ub(1, 12, 200);
        }*/
        if (polygonMode != Gouraud) {
            Vec3Df e01 = V[T[i].v[1]].p -  V[T[i].v[0]].p;
            Vec3Df e02 = V[T[i].v[2]].p -  V[T[i].v[0]].p;
            Vec3Df n = Vec3Df::crossProduct (e01, e02);
            n.normalize ();
            glNormal3f (n[0], n[1], n[2]);
            //glColorMaterial(GLenum face, GLenum mode)
            //modl.V[T[i].v]
        }
        
        //glGetFloatv(GLenum pname, GLfloat *params)
        for (unsigned int j = 0; j < 3; j++) {
            const Vertex & v = V[T[i].v[j]];
            if (polygonMode == Gouraud)
                glNormal3f (v.n[0], v.n[1], v.n[2]);
            
            glVertex3f (v.p[0], v.p[1], v.p[2]);
            
        }
        
    }
    glEnd ();
}