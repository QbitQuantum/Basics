GraphControl::GraphControl(Container *parent) :
        CustomControl(parent)
{
    Container *content = new Container();

    // The content Container will be set to lay out children using a dock layout (to center everything on screen).
    content->setLayout(new DockLayout());

    // Decoration grid only, needs adjusting to data for a more realistic implementation
    Container *xAxis = Container::create().vertical(VerticalAlignment::Bottom).horizontal(
            HorizontalAlignment::Fill).background(Color::fromARGB(0xff2F4C6E)).preferredHeight(5);
    Container *yAxis = Container::create().vertical(VerticalAlignment::Fill).horizontal(
            HorizontalAlignment::Left).background(Color::fromARGB(0xff2F4C6E)).preferredWidth(5);
    content->add(xAxis);
    content->add(yAxis);

    for (int x = 200; x < 1280; x += 200) {
        content->add(
                Container::create().vertical(VerticalAlignment::Fill).background(
                        Color::fromARGB(0xff2F4C6E)).preferredWidth(3).translate(x, 0));
    }
    for (int y = 200; y < 768; y += 200) {
        content->add(
                Container::create().horizontal(HorizontalAlignment::Fill).background(
                        Color::fromARGB(0xff2F4C6E)).preferredHeight(3).translate(0, y));
    }

    mIsCreated = false;
    connect(this, SIGNAL(creationCompleted ()), this, SLOT(onCreationCompleted ()));

    setRoot(content);
}