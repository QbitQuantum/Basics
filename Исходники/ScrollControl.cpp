bb::cascades::Container* ScrollControl::createImageContainer(QString s) {
	QmlDocument *qml = QmlDocument::create("asset:///article.qml").parent(this);

	// create root object for the UI
	Container *article = qml->createRootObject<Container>();

	qml->setParent(article);

	ImageView* imageView = article->findChild<ImageView*>("imageView");

	int c = setRandomPhoto(imageView);

	article->findChild<Label*>("label")->setProperty("text", s);

	if (c == 0) {
		if (article) {
			article->findChild<Label*>("label")->setProperty("text", "Camera folder is empty");
		}
	}

	return article;
}