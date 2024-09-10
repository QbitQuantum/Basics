void RenderBuffer::processPreDeactivate (DrawEnv *pEnv, UInt32 index)
{
    if(_sfReadBack.getValue() == true)
    {
        Image *pImg = this->getImage();
        
        if(pImg == NULL)
            return;
                           
        if(pImg->getData() == NULL)
        {
            SINFO << "TextureBuffer::render: (Re)Allocating image "
                  << "for read-back."
                  << endLog;
            
            pImg->set(pImg->getPixelFormat(),
                      pImg->getWidth      (),
                      pImg->getHeight     ());
        }
       
        // select GL_COLORATTACHMENTn and read data into image
        glReadBuffer(index);
        glReadPixels(0, 0, 
                     pImg->getWidth      (), 
                     pImg->getHeight     (),
                     pImg->getPixelFormat(), 
                     pImg->getDataType   (),
                     pImg->editData      ());

        glReadBuffer(GL_NONE);

        glErr("renderbuffer:predeactivate");
    }
}