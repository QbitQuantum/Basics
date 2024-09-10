SpeedGauge::SpeedGauge(Container *parent) :
    CustomControl(parent)
{
  Container *content = new Container();

  // The content Container will be set to lay out children using a dock layout (to center everything on screen).
  content->setLayout(new DockLayout());

  // Background image in an ImageView
  ImageView *bgImage = ImageView::create("asset:///images/dial_bg.png");

  // Shine Image in an ImageView
  ImageView *dialShineImage = ImageView::create("asset:///images/dial_shine.png");
  dialShineImage->setHorizontalAlignment(HorizontalAlignment::Center);
  dialShineImage->setVerticalAlignment(VerticalAlignment::Center);

  // Create the needles; both needles are centered in the dial and should rotate around the base.
  mSpeedNeedle = setUpNeedle(36.0f, 164.0f, "asset:///images/needle.png");
  mMaxNeedle = setUpNeedle(46.0f, 176.0f, "asset:///images/red_needle.png");

  // Add the controls to the Container.
  content->add(bgImage);
  content->add(mMaxNeedle);
  content->add(mSpeedNeedle);
  content->add(dialShineImage);

  // Set the initial state variable for max speed.
  mMaxSpeedAngle = ZERO_DIAL_ANGLE;

  setRoot(content);
}