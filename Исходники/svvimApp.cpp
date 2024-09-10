// Just create the latest thing
void svvimApp::draw() {
  
  // SvvimLogo
  if (mSvvimLogoPng)
    mSvvimLogoPng.bind(0);
  
  // Mask
  if (mMaskTexture)
    mMaskTexture.bind(1);
  
  //
  if (mImageTexture)
    mImageTexture.bind(2);
  
  // Clear to black
  gl::clear();

  /*
  if (mMaskTexture) {
    Area bounds = mMaskTexture.getBounds();
    
    Area displayArea = getWindowBounds();
    // displayArea.y1 = displayArea.y1 + displayArea.getHeight() * .05;
    // displayArea.y2 = displayArea.y2 - displayArea.getHeight() * .05;
    
    Rectf centeredRect = Rectf(mMaskTexture.getBounds()).getCenteredFit(displayArea, false);
    
    float coverAspectRatio = mMaskTexture.getAspectRatio();
    float windowAspectRatio = getWindowAspectRatio();
    
    if (coverAspectRatio > windowAspectRatio) {
      float scale = displayArea.getHeight()/centeredRect.getHeight();
      centeredRect.scaleCentered(scale);
    }
    else {
      float scale = displayArea.getWidth()/centeredRect.getWidth();
      centeredRect.scaleCentered(scale);
    }
    
    gl::draw(mMaskTexture, centeredRect);
  } */

  
  // Draw pool-water background cover
  if (mImageTexture) {
    Area bounds = mImageTexture.getBounds();

    Area displayArea = getWindowBounds();
    displayArea.y1 = displayArea.y1 + displayArea.getHeight() * .05;
    displayArea.y2 = displayArea.y2 - displayArea.getHeight() * .05;
    
    Rectf centeredRect = Rectf(mImageTexture.getBounds()).getCenteredFit(displayArea, true);

    float coverAspectRatio = mImageTexture.getAspectRatio();
    float windowAspectRatio = getWindowAspectRatio();
    
    if (coverAspectRatio > windowAspectRatio) {
      float scale = displayArea.getHeight()/centeredRect.getHeight();
      centeredRect.scaleCentered(scale);
    }
    else {
      float scale = displayArea.getWidth()/centeredRect.getWidth();
      centeredRect.scaleCentered(scale);
    }
    
    gl::draw(mCurrentBgTexture, centeredRect);
  }

  if (mShader) {
    float displacement = 10. - min(mAlpha * 300.0, 10.0);
    mShader.bind();
    mShader.uniform("displacement", displacement);
    mShader.uniform("maskTexture", 0);
    mShader.uniform("innerTexture", 2);
    mShader.uniform("fillColor", Vec3f(0.3, 0.3, 0.3));
    mShader.uniform("bounds", Vec2f(getWindowWidth(), getWindowHeight()));
    mShader.uniform("alpha", 6 * mAlpha);
  }
  
  if (mSvvimLogoPng) {
    Rectf centeredRect = Rectf(mSvvimLogoPng.getBounds()).getCenteredFit(getWindowBounds(), true);
    Rectf topRect = centeredRect;
    gl::draw(mSvvimLogoPng, centeredRect);
    centeredRect.y1 -= 200;
    centeredRect.y2 -= 200;
    //gl::draw(mSvvimLogoPng, centeredRect);
    centeredRect.y1 += 400;
    centeredRect.y2 += 400;
    //gl::draw(mSvvimLogoPng, centeredRect);
  }
  
  if (mShader)
    mShader.unbind();
  
  if (mMaskTexture)
    mMaskTexture.unbind();
  
  if (mImageTexture)
    mImageTexture.unbind();
  
  if (mSvvimLogoPng)
    mSvvimLogoPng.unbind();

}