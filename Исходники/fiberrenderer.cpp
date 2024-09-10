void FiberRenderer::draw( QMatrix4x4 p_matrix, QMatrix4x4 mv_matrix, int width, int height, int renderMode, PropertyGroup* props )
{
    float alpha = props->get( Fn::Property::ALPHA ).toFloat();
    if ( renderMode != 1 ) // we are not picking
    {
        if ( renderMode == 4 || renderMode == 5 ) // we are drawing opaque objects
        {
            if ( alpha < 1.0 )
            {
                // obviously not opaque
                return;
            }
        }
        else // we are drawing tranparent objects
        {
            if ( !(alpha < 1.0 ) )
            {
                // not transparent
                return;
            }
        }
    }

    QGLShaderProgram* program = GLFunctions::getShader( "fiber" );
    program->bind();

    GLFunctions::setupTextures();
    GLFunctions::setTextureUniforms( GLFunctions::getShader( "fiber" ) );

    // Set modelview-projection matrix
    program->setUniformValue( "mvp_matrix", p_matrix * mv_matrix );
    program->setUniformValue( "mv_matrixInvert", mv_matrix.inverted() );

    initGeometry();

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vboIds[ 0 ] );
    glBindBuffer( GL_ARRAY_BUFFER, vboIds[ 1 ] );
    setShaderVars( props );

    program->setUniformValue( "u_alpha", alpha );
    program->setUniformValue( "u_renderMode", renderMode );
    program->setUniformValue( "u_canvasSize", width, height );
    program->setUniformValue( "D0", 9 );
    program->setUniformValue( "D1", 10 );
    program->setUniformValue( "D2", 11 );

    glLineWidth( props->get( Fn::Property::FIBER_THICKNESS ).toFloat() );

    QVector<bool>*selected = m_selector->getSelection();

    if ( props->get( Fn::Property::COLORMODE ).toInt() != 2 )
    {
        for ( int i = 0; i < m_data.size(); ++i )
        {
            if ( selected->at( i ) )
            {
                glDrawArrays( GL_LINE_STRIP, m_startIndexes[i], m_pointsPerLine[i] );
            }
        }
    }
    else
    {
        for ( int i = 0; i < m_data.size(); ++i )
        {
            if ( selected->at( i ) )
            {
                program->setUniformValue( "u_color", m_colorField[i].redF(),
                                                                                 m_colorField[i].greenF(),
                                                                                 m_colorField[i].blueF(), 1.0 );
                glDrawArrays( GL_LINE_STRIP, m_startIndexes[i], m_pointsPerLine[i] );
            }
        }
    }

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}