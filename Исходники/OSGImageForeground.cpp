void ImageForeground::draw(DrawActionBase *, Viewport *vp)
{
    if(getActive() == false)
        return;

    UInt16 i;
    
    for(i = 0; i < getMFPositions()->size(); i++)
    {
        if(getImages(i) != NullFC)
            break;
    }
    
    if(i == getMFPositions()->size())   // all images == NULL?
        return; 

    glPushAttrib(GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT | 
                 GL_LIGHTING_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDisable(GL_DEPTH_TEST);

    glDisable(GL_COLOR_MATERIAL);

    glDisable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 0, 1);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    float vpWidth = 1.0, vpHeight = 1.0;
    if(vp)
    {
        // for absolute pixel position
        vpWidth  = 1.0/vp->getPixelWidth();
        vpHeight = 1.0/vp->getPixelHeight();
    }

    for(i = 0; i < getMFPositions()->size(); i++)
    {
        ImagePtr img = getImages(i);

        if(img == NullFC)
            continue;

        Pnt2f p = getPositions(i);
        if( p[0] >= 1.0 || p[1] >= 1.0 )
            glRasterPos2f(p[0]*vpWidth, p[1]*vpHeight); // absolute position
        else
            glRasterPos2f(p[0], p[1]); // relative position

        glDrawPixels(img->getWidth(), img->getHeight(),
                     img->getPixelFormat(), GL_UNSIGNED_BYTE,
                     img->getData());
    }
    glDisable(GL_BLEND);
        

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
}