SegmentedControlRecipe::SegmentedControlRecipe(Container *parent) :
		CustomControl(parent) {

	// A recipe showing how to listen to changes in SegmentedControl
	// and use this to change the look of the interface.

	ScrollView *scrollView = new ScrollView();
	ScrollViewProperties* scrollViewProp = scrollView->scrollViewProperties();
	scrollViewProp->setScrollMode(ScrollMode::Vertical);

	Container *recipeContainer = Container::create().left(20.0).right(20.0).bottom(20);
	recipeContainer->setHorizontalAlignment(HorizontalAlignment::Center);
	recipeContainer->setVerticalAlignment(VerticalAlignment::Top);

	StackLayout *recipeLayout = new StackLayout();
	recipeContainer->setLayout(recipeLayout);

	// This labels text is altered when the segmentedControl value is changed.
	mTitleLabel = new Label();
	mTitleLabel->setText("Potato Leek Soup");
	mTitleLabel->textStyle()->setBase(SystemDefaults::TextStyles::bigText());

	// This ImageView's imageSource is altered when the segmentedControl value is changed.
	mImage = ImageView::create("asset:///images/segmentedcontrol/soup_green.png");

	Label *ingredientsTitleLabel = new Label();
	ingredientsTitleLabel->setMultiline(true);
	ingredientsTitleLabel->textStyle()->setBase(SystemDefaults::TextStyles::titleText());
	ingredientsTitleLabel->setText("Ingredients");

	// The segmented control is implemented and given three values and text
	// to represent those values.
	SegmentedControl *segmented = SegmentedControl::create().add(
			bb::cascades::Option::create().text("Leek").value("1").selected(
					true)).add(
			bb::cascades::Option::create().text("Beetroot").value("2")).add(
			bb::cascades::Option::create().text("Garlic").value("3"));

	connect(segmented, SIGNAL(selectedIndexChanged(int)), this, SLOT(onSegmentedIndexChanged(int)));

	Label *ingredientsLabel = new Label();
	ingredientsLabel->setMultiline(true);
	ingredientsTitleLabel->textStyle()->setBase(SystemDefaults::TextStyles::bodyText());
	ingredientsLabel->setText("3 cups chicken broth \n2-3 chopped potatoes \nSalt & Pepper");

	// Add the controls to the recipe Container and scrollView and set it as the root component.
	scrollView->setContent(recipeContainer);
	recipeContainer->add(mTitleLabel);
	recipeContainer->add(mImage);
	recipeContainer->add(ingredientsTitleLabel);
	recipeContainer->add(segmented);
	recipeContainer->add(ingredientsLabel);

	setRoot(scrollView);
}