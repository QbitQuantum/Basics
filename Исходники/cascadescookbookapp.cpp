void CascadesCookbookApp::addApplicationCover()
{
    // A small UI consisting of just an ImageView in a Container is set up
    // and used as the cover for the application when running in minimized mode.
    Container *coverContainer = Container::create();
    coverContainer->setLayout(new DockLayout());

    // A background image for the app cover.
    ImageView *coverImage = ImageView::create("asset:///images/application-cover.png");

    Container *titleContainer = Container::create().bottom(31);
    titleContainer->setHorizontalAlignment(HorizontalAlignment::Center);
    titleContainer->setVerticalAlignment(VerticalAlignment::Bottom);

    Container *labelContainer = Container::create().preferredSize(84, 42).background(Color::fromARGB(0xff121212));
    labelContainer->setLayout(new DockLayout());

    // A title for the "book" cover so that one can see that it is the
    // C++ version of the cookbook that is running.
    Label* title = Label::create("C++");
    title->textStyle()->setColor(Color::fromARGB(0xffebebeb));
    title->textStyle()->setFontSize(FontSize::PointValue);
    title->textStyle()->setFontSizeValue(6);
    title->setHorizontalAlignment(HorizontalAlignment::Center);
    title->setVerticalAlignment(VerticalAlignment::Bottom);

    // Setting up the title Container with a title
    labelContainer->add(title);
    titleContainer->add(labelContainer);

    // Adding the background image and the title Container
    coverContainer->add(coverImage);
    coverContainer->add(titleContainer);

    // Create a SceneCover and set the application cover
    SceneCover *sceneCover = SceneCover::create().content(coverContainer);
    Application::instance()->setCover(sceneCover);
}