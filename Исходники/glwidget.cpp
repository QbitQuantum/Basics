void GLWidget::paintGL()
{
    makeCurrent();

    glClearColor(0.7, 0.7, 0.7, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    if(Interface::showBackgroundImage)
    {
//        renderTexture.imageAlpha = Interface::alphaBackgroundImage;
//        renderTexture.renderTexture(*mTextManagerObj.getBaseTexture(), Eigen::Vector2i(this->width(), this->height()));
    }


//    phong.render(*mTextManagerObj.getMesh(), *currentCamera, light_trackball);

//      multi.render(mTextManagerObj, *currentCamera, light_trackball);
      multiMask.useWeights = Interface::useWeights;
      multiMask.render(mTextManagerObj, *currentCamera, light_trackball);
//    depthMap.render(*mTextManagerObj.getMesh(), calibrationCamera, light_trackball);

    if(Interface::camera == Interface::CAMERA_TYPES::FREE)
    {
//        camera.render();
        if(Interface::ShowCameras){
            for(int i =0 ; i < mTextManagerObj.getNumPhotos(); i++)
            {
                mTextManagerObj.changePhotoReferenceTo(i);
                camRep.resetModelMatrix();
                Eigen::Affine3f m = (*(mTextManagerObj.getViewMatrix())).inverse();
                m.translation() -= mTextManagerObj.getMesh()->getCentroid();
                m.translation() *= mTextManagerObj.getMesh()->getScale();
                m.scale (0.08);
                camRep.setModelMatrix(m);
                camRep.render(*currentCamera, light_trackball);
            }
            mTextManagerObj.changePhotoReferenceTo(0);
        }
    }
}