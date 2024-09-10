GLint gluUnProject( GLdouble winx, GLdouble winy, GLdouble winz, const F64 *model, const F64 * proj, const GLint * vp, F64 * x, F64 * y, F64 * z )
{
    Vector4F v = Vector4F( 2.0f*(winx-vp[0])/vp[2] - 1.0f, 2.0f*(winy-vp[1])/vp[2] - 1.0f, 2.0f*vp[2] - 1.0f, 1.0f );
    MatrixF pmat = MatrixF( false );
    for (int i=0; i<16; i++) { ((F32*)pmat)[i] = (float)proj[i]; }
    MatrixF mmat = MatrixF( false );
    for (int i=0; i<16; i++) { ((F32*)mmat)[i] = (float)model[i]; }
    mmat = pmat.mul(mmat);

    mmat = mmat.inverse();
    mmat.mul( v );
    *x = v.x;
    *y = v.y;
    *z = v.z;
    int glError;
    glError = TEST_FOR_OPENGL_ERRORS
    return GL_TRUE;
}