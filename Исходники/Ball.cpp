void Ball::render()
{
    Matrix4 glmatrix;
    glmatrix = model2world;
    glmatrix.transpose();
    glLoadMatrixd(glmatrix.getPointer());

    glBegin(GL_QUADS);

    glutSolidSphere(radius, 1024, 1024);

    glEnd();
}