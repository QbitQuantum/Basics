void ARDriver::Render(Image<Rgb<byte> >& imFrame, SE3<> se3CfromW) {
  if (!mbInitialised) {
    Init();
    Reset();
  };

  mnCounter++;

  // Upload the image to our frame texture
  glBindTexture(GL_TEXTURE_RECTANGLE_ARB, mnFrameTex);
  glTexSubImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, 0, 0, mirFrameSize.x,
                  mirFrameSize.y, GL_RGB, GL_UNSIGNED_BYTE, imFrame.data());

  // Set up rendering to go the FBO, draw undistorted video frame into BG
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mnFrameBuffer);
  CheckFramebufferStatus();
  glViewport(0, 0, mirFBSize.x, mirFBSize.y);
  DrawFBBackGround();
  glClearDepth(1);
  glClear(GL_DEPTH_BUFFER_BIT);

  // Set up 3D projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMultMatrix(mCamera.MakeUFBLinearFrustumMatrix(0.005, 100));
  glMultMatrix(se3CfromW);

  DrawFadingGrid();

  mGame.DrawStuff(se3CfromW.inverse().get_translation());

  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_BLEND);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Set up for drawing 2D stuff:
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

  DrawDistortedFB();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  mGLWindow.SetupViewport();
  mGLWindow.SetupVideoOrtho();
  mGLWindow.SetupVideoRasterPosAndZoom();
}