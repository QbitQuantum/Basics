void DatasetPlane::draw( QMatrix4x4 pMatrix, QMatrix4x4 mvMatrix, int width, int height, int renderMode, QString target )
{
    if ( !properties( target ).get( Fn::Property::D_ACTIVE ).toBool() )
    {
        return;
    }

    QVector3D h0 = m_properties["maingl"].get( Fn::Property::D_HANDLE_0 ).value<QVector3D>();
    QVector3D h1 = m_properties["maingl"].get( Fn::Property::D_HANDLE_1 ).value<QVector3D>();
    QVector3D h2 = m_properties["maingl"].get( Fn::Property::D_HANDLE_2 ).value<QVector3D>();

    if ( m_properties["maingl"].get( Fn::Property::D_SHOW_PLANE_HANDLES ).toBool() )
    {
        QColor color = m_properties["maingl"].get( Fn::Property::D_HANDLE_COLOR ).value<QColor>();
        color.setAlpha( 254 );
        GLFunctions::renderSphere( pMatrix, mvMatrix, h0.x(), h0.y(), h0.z(), 5, 5, 5,
                                  color, m_handle0, width, height, renderMode );
        GLFunctions::renderSphere( pMatrix, mvMatrix, h1.x(), h1.y(), h1.z(), 5, 5, 5,
                                  color, m_handle1, width, height, renderMode );
        GLFunctions::renderSphere( pMatrix, mvMatrix, h2.x(), h2.y(), h2.z(), 5, 5, 5,
                                  color, m_handle2, width, height, renderMode );
    }

    if ( dirty )
    {
        initGeometry();
    }

    float alpha = GLFunctions::sliceAlpha[target];

    switch ( renderMode )
    {
        case 0:
            break;
        case 1:
        {
            if ( alpha < 1.0 ) // obviously not opaque
            {
                return;
            }
            break;
        }
        default:
        {
            if ( alpha == 1.0  ) // not transparent
            {
                return;
            }
            break;
        }
    }

    if ( !GLFunctions::setupTextures() )
    {
        return;
    }
    QGLShaderProgram* program = GLFunctions::getShader( "slice" );

    program->bind();
    GLFunctions::f->glBindBuffer( GL_ARRAY_BUFFER, vbo0 );

    intptr_t offset = 0;
    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation( "a_position" );
    program->enableAttributeArray( vertexLocation );
    GLFunctions::f->glVertexAttribPointer( vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void *) offset );

    // Set modelview-projection matrix
    program->setUniformValue( "mvp_matrix", pMatrix * mvMatrix );

    program->setUniformValue( "u_alpha", alpha );
    program->setUniformValue( "u_renderMode", renderMode );
    program->setUniformValue( "u_canvasSize", width, height );
    program->setUniformValue( "D0", 9 );
    program->setUniformValue( "D1", 10 );
    program->setUniformValue( "D2", 11 );
    program->setUniformValue( "P0", 12 );

    GLFunctions::setTextureUniforms( program, target );

    // Draw cube geometry using indices from VBO 0
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
    GLFunctions::f->glBindBuffer( GL_ARRAY_BUFFER, 0 );

}