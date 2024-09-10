void OculusDisplay::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
  if ( !oculus_ )
  {
    return;
  }
  Ogre::RenderWindow *window = render_widget_->getRenderWindow();
  window->swapBuffers();
}