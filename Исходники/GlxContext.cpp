GlxContext::GlxContext(GlxContext* shared) :
myWindow    (0),
myContext   (NULL),
myOwnsWindow(true)
{
    // Open a connection with the X server
    myDisplay = XOpenDisplay(NULL);

    // Create a dummy window (disabled and hidden)
    int screen = DefaultScreen(myDisplay);
    myWindow = XCreateWindow(myDisplay,
                             RootWindow(myDisplay, screen),
                             0, 0,
                             1, 1,
                             0,
                             DefaultDepth(myDisplay, screen),
                             InputOutput,
                             DefaultVisual(myDisplay, screen),
                             0, NULL);

    // Create the context
    CreateContext(shared, VideoMode::GetDesktopMode().BitsPerPixel, ContextSettings(0, 0, 0));

    // Activate the context
    SetActive(true);
}