void NodeRendererEvent::render( const Eigen::Matrix4f& view, const Eigen::Matrix4f& model )
{
    glPushMatrix();
    glMultMatrixf( ( model * view ).array() );

    glColor3f( 1.0f, 1.0f, 0.0f );

    // render a filled elipse
    glBegin( GL_POLYGON );
    for ( float step = 0.0f; step < 2.0f * M_PI; step += 0.1f )
    {
        float x = GEOM_WIDTH * sinf( step );
        float y = GEOM_HEIGHT * cosf( step );
        glVertex3f( x, y, 0.0f );
    }
    glEnd();

    // render the border
    if ( _isHighlighted )
    {
        Eigen::Vector3f col = RenderManager::get()->getHeighlightColour();
        glColor3f( col.x(), col.y(), col.z() );
    }
    else
    {
        glColor3f( 0.3f, 0.3f, 0.0f );
    }

    glLineWidth( 8.0f );
    glBegin( GL_LINE_LOOP );
    for ( float step = 0.0f; step < 2.0f * M_PI; step += 0.05f )
    {
        float x = ( GEOM_WIDTH + 0.9f ) * sinf( step );
        float y = ( GEOM_HEIGHT + 0.9f ) * cosf( step );
        glVertex3f( x, y, 0.0f );
    }
    glEnd();

    // render the node text
    glColor3f( 0.0, 0.0, 0.0 );
    std::string text( getText() );
    if ( text.length() )
    {
        Eigen::Vector3f tmin, tmax;
        RenderManager::get()->fontGetDims( text.c_str(), tmin, tmax );

        float xpos = tmax.x() - tmin.x();
        float ypos = tmax.y() - tmin.y();
        if ( getScale().x() )
            xpos /= getScale().x();

        if ( getScale().y() )
            ypos /= getScale().y();

        Eigen::Vector2f pos( -xpos / 2.0f, -ypos / 2.0f );
        RenderManager::get()->fontRender( text.c_str(), pos );
    }

    glPopMatrix();
}