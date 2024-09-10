CommInpCfg :: CommInpCfg()
{
    // Set up logging with stdout as destination
    Category& rootLogCategory = Category::getRoot();
    rootLogCategory.setPriority(Priority::INFO);
    rootLogCategory.removeAllAppenders();

    Appender* appender = new FileAppender("_", dup(fileno(stdout)));
    PatternLayout* patternLayout = new PatternLayout();
    patternLayout->setConversionPattern("[%d{%Y:%m:%d %H:%M:%S.%I}] %p %c %x: %m%n");
    Layout* layout = dynamic_cast<Layout*> (patternLayout);
    appender->setLayout(layout);

    rootLogCategory.addAppender(appender);
}