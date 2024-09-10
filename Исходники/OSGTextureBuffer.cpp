void TextureBuffer::processPreDeactivate(DrawEnv *pEnv, UInt32 index)
{
    if(_sfReadBack.getValue() == true)
    {
        TextureObjChunk *pTexObj = this->getTexture();
        
        if(pTexObj == NULL)
            return;
        
        Image *pTexImg = pTexObj->getImage();
                    
        if(pTexImg->getData() == NULL)
        {
            SINFO << "TextureBuffer::render: (Re)Allocating image "
                  << "for read-back."
                  << endLog;
            
            pTexImg->set(pTexImg->getPixelFormat(),
                         pTexImg->getWidth      (),
                         pTexImg->getHeight     (),
                         pTexImg->getDepth      (),
                         pTexImg->getMipMapCount(),
                         pTexImg->getFrameCount (),
                         pTexImg->getFrameDelay (),
                         NULL,
                         pTexImg->getDataType   (),
                         true,
                         pTexImg->getSideCount  () );
        }

        UInt32  mipMapLevel = _sfLevel.getValue();
        UInt32  frame       = 0;
        UInt32  side        = 0;
        GLenum  target;
        Window *pWindow = pEnv->getWindow();

        if(_sfTexTarget.getValue() != GL_NONE)
        {
            target = _sfTexTarget.getValue();
        }
        else
        {
            target = _sfTexture.getValue()->determineTextureTarget(pWindow);
        }

        switch(target)
        {
            case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
                side = 0;
                break;
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
                side = 1;
                break;
            case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
                side = 2;
                break;
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
                side = 3;
                break;
            case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
                side = 4;
                break;
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
                side = 5;
                break;
        }

        // select GL_COLORATTACHMENTn and read data into image
        glReadBuffer(index);
        glReadPixels(0, 0, 
                     pTexImg->getWidth      (),
                     pTexImg->getHeight     (),
                     pTexImg->getPixelFormat(),
                     pTexImg->getDataType   (),
                     pTexImg->editData      (mipMapLevel, frame, side));
        
        glReadBuffer(GL_NONE);
    }
}