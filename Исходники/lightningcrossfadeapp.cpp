Container *LightningCrossfadeApp::setUpSliderContainer(Container *imageContainer)
{
    bool connectResult;
    Q_UNUSED(connectResult);

    // Create the Slider Container with the controls set to sort themselves from
    // left to right rather then top to bottom (which is the default for a StackLayout).
    Container* sliderContainer = Container::create().left(20.0f).right(20.0f);
    sliderContainer->setLayout(StackLayout::create().orientation(LayoutOrientation::LeftToRight));

    // Setting spacequota not equals to one tells this Container
    // that it should fill up the remaining part of the screen.
    sliderContainer->setLayoutProperties(StackLayoutProperties::create().spaceQuota(1));

    // This is the Slider you see at the bottom of the page when it get's a onImmediateValueChanged
    // event it changes the image with id night's opacity to that value, margins for space.
    Slider* opacitySlider = Slider::create().leftMargin(20.0f).rightMargin(20.0f).vertical(VerticalAlignment::Center);

    // Center the slider in the stack layout. We have given a positive space quota which
    // makes the slider opacity value less than the moon and sun icon images when
    // laying out on screens of different widths.
    opacitySlider->setLayoutProperties(StackLayoutProperties::create().spaceQuota(1.0f));
    opacitySlider->setHorizontalAlignment(HorizontalAlignment::Fill);

    // Add A11y description to the slider
    opacitySlider->accessibility()->setDescription(
            "Drag to change image. Night to the left - day to the right");

    // A moon and sun icon image is used to illustrate that time of day, both
    // aligned to the center in a vertical direction to line up with the slider.
    ImageView* moon = ImageView::create("asset:///images/moon.png");
    moon->setVerticalAlignment(VerticalAlignment::Center);
    ImageView* sun = ImageView::create("asset:///images/sun.png");
    sun->setVerticalAlignment(VerticalAlignment::Center);

    // The day image will be attached to a slider so we need to get the corresponding
    // object from the image Container.
    ImageView *dayImage = imageContainer->findChild<ImageView*>("dayImage");

    // Connect the Slider value directly to the opacity property of the day image view.
    connectResult = connect(opacitySlider, SIGNAL(immediateValueChanged(float)), dayImage, SLOT(setOpacity(float)));
    Q_ASSERT(connectResult);

    // Add the components to the slider container (remember that they will be stacked from left to right).
    sliderContainer->add(moon);
    sliderContainer->add(opacitySlider);
    sliderContainer->add(sun);

    return sliderContainer;
}