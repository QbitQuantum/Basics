ImageRecipe::ImageRecipe(Container *parent) :
		CustomControl(parent) {
	// Get the UIConfig object in order to use resolution independent sizes.
	UIConfig *ui = this->ui();

	// Create the ImageView with an image in the assets folder as imageSource.
	Container *recipeContainer = Container::create().top(ui->du(2)).left(
			ui->du(2)).right(ui->du(2));

    DockLayout *recipeContainerLayout = new DockLayout();
    recipeContainer->setLayout(recipeContainerLayout);

	mImage = ImageView::create("asset:///images/peach_big.png").scalingMethod(
			ScalingMethod::AspectFit);
	mImage->setHorizontalAlignment(HorizontalAlignment::Center);
	mImage->setVerticalAlignment(VerticalAlignment::Center);

	// A checkbox so that we can turn on and off the filterColor property
	CheckBox *filterColorCheckBox = CheckBox::create().text("filterColor");
	filterColorCheckBox->setVerticalAlignment(VerticalAlignment::Bottom);

	connect(filterColorCheckBox, SIGNAL(checkedChanged(bool)), this,
			SLOT(onCheckedChanged(bool)));

	recipeContainer->add(mImage);
	recipeContainer->add(filterColorCheckBox);

	setRoot(recipeContainer);
}