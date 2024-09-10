void GrabForeground::draw(DrawEnv *, Viewport *port)
{
    if(getActive() == false)
        return;
    
    Image *i = getImage();
    
    if(i == NULL)       // No image, no grab.
        return;

    Int32 w = osgMax(2, port->getPixelWidth ());
    Int32 h = osgMax(2, port->getPixelHeight());

    // If image is smaller than 2x2, resize it to vp size
    // the 2x2 is because you can't create 0x0 images
    // If autoResize then update img size if vp changed

    if( (i->getWidth() <= 1 || i->getHeight() <= 1) ||
         (getAutoResize() && (w != i->getWidth() || h != i->getHeight())) )
    {
        i->set(i->getPixelFormat(),
               w, 
               h);
    }
    
    bool storeChanged = false;    

    if ( !getAutoResize() )
    {
        w = osgMin(Int32(i->getWidth ()), port->getPixelWidth());
        h = osgMin(Int32(i->getHeight()), port->getPixelHeight());
        
        if(Int32(i->getWidth()) != port->getPixelWidth())
        {
            glPixelStorei(GL_PACK_ROW_LENGTH, i->getWidth());
            storeChanged = true;
        }
    }
    
    glReadPixels(port->getPixelLeft(), 
                 port->getPixelBottom(), 
                 w, 
                 h, 
                 i->getPixelFormat(),
                 i->getDataType(), 
                 i->editData());

    if(storeChanged)
        glPixelStorei(GL_PACK_ROW_LENGTH, 0);
}