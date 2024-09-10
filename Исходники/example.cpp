void display()
{
    using namespace Eigen;
    using namespace igl;
    using namespace std;

    glClearColor(back[0],back[1],back[2],0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(is_animating)
    {
        double t = (get_seconds() - animation_start_time)/ANIMATION_DURATION;
        if(t > 1)
        {
            t = 1;
            is_animating = false;
        }
        const Quaterniond q = animation_from_quat.slerp(t,animation_to_quat).normalized();
        s.camera.orbit(q.conjugate());
    }

    glDisable(GL_LIGHTING);
    lights();
    push_scene();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    push_object();

    // Draw the model
    // Set material properties
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,tex_id);
    MatrixXd _d;
    MatrixXi _i;

    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();
    if(flip_y)
    {
        glTranslated(0,1,0);
        glScaled(1,-1,1);
    }
    if(rotate_xy)
    {
        glRotated(90,0,0,1);
        glTranslated(-1,0,0);
    }
    glMatrixMode(GL_MODELVIEW);

    igl::opengl2::draw_mesh(V,F,N,MatrixXi(),MatrixXd(),TC,TF,MatrixXd(),0,MatrixXi(),0);

    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    pop_object();


    // Draw a nice floor
    glPushMatrix();
    const double floor_offset =
        -2./bbd*(V.col(1).maxCoeff()-mid(1));
    glTranslated(0,floor_offset,0);
    const float GREY[4] = {0.5,0.5,0.6,1.0};
    const float DARK_GREY[4] = {0.2,0.2,0.3,1.0};

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-1,1);
    glBegin(GL_QUADS);
    glNormal3d(0,1,0);
    glTexCoord2d(0,1);
    glVertex3d(-1,0,1);
    glTexCoord2d(1,1);
    glVertex3d(1,0,1);
    glTexCoord2d(1,0);
    glVertex3d(1,0,-1);
    glTexCoord2d(0,0);
    glVertex3d(-1,0,-1);
    glEnd();
    glDisable(GL_POLYGON_OFFSET_FILL);
    glDisable(GL_TEXTURE_2D);

    igl::opengl2::draw_floor(GREY,DARK_GREY);
    glPopMatrix();

    pop_scene();

    igl::opengl::report_gl_error();

    TwDraw();
    glutSwapBuffers();
    if(is_animating)
    {
        glutPostRedisplay();
    }
}