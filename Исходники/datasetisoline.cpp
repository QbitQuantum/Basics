void DatasetIsoline::draw( QMatrix4x4 pMatrix, QMatrix4x4 mvMatrix, int width, int height, int renderMode, QString target )
{
    bool renderAnySlice =  m_properties["maingl"].get( Fn::Property::D_RENDER_AXIAL ).toBool() ||
                           m_properties["maingl"].get( Fn::Property::D_RENDER_CORONAL ).toBool() ||
                           m_properties["maingl"].get( Fn::Property::D_RENDER_SAGITTAL ).toBool();
    if ( !properties( target ).get( Fn::Property::D_ACTIVE ).toBool() || ! renderAnySlice )
    {
        return;
    }

    if ( m_dirty )
    {
        initGeometry();
    }

    float alpha = 1.0; //GLFunctions::sliceAlpha[target];

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

    QGLShaderProgram* program = GLFunctions::getShader( "stipple" );

    if ( ( m_vertCountAxial + m_vertCountCoronal + m_vertCountSagittal ) > 0 )
    {
        program->bind();

        intptr_t offset = 0;
        // Tell OpenGL programmable pipeline how to locate vertex position data
        GLFunctions::f->glBindBuffer( GL_ARRAY_BUFFER, vbo0 );

        int vertexLocation = program->attributeLocation( "a_position" );
        program->enableAttributeArray( vertexLocation );
        GLFunctions::f->glVertexAttribPointer( vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *) offset );

        offset += sizeof(float) * 3;
        int offsetLocation = program->attributeLocation( "a_vec" );
        program->enableAttributeArray( offsetLocation );
        GLFunctions::f->glVertexAttribPointer( offsetLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *) offset );

        offset += sizeof(float) * 3;
        int dirLocation = program->attributeLocation( "a_dir2" );
        program->enableAttributeArray( dirLocation );
        GLFunctions::f->glVertexAttribPointer( dirLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *) offset );
        GLFunctions::f->glBindBuffer( GL_ARRAY_BUFFER, 0 );

        GLFunctions::f->glBindBuffer( GL_ARRAY_BUFFER, vbo1 );
        int colorLocation = program->attributeLocation( "a_color" );
        program->enableAttributeArray( colorLocation );
        GLFunctions::f->glVertexAttribPointer( colorLocation, 4, GL_FLOAT, GL_FALSE, 0, 0 );
        GLFunctions::f->glBindBuffer( GL_ARRAY_BUFFER, 0 );

        // Set modelview-projection matrix
        program->setUniformValue( "mvp_matrix", pMatrix * mvMatrix );
        program->setUniformValue( "u_scaling", 1.0f );

        program->setUniformValue( "u_alpha", 1.0f );
        program->setUniformValue( "u_renderMode", renderMode );
        program->setUniformValue( "u_canvasSize", width, height );
        program->setUniformValue( "D0", 9 );
        program->setUniformValue( "D1", 10 );
        program->setUniformValue( "D2", 11 );
        program->setUniformValue( "P0", 12 );

        program->setUniformValue( "u_aVec", 1., 0., 0. );
        program->setUniformValue( "u_bVec", 0., 1., 0. );
        program->setUniformValue( "u_orient", 0 );

        program->setUniformValue( "u_glyphThickness", m_properties["maingl"].get( Fn::Property::D_LINE_WIDTH ).toFloat() );
        program->setUniformValue( "u_glyphSize", m_properties["maingl"].get( Fn::Property::D_STIPPLE_GLYPH_SIZE ).toFloat() );
        program->setUniformValue( "u_constantThickness", true );

        if ( m_properties["maingl"].get( Fn::Property::D_RENDER_AXIAL ).toBool() && m_vertCountAxial > 0 )
        {
            glDrawArrays( GL_TRIANGLES, 0, m_vertCountAxial );
            GLFunctions::getAndPrintGLError( "render stipples: opengl error" );
        }

        if ( m_properties["maingl"].get( Fn::Property::D_RENDER_CORONAL ).toBool() && m_vertCountCoronal > 0 )
        {
            program->setUniformValue( "u_aVec", 1., 0., 0. );
            program->setUniformValue( "u_bVec", 0., 0., 1. );
            program->setUniformValue( "u_orient", 1 );

            glDrawArrays( GL_TRIANGLES, m_vertCountAxial, m_vertCountCoronal );
            GLFunctions::getAndPrintGLError( "render stipples: opengl error" );
        }

        if ( m_properties["maingl"].get( Fn::Property::D_RENDER_SAGITTAL ).toBool() && m_vertCountSagittal > 0 )
        {
            program->setUniformValue( "u_aVec", 0., 1., 0. );
            program->setUniformValue( "u_bVec", 0., 0., 1. );
            program->setUniformValue( "u_orient", 2 );

            glDrawArrays( GL_TRIANGLES, m_vertCountAxial + m_vertCountCoronal, m_vertCountSagittal );
            GLFunctions::getAndPrintGLError( "render stipples: opengl error" );
        }
    }

    if ( ( m_stripeVertCountAxial + m_stripeVertCountCoronal + m_stripeVertCountSagittal ) > 0 )
    {
        program->bind();

        intptr_t offset = 0;
        // Tell OpenGL programmable pipeline how to locate vertex position data
        GLFunctions::f->glBindBuffer( GL_ARRAY_BUFFER, vbo2 );

        int vertexLocation = program->attributeLocation( "a_position" );
        program->enableAttributeArray( vertexLocation );
        GLFunctions::f->glVertexAttribPointer( vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *) offset );

        offset += sizeof(float) * 3;
        int offsetLocation = program->attributeLocation( "a_vec" );
        program->enableAttributeArray( offsetLocation );
        GLFunctions::f->glVertexAttribPointer( offsetLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *) offset );

        offset += sizeof(float) * 3;
        int dirLocation = program->attributeLocation( "a_dir2" );
        program->enableAttributeArray( dirLocation );
        GLFunctions::f->glVertexAttribPointer( dirLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *) offset );
        GLFunctions::f->glBindBuffer( GL_ARRAY_BUFFER, 0 );

        GLFunctions::f->glBindBuffer( GL_ARRAY_BUFFER, vbo3 );
        int colorLocation = program->attributeLocation( "a_color" );
        program->enableAttributeArray( colorLocation );
        GLFunctions::f->glVertexAttribPointer( colorLocation, 4, GL_FLOAT, GL_FALSE, 0, 0 );
        GLFunctions::f->glBindBuffer( GL_ARRAY_BUFFER, 0 );

        // Set modelview-projection matrix
        program->setUniformValue( "mvp_matrix", pMatrix * mvMatrix );
        program->setUniformValue( "u_scaling", 1.0f );

        program->setUniformValue( "u_alpha", 1.0f );
        program->setUniformValue( "u_renderMode", renderMode );
        program->setUniformValue( "u_canvasSize", width, height );
        program->setUniformValue( "D0", 9 );
        program->setUniformValue( "D1", 10 );
        program->setUniformValue( "D2", 11 );
        program->setUniformValue( "P0", 12 );

        program->setUniformValue( "u_aVec", 1., 0., 0. );
        program->setUniformValue( "u_bVec", 0., 1., 0. );
        program->setUniformValue( "u_orient", 0 );

        program->setUniformValue( "u_glyphThickness", m_properties["maingl"].get( Fn::Property::D_ISOLINE_STRIPES_WIDTH ).toFloat() );
        program->setUniformValue( "u_glyphSize", m_properties["maingl"].get( Fn::Property::D_STIPPLE_GLYPH_SIZE ).toFloat() );
        program->setUniformValue( "u_constantThickness", true );

        if ( m_properties["maingl"].get( Fn::Property::D_RENDER_AXIAL ).toBool() && m_stripeVertCountAxial > 0 )
        {
            glDrawArrays( GL_TRIANGLES, 0, m_stripeVertCountAxial );
            GLFunctions::getAndPrintGLError( "render stipples: opengl error" );
        }

        if ( m_properties["maingl"].get( Fn::Property::D_RENDER_CORONAL ).toBool() && m_stripeVertCountCoronal > 0 )
        {
            program->setUniformValue( "u_aVec", 1., 0., 0. );
            program->setUniformValue( "u_bVec", 0., 0., 1. );
            program->setUniformValue( "u_orient", 1 );

            glDrawArrays( GL_TRIANGLES, m_stripeVertCountAxial, m_stripeVertCountCoronal );
            GLFunctions::getAndPrintGLError( "render stipples: opengl error" );
        }

        if ( m_properties["maingl"].get( Fn::Property::D_RENDER_SAGITTAL ).toBool() && m_stripeVertCountSagittal > 0 )
        {
            program->setUniformValue( "u_aVec", 0., 1., 0. );
            program->setUniformValue( "u_bVec", 0., 0., 1. );
            program->setUniformValue( "u_orient", 2 );

            glDrawArrays( GL_TRIANGLES, m_stripeVertCountAxial + m_stripeVertCountCoronal, m_stripeVertCountSagittal );
            GLFunctions::getAndPrintGLError( "render stipples: opengl error" );
        }
    }
}