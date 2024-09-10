//called to draw one item
void GlutGuiViewport::drawMobile( Mobile& item)
{
    //drawing a triangle
    const vec2 &pos = item.getPos();
    

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
	
    glTranslatef(pos.x, pos.y, 0);
    glRotatef( item.getAngle()*(180/M_PI), 0,0,1);
    drawIcon( item );
	
    glPopMatrix();
}