void SliceRenderer::draw( QMatrix4x4 p_matrix, QMatrix4x4 mv_matrix, int width, int height, int renderMode, QString target )
{
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
    // Set modelview-projection matrix
    program->setUniformValue( "mvp_matrix", p_matrix * mv_matrix );

    program->setUniformValue( "u_alpha", alpha );
    program->setUniformValue( "u_renderMode", renderMode );
    program->setUniformValue( "u_canvasSize", width, height );
    program->setUniformValue( "D0", 9 );
    program->setUniformValue( "D1", 10 );
    program->setUniformValue( "D2", 11 );
    program->setUniformValue( "P0", 12 );

    float pAlpha =  1.0;
    float green = 0.0f;
    float red =   0.0f;

    initGeometry();
    if ( Models::getGlobal( Fn::Property::G_SHOW_AXIAL ).toBool() )
    {
        float blue =  (float)(( 1 ) & 0xFF) / 255.f;
        GLFunctions::getShader( "slice" )->setUniformValue( "u_pickColor", red, green , blue, pAlpha );
        drawAxial( target );
    }
    if ( Models::getGlobal( Fn::Property::G_SHOW_CORONAL ).toBool() )
    {
        float blue =  (float)(( 2 ) & 0xFF) / 255.f;
        GLFunctions::getShader( "slice" )->setUniformValue( "u_pickColor", red, green , blue, pAlpha );
        drawCoronal( target );
    }
    if ( Models::getGlobal( Fn::Property::G_SHOW_SAGITTAL ).toBool() )
    {
        float blue =  (float)(( 3 ) & 0xFF) / 255.f;
        GLFunctions::getShader( "slice" )->setUniformValue( "u_pickColor", red, green , blue, pAlpha );
        drawSagittal( target );
    }
}