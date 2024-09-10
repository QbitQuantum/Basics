DateTimePickerRecipe::DateTimePickerRecipe(Container *parent) :
CustomControl(parent)
{
    // The recipe Container.
    Container *recipeContainer = new Container();
    recipeContainer->setLayout(StackLayout::create().top(50.0f));
    recipeContainer->setMinHeight(1024.0f);

    // The recipe title, we add it to a Container in order to get some padding around it.
    Container *titleContainer = new Container();
    titleContainer->setLayout(StackLayout::create().left(20.0f).bottom(20.0f));
    QDateTime date = QDateTime::currentDateTime();
    Label *title = new Label(titleContainer);
    title->setText("Today is: " + date.toString("M/d/yy"));
    title->textStyle()->setBase(SystemDefaults::TextStyles::bodyText());
    title->textStyle()->setColor(Color::White) ;


    // This is where we create the DateTimePicker, we set the mode so that we 
    // can change the date and update the state of the fruit depending on that.
    DateTimePicker *datePicker = new DateTimePicker();
    datePicker->setTitle("Banana at date:");
    datePicker->setMode(DateTimePickerMode::Date);
    connect(datePicker, SIGNAL(valueChanged(QDateTime )), this, SLOT(onValueChanged(QDateTime )));

    // An image of a fruit is used to show how one can use the QDateTime value 
    // reported by the picker.
    Container *fruitContainer = new Container();
    fruitContainer->setTopMargin(20.0f);
    fruitContainer->setLayoutProperties(StackLayoutProperties::create().spaceQuota(1));
    mTimeWarpFruit = ImageView::create("asset:///images/picker/banana_new.png");
    mTimeWarpFruit->setPreferredSize(768.0f, 512.0f);
    fruitContainer->add(mTimeWarpFruit);

    recipeContainer->add(titleContainer);
    recipeContainer->add(datePicker);
    recipeContainer->add(fruitContainer);

    setRoot(recipeContainer);
}