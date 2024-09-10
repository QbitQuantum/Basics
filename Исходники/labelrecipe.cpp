LabelRecipe::LabelRecipe(Container *parent) :
    CustomControl(parent)
{
    Container *recipeContainer = new Container();
    StackLayout *recipeLayout = new StackLayout();
    recipeLayout->setLayoutDirection(LayoutDirection::LeftToRight);
    recipeContainer->setLayout(recipeLayout);

    // Here all the available bold type fonts are stacked in a Container.
    Container *headerStyleContainer = new Container();
    headerStyleContainer->setLayoutProperties(
        DockLayoutProperties::create().horizontal(HorizontalAlignment::Center).vertical(
            VerticalAlignment::Center));

    headerStyleContainer->setRightMargin(60);

    headerStyleContainer->add(
        setUpLabelWithStyle((const QString) "BigText", SystemDefaults::TextStyles::bigText(),
                            true, Color::Gray , true));
    headerStyleContainer->add(
        setUpLabelWithStyle((const QString) "TitleText", SystemDefaults::TextStyles::titleText(),
                            true, Color::Gray, true));
    headerStyleContainer->add(
        setUpLabelWithStyle((const QString) "BodyText", SystemDefaults::TextStyles::bodyText(),
                            true, Color::Gray, true));
    headerStyleContainer->add(
        setUpLabelWithStyle((const QString) "SubtitleText", SystemDefaults::TextStyles::subtitleText(),
                            true, Color::Gray, true ));
    headerStyleContainer->add(
        setUpLabelWithStyle((const QString) "SmallText", SystemDefaults::TextStyles::smallText(),
                            true, Color::Gray, true));

    // The second stacked Container show the regular style fonts.
    Container *paragraphStyleContainer = new Container();

    paragraphStyleContainer->add(
        setUpLabelWithStyle((const QString) "BigText", SystemDefaults::TextStyles::bigText(),
                            false, Color::Gray, false));
    paragraphStyleContainer->add(
        setUpLabelWithStyle((const QString) "TitleText", SystemDefaults::TextStyles::titleText(),
                            false, Color::Gray, false));
    paragraphStyleContainer->add(
        setUpLabelWithStyle((const QString) "BodyText", SystemDefaults::TextStyles::bodyText(),
                            false, Color::Gray, false));
    paragraphStyleContainer->add(
        setUpLabelWithStyle((const QString) "SubtitleText", SystemDefaults::TextStyles::subtitleText(),
                            false, Color::Gray, false));
    paragraphStyleContainer->add(
        setUpLabelWithStyle((const QString) "SmallText", SystemDefaults::TextStyles::smallText(),
                            false, Color::Gray, false));

    recipeContainer->add(headerStyleContainer);
    recipeContainer->add(paragraphStyleContainer);

    setRoot(recipeContainer);
}