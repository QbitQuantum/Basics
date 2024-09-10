void LVL_Block::render(double camX, double camY)
{
    //Don't draw hidden block before it will be hitten
    if(isHidden) return;
    if(destroyed) return;

    PGE_RectF blockG;
    blockG.setRect(posX()-camX+offset_x,
                         posY()-camY+offset_y,
                         _width,
                         _height);


    AniPos x(0,1);

    if(animated) //Get current animated frame
        x = ConfigManager::Animator_Blocks[animator_ID].image();

    glEnable(GL_TEXTURE_2D);
    glColor4f( 1.f, 1.f, 1.f, 1.f);

    glBindTexture( GL_TEXTURE_2D, texId );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if(sizable)
    {
        int w = _width;
        int h = _height;

        int x,y, x2, y2, i, j;
        int hc, wc;

        x = qRound(qreal(texture.w)/3);  // Width of one piece
        y = qRound(qreal(texture.h)/3); // Height of one piece

        //Double size
        x2 = x<<1;
        y2 = y<<1;

        int pWidth = texture.w-x2;//Width of center piece
        int pHeight = texture.h-y2;//Height of center piece

        int fLnt = 0; // Free Lenght
        int fWdt = 0; // Free Width

        int dX=0; //Draw Offset. This need for crop junk on small sizes
        int dY=0;

        if(w < x2) dX = (x2-w)>>1; else dX=0;
        if(h < y2) dY = (y2-h)>>1; else dY=0;