ActivityIndicatorRecipe::ActivityIndicatorRecipe(Container *parent) :
        CustomControl(parent)
{
    // The recipe Container
    Container *recipeContainer = new Container();
    recipeContainer->setLeftPadding(20.0);
    recipeContainer->setRightPadding(20.0);

    // The introduction text
    TextArea *introText = new TextArea();
    introText->setText((const QString) "This is a milk boiling simulator recipe");
    introText->setEditable(false);
    introText->textStyle()->setBase(SystemDefaults::TextStyles::bodyText());
    introText->setBottomMargin(100);

    Container* smashContainer = new Container();
    smashContainer->setLayout(new DockLayout());

    // Create the unbroken egg ImageView
    mUnbroken = ImageView::create("asset:///images/stockcurve/egg.png");

    // Center the unbroken egg image
    mUnbroken->setHorizontalAlignment(HorizontalAlignment::Center);
    mUnbroken->setVerticalAlignment(VerticalAlignment::Center);

    // Since this broken egg image is on top of the unbroken egg image, we can hide
    // this image by changing the opacity value of this image.
    mBroken = ImageView::create("asset:///images/stockcurve/broken_egg.png").opacity(0.0);

    // Center the brown egg image (same as unbroken one)
    mBroken->setHorizontalAlignment(HorizontalAlignment::Center);
    mBroken->setVerticalAlignment(VerticalAlignment::Center);

    mActivityIndicator = new ActivityIndicator();
    mActivityIndicator->setPreferredSize(130, 130);

    smashContainer->add(mUnbroken);
    smashContainer->add(mActivityIndicator);
    smashContainer->add(mBroken);

    mButton = new Button();
    mButton->setTopMargin(100);
    mButton->setText((const QString) "start cooking");
    connect(mButton, SIGNAL(clicked()), this, SLOT(onClicked()));

    // Add the controls to the recipe Container and set it as root.
    recipeContainer->add(introText);
    recipeContainer->add(smashContainer);

    recipeContainer->add(mButton);

    setRoot(recipeContainer);

}