void draw() {
    // clear the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // make modelview matrix active
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Define a viewing transformation
    //gluLookAt(0, 0, -15, 0, 0, 0, 0, -1, 0);

    // use different lighting on the different geometry
    light01_diffuse[0] = 1.0;
    light01_diffuse[1] = 1.0;
    light01_diffuse[2] = 1.0;
    setLights();


    glPushMatrix();
    gluLookAt(0, 0, 150, 0, 0, 0, 0, -1, 0);
    glTranslatef(transX, transY, transZ);
    glRotatef(liveRotX, 0, 1, 0);
    glRotatef(liveRotY, 1, 0, 0);

    // Rendering state utils
    //glDisable(GL_TEXTURE_2D);
    //shader.bind();
    //shader.unbind();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    // glShadeModel(GL_FLAT);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //    spline01.display();
    //    spline01.displayControlPts();
    //    spline01.displayInterpPts();

    //tube.display(GeomBase::VERTEX_BUFFER_OBJECT, GeomBase::SURFACE);

    //glScalef(5, 5, 5);
    shader.bind();
    helix.display();
    shader.unbind();
    
    //sphere.display();
    glPopMatrix();

}