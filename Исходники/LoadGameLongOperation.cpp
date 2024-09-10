bool LoadGameLongOperation::operator()(RLMachine& machine) {
  load(machine);
  // Warning: the stack has now been nuked and |this| is an invalid.

  // Render the current state of the screen
  GraphicsSystem& graphics = machine.system().graphics();

  boost::shared_ptr<Surface> currentWindow = graphics.renderToSurface();
  Size s = currentWindow->size();

  // Blank dc0 (because we won't be using it anyway) for the image
  // we're going to render to
  boost::shared_ptr<Surface> blankScreen = graphics.buildSurface(s);
  blankScreen->fill(RGBAColour::Black());

  machine.pushLongOperation(
      new FadeEffect(machine, currentWindow, blankScreen, s, 250));

  // At this point, the stack has been nuked, and this current
  // object has already been deleted, leaving an invalid
  // *this. Returning false is the correct thing to do since
  // *returning true will pop an unrelated stack frame.
  return false;
}