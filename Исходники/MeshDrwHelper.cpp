//-*****************************************************************************
void MeshDrwHelper::draw( const DrawContext & iCtx ) const
{

    // Bail if invalid.
    if ( !m_valid || m_triangles.size() < 1 || !m_meshP )
    {
        return;
    }

    const V3f *points = m_meshP->get();
    const V3f *normals = NULL;
    if ( m_meshN  && ( m_meshN->size() == m_meshP->size() ) )
    {
        normals = m_meshN->get();
    }
    else if ( m_customN.size() == m_meshP->size() )
    {
        normals = &(m_customN.front());
    }
    
    // colors
    const C4f *colors = NULL;
    if (m_colors.size() == m_meshP->size() )
    {
        colors = &(m_colors.front());

    }

    static MGLFunctionTable *gGLFT = NULL;
    if (gGLFT == NULL)
       gGLFT = MHardwareRenderer::theRenderer()->glFunctionTable();

    gGLFT->glBegin( MGL_TRIANGLES );

    for ( size_t i = 0; i < m_triangles.size(); ++i )
    {
        const Tri &tri = m_triangles[i];
        const V3f &vertA = points[tri[0]];
        const V3f &vertB = points[tri[1]];
        const V3f &vertC = points[tri[2]];

        if ( normals )
        {
            const V3f &normA = normals[tri[0]];
            gGLFT->glNormal3fv( ( const GLfloat * )&normA );
            gGLFT->glVertex3fv( ( const GLfloat * )&vertA );

            const V3f &normB = normals[tri[1]];
            gGLFT->glNormal3fv( ( const GLfloat * )&normB );
            gGLFT->glVertex3fv( ( const GLfloat * )&vertB );

            const V3f &normC = normals[tri[2]];
            gGLFT->glNormal3fv( ( const GLfloat * )&normC );
            gGLFT->glVertex3fv( ( const GLfloat * )&vertC );
        }
        else
        {
            V3f AB = vertB - vertA;
            V3f AC = vertC - vertA;
            V3f N = AB.cross( AC );
            if ( N.length() > 1.0e-4f )
            {
                N.normalize();
                gGLFT->glNormal3fv( ( const GLfloat * )&N );
            }

            gGLFT->glVertex3fv( ( const GLfloat * )&vertA );

            gGLFT->glVertex3fv( ( const GLfloat * )&vertB );

            gGLFT->glVertex3fv( ( const GLfloat * )&vertC );
        }

    }

    gGLFT->glEnd();

}